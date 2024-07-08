#include"include/minishell.h"

void remove_qoutes_fl(char *str, char *new_str)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while(str[i])
    {
        new_str[j] = str[i];
        i++;
        j++;
    }
    new_str[j - 1] = '\0';
}

char *remove_quotes(char *str)
{

    int i;
    int j;
    char *new_str;
    int len;
    int much;

    i = 0;
    j = 0;
    much = calcule_qoutes(str);
    len = ft_strlen(str) - much;
    new_str = malloc(sizeof(char) * (len + 1));
    if(!new_str)
    {
        perror("malloc");
        return NULL;
    }

     if(str[0] == '\'' || str[0] == '\"')
     {
        remove_qoutes_fl(str, new_str);
     }
     else
     {
    while(str[i])
    {
        if(str[i] != '\'' && str[i] != '\"')
        {
            new_str[j] = str[i];
            j++;
        }
        i++;
    }
    new_str[j] = '\0';
    }
    return new_str;
    
}

void concatenate_lexer(t_token **head)
{
    
    t_token *temp = *head;

    while(temp)
    {
        if(temp->type == TOKEN_WORD)
        {
            if(check_qoutes(temp->value))
            {
                temp->value = remove_quotes(temp->value);
            }
        }
        temp = temp->next;
    }

}