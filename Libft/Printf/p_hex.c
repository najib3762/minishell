/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_hex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:08:28 by mlamrani          #+#    #+#             */
/*   Updated: 2023/12/15 14:49:30 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	p_hexl(unsigned long n, int *count, bool a)
{
	if (n > 15)
	{
		p_hexl((n / 16), count, a);
		p_hexl((n % 16), count, a);
	}
	else
	{
		if (a == true)
			p_char(STRL[n], count);
		else
			p_char(STRU[n], count);
	}
}
