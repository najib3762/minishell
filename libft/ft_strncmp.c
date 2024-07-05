/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macpro15 <macpro15@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:27:28 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/05 14:25:32 by macpro15         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;
	int				r;

	r = 0;
	i = 0;
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
