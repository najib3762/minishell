/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:35:03 by mlamrani          #+#    #+#             */
/*   Updated: 2023/11/30 17:34:23 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[j] == '\0')
		return ((char *)big);
	if (len <= 0)
		return (NULL);
	while (big[i] && i < len)
	{
		if (big[i] == little[j])
		{
			while (i + j < len && big[i + j] == little[j])
			{
				j++;
				if (little[j] == '\0')
					return ((char *)big + i);
			}
			j = 0;
		}
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	size_t		len;
// 	const char	word[] = "";

// 	// char hand[] = NULL;
// 	len = -2;
// 	// printf("%s\n", strnstr(hand, word, 7));
// 	printf("%p\n", ft_strnstr("cc", word, 16));
// 	printf("%p\n", ft_strnstr("cc", word, 16));
// 	printf("num is :%zu", len);
// }
