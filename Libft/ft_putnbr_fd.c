/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:59:07 by mlamrani          #+#    #+#             */
/*   Updated: 2023/11/20 12:23:01 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

void	ft_putnbr_fd(int nb, int fd)
{
	if (fd > 0)
	{
		if (nb == -2147483648)
		{
			write(fd, "-2147483648", 11);
		}
		else if (nb < 0)
		{
			ft_putchar_fd('-', fd);
			nb = -nb;
			ft_putnbr_fd(nb, fd);
		}
		else if (nb > 9)
		{
			ft_putnbr_fd(nb / 10, fd);
			ft_putnbr_fd(nb % 10, fd);
		}
		else if (nb >= 0 && nb <= 9)
		{
			ft_putchar_fd(nb + '0', fd);
		}
	}
}
/*
#include <stdio.h>

int	main(void){
	int fd = open("ana.txt", O_RDWR | O_CREAT, 0644);
	printf("%d", fd);
	ft_putnbr_fd(-5, fd);
	close (fd);
}*/
