/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <namoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:27:28 by namoussa          #+#    #+#             */
/*   Updated: 2023/11/17 12:59:27 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;
	int				r;

	r = 0;
	while ((s1[i] || s2[i]) && r == 0 && i < n)
	{
		if (s1[i] != s2[i])
		{
			r = s1[i] - s2[i];
		}
		i++;
	}
	return (r);
}
/*int main ()
{
  char str1[] = "hil";
  char str2[] = "hilhu";
  printf("%d",ft_strncmp(str1,str2, 3));
  return 0;
  }*/
