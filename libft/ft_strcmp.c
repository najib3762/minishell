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

int    ft_strcmp(const char *s1, const char *s2)
{
    size_t    i;

    i = 0;
    while (s1[i] != '\0')
    {
        if (s1[i] != s2[i])
        return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));

        i++;
    }
    return (0);
}
/*int main ()
{
  char str1[] = "hil";
  char str2[] = "hilhu";
  printf("%d",ft_strncmp(str1,str2, 3));
  return 0;
  }*/
