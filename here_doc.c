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

void here_doc(t_token *token)
{
    char *filename;
    int fd;
    char *line;
    char *eof;
    t_global *g;
    char *ptr;

    filename = random_file();
    fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fd < 0)
    {
        perror("open");
        exit(1);
    }
    eof = is_qoutes(token->next->value);

      line = readline(">");
        while (line)
        {
            if (ft_strcmp(line, eof) && g->g_qoutes != 1 && !check_dollar(line))
            {

            }
            if (ft_strcmp(line, eof) == 0)
            {
                free(line);
                break;
            }
            write(fd, line, ft_strlen(line));
            write(fd, "\n", 1);
            free(line);
            line = readline(">");
        }
    // addback_node(&prog->token, TOKEN_WORD, filename, 0);
}