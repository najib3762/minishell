#include "include/minishell.h"

//"sdfdsf""$USER"sdsfdsaf
//PATH=/bin/zsh
//USER = namoussa
char	*my_strdup(char *str, int len)
{
	char	*array;
	int		i;

	if (!str || !len)
		return (NULL);
	i = -1;
	array = (char *)malloc((len + 1) * sizeof(char));
	if (!array)
		return (NULL);
	while (++i < len)
		array[i] = str[i];
	array[i] = '\0';
	return (array);
}

char	*my_strjoin(char *s1, char *s2)
{
	size_t	i;
	int		len;
	char	*array;

	i = 0;
    len = 0;
    if (!s1 && !s2)
            return (NULL);
	if (!s1)
		     return (s2);
    if(!s2)
             return (s1);
	len = ft_strlen(s2) + ft_strlen(s1);
	array = (char *)malloc(sizeof(char) * (len + 1));
	if (!array)
		return (NULL);
	len = 0;
	while (s1[i])
		array[len++] = s1[i++];
	i = 0;
	while (s2[i])
        array[len++] = s2[i++];
	array[len] = '\0';
    free(s1);
    free(s2);
	return (array);
}

char *ft_strdup_char(char c)
{
    char *array;

    array = (char *)malloc(sizeof(char) * 2);
    if (!array)
        return (NULL);
    array[0] = c;
    array[1] = '\0';
    return (array);
}

char *ft_strjoin_char(char *s1, char c)
{
     
    char *array;
    int i;
    int len;

    i = 0;
	if (!s1)
		return (ft_strdup_char(c));
    len = ft_strlen(s1);
    array = (char *)malloc(sizeof(char) * (len + 2));
    if (!array)
        return (NULL);
    while (s1[i])
    {
        array[i] = s1[i];
        i++;
    }
    array[i] = c;
    array[i + 1] = '\0';
    free(s1);
    return (array);
}
char	*my_getenv(char *name, char *env)
{
	int		i;
	char	*value;
	int		j;

	i = 0;
	j = 0;
	value = NULL;
	while (env[i] && env[i] != '=')
    {
		value = ft_strjoin_char(value, env[i]);
        i++;
    }
	if (ft_strcmp(value, name) == 0)
	{
		free(value);
		return (ft_strdup(env + (i + 1)));
	}
	free(value);
	return (NULL);
}

char	*get_env_value(char *key, t_list *env)
{
	t_list	*temp;
	char	*value;

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

char *take_var_name(char *str, int *i)
{
    int j;
    char *var_name = NULL;

    j = 0;
    if (!var_name)
    {
        var_name = malloc(sizeof(char) * 1);
        var_name[0] = '\0';
    }
    while (ft_isalpha(str[*i]) || ft_isdigit(str[*i]) || str[*i] == '_')
    {
        var_name = ft_strjoin_char(var_name, str[*i]);
        (*i)++;
    }
    return (var_name);
}


char	*handle_dollar(char *str, int *i, t_mini *prog)
{
	char	*var_name;
	char	*var_value;

    var_name = NULL;
    var_value = NULL;
	(*i)++;
	if (ft_isalpha(str[*i]) || ft_isdigit(str[*i]))
		      var_name = take_var_name(str, i);
	var_value = get_env_value(var_name, prog->env_head);
	if (var_value)
		     return (free(var_name),var_value);
	return (free(var_name), NULL);
}

char	*handle_dquotes(char *str, int *i, t_mini *prog)
{
	char	*double_quote;
	char	*temp;

	double_quote = NULL;
    temp = NULL;  
	double_quote = ft_strjoin_char(double_quote, str[*i]);
	(*i)++;
	while (str[*i] && (str[*i] != '\"' || str[*i] == '_'))
    {
		 double_quote = ft_strjoin_char(double_quote, str[*i]);
        (*i)++;
    }
	double_quote = ft_strjoin_char(double_quote, str[*i]);
	(*i)++;
	temp = ft_expand(double_quote, prog);
     if (temp)
           return (free(double_quote), temp);
	return (free(double_quote), NULL);
}

char	*handle_squotes(char *str, int *i)
{
	char	*single_quote;

    single_quote = NULL;
	single_quote = ft_strjoin_char(single_quote, str[*i]);
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		single_quote = ft_strjoin_char(single_quote, str[*i]);
		(*i)++;
	}
	single_quote = ft_strjoin_char(single_quote, str[*i]);
	(*i)++;
    
	return (single_quote);
}

char	*dollar_expand(char *str, t_mini *prog)
{
	char	*temp;
	int		i = 0;

    temp = NULL;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isdigit(str[i + 1])) && str[i + 2] != '\0')
			i += 2;
		else if (str[i] == '$' && (ft_isalpha(str[i + 1]) || ft_isdigit(str[i + 1])))
           	   temp = my_strjoin(temp, handle_dollar(str, &i, prog));
		else if (str[i] == '\"')
    			temp = my_strjoin(temp, handle_dquotes(str, &i, prog));
		else if (str[i] == '\'')
			   temp = my_strjoin(temp, handle_squotes(str, &i));
		else if (str[i] != '\0')
        {
			  temp = my_strjoin(ft_strdup(temp), ft_strdup_char(str[i]));
                i++;
        }
        if (str[i] == '\0')
            break;

	}
    printf("new_str = %s\n", temp);
	return (temp);
}


void real_expand(t_token **head, t_mini *prog)
{
        t_token *temp;
        char *new_str;

         temp = *head;
          new_str = NULL;
         while(temp)
         {
               if(temp->type == TOKEN_WORD)
               {
                   if(check_dollar(temp->value))
                   {
                        new_str = dollar_expand(temp->value, prog);
                        if(new_str != NULL)
                              temp->value = new_str;
                        else
                              temp->value = "";
                   }
               }
               temp = temp->next;
         }
       
}

