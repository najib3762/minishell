/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:03:48 by mlamrani          #+#    #+#             */
/*   Updated: 2023/12/01 16:20:27 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	size_t	start;
	size_t	end;
	char	*p;

	size = 0;
	start = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, (char)s1[start]))
		start++;
	while (s1[end] && ft_strrchr(set, s1[end]))
		end--;
	size = end - start + 1;
	p = ft_substr(s1, start, size);
	if (!p)
		return (0);
	return (p);
}
// int main()
// {
//     // char space = " ";
//     char s1[] = "lorem \n ipsum \t dolor \n sit \t amet";
//     printf("%s", ft_strtrim(s1, " " ));
// }