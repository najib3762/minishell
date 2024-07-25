/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 11:49:22 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 11:49:28 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int    ft_strcmp(const char *s1, const char *s2)
{
    size_t    i;
    
	if(s1 == NULL || s2 == NULL)
		return (-1);
    i = 0;
    while (s1[i] != '\0')
    {
        if (s1[i] != s2[i])
        return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
        i++;
    }
    return (0);
}
