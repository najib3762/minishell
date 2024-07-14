#include "../minishell.h"

void close_fd_pipe(t_mini *prog)
{
    int **fd;
    int i;

    i = 0;
    fd = prog->fd;
    while(fd[i])
    {
        close(fd[i][0]);
        close(fd[i][1]);
        i++;
    }
}

void free_fd_pipe(t_mini *prog)
{
    int **fd;
    int i;

    i = 0;
    fd = prog->fd;
    while(fd[i])
    {
        free(fd[i]);
        i++;
    }
    free(fd);
}

int set_pipe_fd(t_mini *prog, t_parse **parse)
{
      int **fd_arr;
      t_parse *temp;
      int i;

    i = 1;
     if(!prog->fd)
        return (0);
    fd_arr = prog->fd;
    temp = *parse;
    temp->red_out = fd_arr[0][1];
    temp = temp->next;
    while(fd_arr[i])
    {
        temp->red_in = fd_arr[i - 1][0];
        temp->red_out = fd_arr[i][1];
        temp = temp->next;
        i++;
    }
    temp->red_in = fd_arr[i - 1][0];
    return (0);
}

int **create_multiple_pipe(t_parse **parse, t_mini *prog)
{
    
    t_parse *temp;
    int  i;
    int j;

    i = 0;
    j = 0;
    temp = *parse;
    while(temp)
    {
            i++;
        temp = temp->next;
    }
    if(i == 1)
        return (0);
    prog->fd = (int **)malloc(sizeof(int *) * i);
    if(!prog->fd_head)
        return (0);
    while(j < i - 1)
    {
         prog->fd[j++] = (int *)malloc(sizeof(int) * 2);
        if(!prog->fd_head[j])
            return (0);
            pipe(prog->fd[j++]);
    }
        prog->fd[j] = NULL;
    return (prog->fd);
}
