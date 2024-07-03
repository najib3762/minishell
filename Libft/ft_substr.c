/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:55:41 by mlamrani          #+#    #+#             */
/*   Updated: 2023/12/01 15:05:35 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
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
		return (ft_strdup(""));
	}
	if (len > len_s - start)
	{
		len = len_s - start;
	}
	p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	len += start;
	while (start < len)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}

// #include <stdio.h>

// int	main(void){
// 	char *str= ft_strdup("0123456789");
// 	char *ptr = ft_substr(str, 9, 10);
// 	printf("%s", ptr);
// 	free(str);
// 	free(ptr);
// }