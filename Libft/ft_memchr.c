/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:08:26 by mlamrani          #+#    #+#             */
/*   Updated: 2023/11/30 17:17:13 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}
// int main(){
// 	// char s[] = {0, 1, 2 ,3 ,4 ,5};
// 	char *result = ft_memchr("hello", '\0', 5);
// 	//char *result = memchr(0, '\0', 5);
// 	printf("%s", result);
// }
