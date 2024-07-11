#include "include/minishell.h"

void redirection(t_parse **parse)
{
    t_parse *temp;
    t_redir *temp_redir;

    temp = *parse;

    while(temp)
    {
        if(temp->redir_list)
        {
           
            temp_redir = temp->redir_list;
            while(temp_redir)
            {
                if(temp_redir->type == REDIR_IN)
                    temp->red_in = open(temp_redir->filename, O_RDONLY);
                else if(temp_redir->type == REDIR_OUT)
                    temp->red_out = open(temp_redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                else if(temp_redir->type == REDIR_APPEND)
                    temp->red_out = open(temp_redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
                temp_redir = temp_redir->next;
            }
        }
        temp = temp->next;
    }
}


int create_multiple_pipe(t_parse *parse)
{

     

}

