/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:14:43 by mlamrani          #+#    #+#             */
/*   Updated: 2023/11/30 15:29:28 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*pdest;
	unsigned char	*psrc;
	size_t			i;

	pdest = (unsigned char *)dest;
	psrc = (unsigned char *)src;
	if (!pdest && !psrc)
		return (pdest);
	if (psrc < pdest)
	{
		i = n;
		while (i--)
			pdest[i] = psrc[i];
	}
	else if (psrc > pdest)
	{
		i = 0;
		while (i < n)
		{
			pdest[i] = psrc[i];
			i++;
		}
	}
	return (dest);
}
// #include <stdio.h>
// int main() {
//     char src[] = "lorem ipsum dolor sit amet";
//     char dest[20];

//     ft_memmove(dest, src + 2, 19);

//     // dest[20] = '\0';

//     printf("Original string: %s\n", src);
//     printf("Copied string: %s\n", dest);

//     return (0);
// }
