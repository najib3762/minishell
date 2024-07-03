/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_add.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:00:50 by mlamrani          #+#    #+#             */
/*   Updated: 2023/12/15 11:49:42 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	p_add(unsigned long p, int *count)
{
	if (!p)
	{
		write(1, "(nil)", 5);
		*count += 5;
		return ;
	}
	p_str("0x", count);
	p_hexl(p, count, true);
}
