#include "include/minishell.h"


void sig_here_doc(int sig)
{
    (void)sig;
    write(1, "\n", 1);
}

pid_t fork_heredoc(char *eof, int fd, int qoutes)
{
    pid_t pid;
    char *line;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0)
    {
      line = readline(">");
        while (line)
        {
            signal(SIGINT, sig_here_doc);
            if (!ft_strncmp(line, eof, ft_strlen(eof)) && (ft_strlen(line) == ft_strlen(eof)))
                return (free(line), close(fd), exit(0), 0);
            if (ft_strncmp(line, eof, ft_strlen(eof)) && qoutes != 1 && check_dollar(line))
                        line = ft_expand(line);
            ft_putendl_fd(line, fd);
            free(line);
     line = readline(">");
        }
    exit(0);
    }
    return pid;
}

int read_here_doc(char *eof, int fd)
{
    pid_t heredoc_pid;
    int status;
    char *limiter;
    int qoutes;
 
    qoutes = 0;
    limiter = is_qoutes(eof, &qoutes);
    if(!limiter)
       return (-1);
    heredoc_pid = fork_heredoc(limiter, fd, qoutes);
    if (heredoc_pid < 0)
    {
        perror("fork");
        return (-1);
    }

    waitpid(heredoc_pid, &status, 0);
    if(WIFEXITED(status))
        return (WEXITSTATUS(status));
  return (1);
}


int here_doc2(t_token *token)
{
    char *filename;
    int fd;
    
    filename = random_file();
    if (!filename)
        return (-1);
    fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return (free(filename), -1);
    if( token->next->type == TOKEN_WORD)
    {
    if(read_here_doc(token->next->value, fd) != 0)
        return (close(fd), free(filename), -1);
    }
    else
        return (close(fd), free(filename), -1);
    close(fd);
    change_value_node(token, filename);
    return (0);
}

int ft_here_doc(t_token **token)
{
    t_token *tmp;

    tmp = *token;
    while (tmp)
    {
        if (tmp->type == TOKEN_HERE &&  here_doc2(tmp) < 0)
        return (-1);
        tmp = tmp->next;
    }
    return (0);
}

