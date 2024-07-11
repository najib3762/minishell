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
int is_double(char c)
{
    if(c == '"')
        return 1;
    return 0;
}
char *dollar_expand( char *str, t_mini *prog)
{
    char *new_str;
    char var_name[100];
    char *var_value;
    char  double_quote[100];
    int i;
    int j;
    int k;
    int len;
    int l;

    i = 0;
    j = 0;
    k = 0;
    len = 0;
    new_str = malloc(BUFSIZ);
    // double_quote = malloc(BUFSIZ);

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
                var_name[k++] = str[i++];
            }
            var_name[k] = '\0';

            var_value = get_env_value(var_name, prog->env_head);
            if (var_value)
            {
                len = ft_strlen(var_value);
                strncpy(new_str + j, var_value, len);
                j += len;
            }
        }
        else if (str[i] == '\"')
        {
            l = 0;
            double_quote[l++] = str[i++];
            while(str[i] != '"')
            {
                double_quote[l++] = str[i++];
            }
            double_quote[l++] = str[i++];
            double_quote[l] = '\0';
           

            char *temp = ft_expand(double_quote, prog);
            if(temp)
            {
                int l = ft_strlen(temp);
                strncpy(new_str + j, temp, l);
                j += l;
                free(temp);
            }
        }
        else if (str[i] == '\'')
        {
            new_str[j++] = str[i++];
            while(str[i] != '\'')
            {
                new_str[j++] = str[i++];
            }
            new_str[j++] = str[i++];
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
                        temp->value = dollar_expand(temp->value, prog);
                   }
               }
               temp = temp->next;
         }
       
}

