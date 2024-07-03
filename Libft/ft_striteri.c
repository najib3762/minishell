/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:32:49 by mlamrani          #+#    #+#             */
/*   Updated: 2023/11/26 17:39:56 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
// #include <stdio.h>
// void f_striteri(unsigned int i, char *s)
// {
//     (void)i;
// 	s += 1;
// }
// int main(){
// char b[] = "override this !";
// char b2[0xF0];
// size_t size = ft_strlen(b);

// for (unsigned int i = 0; i < size; i++)
// 	f_striteri(i, b2 + i);
// b2[size] = 0;
// ft_striteri(b, f_striteri);
// if (!strcmp(b, b2))
// 	exit(1);
// exit(3);
// }