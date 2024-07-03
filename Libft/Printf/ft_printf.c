/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:24:39 by mlamrani          #+#    #+#             */
/*   Updated: 2023/12/15 14:50:21 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	mini_printf(char specifer, va_list list, int *count)
{
	if (specifer == 'c')
		p_char(va_arg(list, int), count);
	else if (specifer == 's')
		p_str(va_arg(list, char *), count);
	else if (specifer == 'd' || specifer == 'i')
		p_num(va_arg(list, int), count);
	else if (specifer == 'u')
		p_unum(va_arg(list, unsigned int), count);
	else if (specifer == 'x')
		p_hexl(va_arg(list, unsigned int ), count, true);
	else if (specifer == 'X')
		p_hexl(va_arg(list, unsigned int ), count, false);
	else if (specifer == 'p')
		p_add(va_arg(list, unsigned long ), count);
	else if (specifer == '%')
		p_char('%', count);
	else
		p_char(specifer, count);
	return (*count);
}

int	ft_printf(const char *format, ...)
{
	va_list	list;
	int		count;
	int		i;

	i = 0;
	count = 0;
	va_start(list, format);
	if (!format || (format[i] == '%' && format[i + 1] == '\0'))
		return (-1);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] == '\0')
			return (-1);
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			mini_printf(format[i + 1], list, &count);
			i++;
		}
		else
			p_char(format[i], &count);
		i++;
	}
	va_end(list);
	return (count);
}
