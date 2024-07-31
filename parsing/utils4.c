/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:28:41 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/22 17:28:42 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	count_str(char *s, char c1, char c2)
{
	size_t	nb_strings;

	if (!s)
		return (0);
	nb_strings = 0;
	while (*s != '\0')
	{
		if (*s != c1 && *s != c2)
		{
			while (*s != '\0' && (*s != c1 && *s != c2))
				s++;
			nb_strings++;
			continue ;
		}
		s++;
	}
	return (nb_strings);
}

char	*dup_words(char **dest, char *src, char c1, char c2)
{
	size_t	len;
	size_t	i;

	while (*src == c1 || *src == c2)
		src++;
	len = 0;
	while (src[len] != '\0' && (src[len] != c1 && src[len] != c2))
		len++;
	*dest = (char *)malloc(sizeof(char) * (len + 1));	
	if (*dest == NULL)
		return (NULL);
	addback_node_free(&g_global->address, newnode_free(*dest));
	i = 0;
	while (i < len)
	{
		(*dest)[i] = src[i];
		i++;
	}
	(*dest)[i] = '\0';
	src += len + 1;
	return (src);
}

char	**m_split(char *s, char c1, char c2)
{
	char	**strs;
	size_t	nbr_strings;
	size_t	i;

	nbr_strings = count_str(s, c1, c2);
	strs = (char **)malloc(sizeof(char *) * (nbr_strings + 1));
	if (strs != NULL)
	{
		addback_node_free(&g_global->address, newnode_free(strs));
		strs[nbr_strings] = NULL;
		i = 0;
		while (i < nbr_strings)
		{
			s = dup_words(strs + i, s, c1, c2);
			if (s == NULL)
			{
				break ;
			}
			i++;
		}
	}
	return (strs);
}

char	*m_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;
	size_t	len_s;

	i = 0;
	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start > len_s)
	{
		return (m_strdup(""));
	}
	if (len > len_s - start)
	{
		len = len_s - start;
	}
	p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	addback_node_free(&g_global->address, newnode_free(p));
	len += start;
	while (start < len)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}
