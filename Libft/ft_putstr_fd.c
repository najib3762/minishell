/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:36:04 by mlamrani          #+#    #+#             */
/*   Updated: 2023/11/20 12:24:13 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	if (fd > 0)
	{
		while (s[i])
		{
			write(fd, &s[i++], 1);
		}
	}
}
/*
#include <stdio.h>

int	main(void){
	int fd = open("ana.txt", O_RDWR | O_CREAT, 0644);
	printf("%d", fd);
	ft_putstr_fd("", fd);
	close (fd);
}*/
