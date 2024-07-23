/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:26:24 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 18:26:25 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_strdup(char *str, int len)
{
	char	*array;
	int		i;

	if (!str || !len)
		return (NULL);
	i = -1;
	array = (char *)malloc((len + 1) * sizeof(char));
	addback_node_free(&g_global->address, newnode_free(array));
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
	if (!s2)
		return (s1);
	len = ft_strlen(s2) + ft_strlen(s1);
	array = (char *)malloc(sizeof(char) * (len + 1));
	addback_node_free(&g_global->address, newnode_free(array));
	if (!array)
		return (free(s1), free(s2), NULL);
	len = 0;
	while (s1[i])
		array[len++] = s1[i++];
	i = 0;
	while (s2[i])
		array[len++] = s2[i++];
	array[len] = '\0';
	return (free(s1), free(s2), array);
}

int	all_dollar(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '?' || c == '\"' || c == '\''
		|| c == '_')
		return (1);
	return (0);
}
