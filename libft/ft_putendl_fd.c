/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:50:35 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/11 18:24:43 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int 	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	if (fd > 0)
	{
		while (s[i])
		{
			write(fd, &s[i++], 1);
		}
		write(fd, "\n", 1);
	}
	return (1);
}
/*
#include <stdio.h>

int	main(void){
	int fd = open("ana.txt", O_RDWR | O_CREAT, 0644);
	printf("%d", fd);
	ft_putendl_fd("ana", fd);
	close (fd);
}*/
