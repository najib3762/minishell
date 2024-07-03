/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:07:03 by mlamrani          #+#    #+#             */
/*   Updated: 2023/11/20 16:34:43 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*p;
	size_t	i;

	i = 0;
	p = (char *)malloc(sizeof(char) * ((ft_strlen(s)) + 1));
	if (!p)
		return (0);
	while (*s)
		p[i++] = *s++;
	p[i] = '\0';
	return (p);
}
/*
#include <stdio.h>

int	main(void){
  char s[] = " ";
  printf("%s", ft_strdup(s));
}*/
