/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:05:46 by mlamrani          #+#    #+#             */
/*   Updated: 2023/11/20 11:17:46 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd > 0)
		write(fd, &c, 1);
}
/*
#include <stdio.h>

int	main(void){
	int fd1 = open("haji.txt", O_RDWR | O_CREAT, 0644);
	printf("%i", fd1);
	ft_putchar_fd('0', fd1);
	close(fd1);
	return (0);
}*/
