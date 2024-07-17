/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:26:32 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 18:26:33 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_char(char c)
{
	char	*array;

	array = (char *)malloc(sizeof(char) * 2);
	addback_node_free(&g_global->address, newnode_free(array));
	if (!array)
		return (NULL);
	array[0] = c;
	array[1] = '\0';
	return (array);
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*array;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!s1)
		return (ft_strdup_char(c));
	len = ft_strlen(s1);
	array = (char *)malloc(sizeof(char) * (len + 2));
	addback_node_free(&g_global->address, newnode_free(array));
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
		return (free(value), m_strdup(env + (i + 1)));
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

char	*take_var_name(char *str, int *i)
{
	int		j;
	char	*var_name;

	var_name = NULL;
	j = 0;
	if (!var_name)
	{
		var_name = malloc(sizeof(char) * 1);
		addback_node_free(&g_global->address, newnode_free(var_name));
		if( !var_name)
			return (NULL);
		var_name[0] = '\0';
	}
	while (ft_isalpha(str[*i]) || ft_isdigit(str[*i]) || str[*i] == '_')
	{
		var_name = ft_strjoin_char(var_name, str[*i]);
		(*i)++;
	}
	return (var_name);
}
