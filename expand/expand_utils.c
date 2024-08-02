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
	char		*array;
	t_global	*g_global;

	g_global = global_function();
	array = (char *)malloc(sizeof(char) * 2);
	if (!array)
		return (NULL);
	addback_node_free(&g_global->address, newnode_free(array));
	array[0] = c;
	array[1] = '\0';
	return (array);
}

char	*ft_strjoin_char(char *s1, char c)
{
	char		*array;
	int			i;
	int			len;
	t_global	*g_global;

	i = 0;
	len = 0;
	g_global = global_function();
	if (!s1)
		return (ft_strdup_char(c));
	len = ft_strlen(s1);
	array = (char *)malloc(sizeof(char) * (len + 2));
	if (!array)
		return (NULL);
	addback_node_free(&g_global->address, newnode_free(array));
	while (s1[i])
	{
		array[i] = s1[i];
		i++;
	}
	array[i] = c;
	array[i + 1] = '\0';
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
		return (m_strdup(env + (i + 1)));
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
	int			j;
	char		*var_name;
	t_global	*g_global;

	var_name = NULL;
	g_global = global_function();
	j = 0;
	if (!var_name)
	{
		var_name = malloc(sizeof(char) * 1);
		if (!var_name)
			return (NULL);
		addback_node_free(&g_global->address, newnode_free(var_name));
		var_name[0] = '\0';
	}
	while (all_dollar1(str[*i]) && str[*i])
	{
		var_name = ft_strjoin_char(var_name, str[*i]);
		(*i)++;
	}
	return (var_name);
}
