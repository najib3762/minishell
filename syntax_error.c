#include "include/minishell.h"

int check_syntax_errors(t_token *head) 
{
    t_token *current = head;

    if (current && current->type == TOKEN_PIPE) 
    {
        print_error("syntax error near unexpected token `|'\n");
        return 1;
    }

    while (current) 
    {
        if (current->type == TOKEN_PIPE) 
        {
            if (!current->next || current->next->type == TOKEN_PIPE) 
            {
                print_error("syntax error near unexpected token `|'\n");
                return 1;
            }
        } 
        else if (current->type == TOKEN_OUT || current->type == TOKEN_APPEND ||
                   current->type == TOKEN_IN || current->type == TOKEN_HERE) 
        {
            if (!current->next || current->next->type != TOKEN_WORD)
            {
                print_error("Syntax error  invalid redirection\n");
                return 1;
            }
        }
        current = current->next;
    }
    return 0;
}
