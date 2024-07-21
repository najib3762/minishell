/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:36:09 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/11 18:24:43 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdio.h>

static int	num_words(char const *s, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (*s == sep)
			count = 0;
		else if (count == 0)
		{
			count = 1;
			i++;
		}
		s++;
	}
	return (i);
}

static void	free_my_split(char **p, int word_index)
{
	while (word_index >= 0)
		free(p[word_index--]);
	free(p);
}

static int	check(char const *s, char sep, int i, int start)
{
	int	wordlength;

	wordlength = 0;
	if (i == 0)
	{
		while (s[start] && s[start] == sep)
			start++;
		return (start);
	}
	if (i == 1)
	{
		while (s[start] && s[start] != sep)
		{
			wordlength++;
			start++;
		}
		return (wordlength);
	}
	return (0);
}

static char	**mini_split(char const *s, char sep, int i, char **ptr)
{
	int	wordlength;
	int	word_index;

	word_index = 0;
	wordlength = 0;
	while (s[i])
	{
		if (s[i] == sep)
		{
			i = check(s, sep, 0, i);
		}
		else
		{
			wordlength = check(s, sep, 1, i);
			ptr[word_index] = (char *)malloc((wordlength + 1) * sizeof(char));
			if (!ptr[word_index])
				free_my_split(ptr, word_index);
			ft_strlcpy(ptr[word_index], s + i, wordlength + 1);
			word_index++;
			i += wordlength;
		}
	}
	ptr[word_index] = 0;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	int		number;
	char	**ptr;

	
	if (!s || s == 0)
		return (NULL);
	number = num_words(s, c);
	ptr = (char **)malloc((number + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	mini_split((char *)s, c, 0, ptr);
	ptr[number] = (char *) '\0';
	return (ptr);
}
