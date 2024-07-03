/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:58:10 by mlamrani          #+#    #+#             */
/*   Updated: 2023/11/30 16:09:31 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	t;
	size_t	j;

	i = 0;
	j = 0;
	j = ft_strlen(dst);
	t = j + ft_strlen(src);
	if (size <= j)
		return (ft_strlen(src) + size);
	while (src[i] && (i + j) < size - 1)
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	return (t);
}

// int main(){
// char dest[10] = "a";
// ft_strlcat(dest, "lorem ipsum dolor sit amet",0);
// printf("%s\n", dest);
// }
