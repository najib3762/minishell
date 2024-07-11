#include "include/minishell.h"

//"sdfdsf""$USER"sdsfdsaf
//PATH=/bin/zsh
//USER = namoussa

char	*my_getenv(char *name, char *env)
{
	int		i;
    char    *value;
    int j;

	i = 0;
    j = 0;
    value = malloc(BUFSIZ);

		while (env[i] && env[i] != '=')
                value[j++] = env[i++];
        value[j] = '\0';
		if (ft_strcmp(value, name) == 0)
		{
            free(value);
            return (&env[i] + 1);
		
		}
	 free(value);
	return (NULL);
}

char *get_env_value(char *key, t_list *env)
{
    t_list *temp;
    char *value;

    temp = env;
    while (temp)
    {
        value = my_getenv(key, temp->content);
        if (value)
            return (value);
         
        temp = temp->next;
    }
    return (NULL);
}

char *dollar_expand( char *str, t_list *env)
{
    char *new_str;
    char *temp;
    char *value;
    char *key;
    int i;
    int j;
    int k;
    int l;

    i = 0;
    j = 0;
    k = 0;
    l = 0;

    new_str = malloc(sizeof(char) * ft_strlen(str) + 1);
    while(str[i])
    {
        
        if(str[i] == '$' && (ft_isdigit(str[i + 1])) && str[i + 2] != '\0') 
        {
            i+=2;
            new_str[j++] = str[i++];
        }
        if (str[i] == '$' && (ft_isalpha(str[i + 1]) || ft_isdigit(str[i + 1])))
        {
            i++;
            k = 0;
            while (ft_isalpha(str[i]) || ft_isdigit(str[i]))
            {
                key[k++] = str[i++];
            }
            key[k] = '\0';
            value = get_env_value(key, env);
            if (value)
            {
                l = ft_strlen(value);
                ft_strncpy(new_str + j, value, l);
                j += l;
            }
        }

        else
        {
            new_str[j++] = str[i++];
        }
    }
       new_str[j] = '\0';
       return new_str;
}

void real_expand(t_token **head, t_mini *prog)
{
        t_token *temp;

         temp = *head;

         while(temp)
         {
               if(temp->type == TOKEN_WORD)
               {
                   if(check_dollar(temp->value))
                   {
                        temp->value = dollar_expand(temp->value, prog->env_head);
                   }
               }
               temp = temp->next;
         }
       
}

