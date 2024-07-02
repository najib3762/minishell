#include "include/minishell.h"
#include "include/libft.h"



int ft_isspace(char c)
{
    return ((c >= 9 && c <= 13) || c == 32);
}

t_token *create_newnode(t_type new_type, char *new_value, int flags)
{
    t_token *ptr;
    
    ptr = malloc(sizeof(t_token));
    if(!ptr)
    {  
        perror("malloc");
        exit(1);
    }
    ptr->type = new_type;
    ptr->value = ft_strdup(new_value);
    ptr->flag = flags;
    ptr->next = NULL;
    return (ptr);
}

void addback_node(t_token **head, t_type tnum, char *value, int flags)
{
    t_token *root ;
    t_token *current;
    root = create_newnode(tnum, value, flags);

    if(!*head)
    { 
      *head = root;
      return;
    }

     current = *head;

     while(current->next != NULL)
     current = current->next;
     
     current->next = root;
}

int check_quotes(t_mini *prog) 
{
    int i;
    char quote;  
    int res;

    quote = '\0';
    res = 1;
    i = 0;
    while (prog->line[i]) 
    {
        if (prog->line[i] == '"' || prog->line[i] == '\'') 
        {
            if (quote == '\0') 
                quote = prog->line[i];
            else if (prog->line[i] == quote) 
                quote = '\0';
        }
        i++;
    }
    if (quote != '\0') 
    {
        print_error("Syntax error quotes\n");
        res = 0;
    }
    return res;
}


void free_token_list(t_token **head)
{
    t_token *tmp;

    while (*head != NULL)
    {
        tmp = *head;
        *head = (*head)->next;
            free(tmp->value);
        free(tmp);
    }
    *head = NULL;
}


// void ft_parsing(t_mini *prog, t_token **head)
// {
// }



