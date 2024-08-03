/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:20:32 by mlamrani          #+#    #+#             */
/*   Updated: 2024/08/03 15:06:59 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../minishell.h"
#include <stdio.h>

static int	len(int *nb)
{
	long	m;
	int		count;

	m = *nb;
	count = 0;
	if (m < 0 || m == 0)
	{
		m = -(m);
		count += 1;
	}
	while (m != 0)
	{
		m /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	x;
	long	l;
	char	*p;

	l = len(&n);
	x = n;
	p = (char *)malloc(l + 1);
	if (!p)
		return (0);
	addback_node_free(&g_global->address, newnode_free(p));
	if (x < 0)
	{
		x *= -1;
		p[0] = '-';
	}
	if (n == 0)
		p[0] = '0';
	p[l] = '\0';
	while (x > 0)
	{
		p[l - 1] = (x % 10) + '0';
		x /= 10;
		l--;
	}
	return (p);
}
