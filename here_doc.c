#include "include/minishell.h"


#define FILENAME "/tmp/here_doc_"

char *random_file()
{
    char *filename;
    static int i;

    filename = ft_strjoin(FILENAME, ft_itoa(i++));
    return (filename);
}

char *concatunation(char *str)
{

    char *eof;
    int i;
    int j;
    int len;
    t_global *g;

    i = 0;
    j = 0;
    len = ft_strlen(str);
    g->g_qoutes = 1;
    eof = malloc(sizeof(char) * (len + 1));
    if (!eof)
    {
        perror("malloc");
        exit(1);
    }
    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
            i++;
        eof[j] = str[i];
        i++;
        j++;
    }
    eof[j] = '\0';
    return (eof);   
}

char *is_qoutes(char *str)
{
    char *eof;
    if(str[0] == '\'' || str[0] == '"')
    eof = concatunation(str);
    else
    eof = str;
    return (eof);
}

int check_dollar(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
            return (1);
        i++;
    }
    return (0);
}

char *ft_expand(char *line)
{
    char *new_line;
    int i;
    int j;
    int k;
    char var_name[100];
    char *var_value;
    int len;


     new_line = malloc(BUFSIZ);
     i = 0;
     j = 0;
    while (line[i])
    {
        if (line[i] == '$' && (ft_isalnum(line[i + 1]) || ft_isdigit(line[i + 1])))
        {
            i++;
            k = 0;
            while (ft_isalnum(line[i]) || ft_isdigit(line[i]))
            {
                var_name[k++] = line[i++];
            }
            var_name[k] = '\0';

            var_value = getenv(var_name);
            if (var_value)
            {
                len = strlen(var_value);
                strncpy(new_line + j, var_value, len);
                j += len;
            }
        }
        else
        {
            new_line[j++] = line[i++];
        }
    }
    new_line[j] = '\0';
    return new_line;
}
pid_t fork_heredoc( char *eof, int fd)
{
    pid_t pid;
    char *line;
    char *ptr;
    t_global *g;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return (-1);
    }
    if (pid == 0)
    {

      line = readline(">");
        while (line)
        {
            signal(SIGINT, SIG_DFL);
            if (!ft_strncmp(line, eof, ft_strlen(eof)) && (ft_strlen(line) == ft_strlen(eof)))
            {
                return (free(line), close(fd), exit(0), 0);
            }

            if (ft_strncmp(line, eof, ft_strlen(eof)) && g->g_qoutes != 1 && !check_dollar(line))
            {
                        line = ft_expand(line);
            }
           
            write(fd, line, ft_strlen(line));
            write(fd, "\n", 1);
            free(line);
            line = readline(">");
        }
    close(fd);
    exit(0);
    }
    return pid;
}
int read_here_doc(char *eof, int fd)
{
    pid_t heredoc_pid;
    int status;
    char *line;
    char *ptr;
    
       eof = is_qoutes(eof);
       if(!eof)
       return (-1);

    heredoc_pid = fork_heredoc(eof, fd);
    if (heredoc_pid < 0)
    {
        perror("fork");
        return (-1);
    }
    waitpid(heredoc_pid, &status, 0);
    if(WIFEXITED(status))
        return (WEXITSTATUS(status));
  return (0);
}
void change_value_node(t_token *token, char *filename)
{
    free(token->value);
    token->value = filename;
    token->type = TOKEN_WORD;
    free(token->next->value);
    token->next->value = ft_strdup("<");
    token->next->type = TOKEN_IN;
}

int here_doc2(t_token *token)
{
    char *filename;
    int fd;

    filename = random_file();
    fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return (free(filename), -1);
    if(read_here_doc(token->next->value, fd) != 0);
        return (unlink(filename), close(fd), free(filename), -1);
    close(fd);
    change_value_node(token, filename);
    return (0);
}

int ft_here_doc(t_token *token)
{
    t_token *tmp;
    // t_token *tmp2;

    tmp = token;
    while (tmp)
    {
        if (tmp->type == TOKEN_HERE &&  here_doc2(tmp) < 0)
        return (-1);
        tmp = tmp->next;
    }
    return (0);
}

// int main()
// {
//     t_global *g;
     

//     g = malloc(sizeof(t_global));
//     if (!g)
//     {
//         perror("malloc");
//         return 1;
//     }

//     t_token token1 = { "<<", TOKEN_HERE, NULL };
//     t_token token2 = { "EOF", TOKEN_WORD, NULL };
//     token1.next = &token2;

//     ft_here_doc(&token1);

//     printf("Temporary file created: %s\n", token1.value);

//     free(token1.value);
//     free(g);

//     return 0;
// }
