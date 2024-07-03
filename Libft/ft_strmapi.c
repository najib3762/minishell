/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:31:33 by mlamrani          #+#    #+#             */
/*   Updated: 2023/11/21 15:12:46 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*p;

	i = 0;
	if (!s)
		return (0);
	p = (char *)malloc(ft_strlen(s) + 1);
	if (!p)
		return (0);
	while (i < ft_strlen(s))
	{
		p[i] = f(i, s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
// #include <stdio.h>
// char my_z(unsigned int i, char s)
// {
//     (void)i;
//     s = 'z';
//     return (s);
// }
// int main(){
//     // char s[] = 0;
//     char *result = ft_strmapi(s, my_z);
//     printf("%s", result);

// }