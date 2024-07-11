#include "include/minishell.h"

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

int check_qoutes(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] && (str[i] == '\"' || str[i] == '\''))
            return (1);
        i++;
    }
    return (0);
}

char *is_qoutes(char *str, int *qoutes)
{
    char *eof;
    
   
    if(check_qoutes(str) == 1)
       {    
        eof = skip_quotes(str);
        *qoutes = 1;
       }
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

// int special_char(char c)
// {
//     if (c == '?' || c == '_')
//         return (1);
//     return (0);
// }
