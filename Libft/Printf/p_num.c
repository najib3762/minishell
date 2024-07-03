/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_num.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:52:53 by mlamrani          #+#    #+#             */
/*   Updated: 2023/12/15 14:49:03 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	p_num(int nb, int *count)
{
	if (nb == -2147483648)
	{
		p_str("-2147483648", count);
	}
	else if (nb < 0)
	{
		p_char('-', count);
		nb = -nb;
		p_num(nb, count);
	}
	else if (nb > 9)
	{
		p_num(nb / 10, count);
		p_num(nb % 10, count);
	}
	else
		p_char(nb + 48, count);
}

void	p_unum(unsigned int n, int *count)
{
	if (n > 9)
	{
		p_unum(n / 10, count);
		p_unum(n % 10, count);
	}
	else
		p_char(n + 48, count);
}
