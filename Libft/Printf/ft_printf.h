/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:25:18 by mlamrani          #+#    #+#             */
/*   Updated: 2023/12/15 14:47:33 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>

# define STRL "0123456789abcdef"
# define STRU "0123456789ABCDEF"

int		ft_printf(const char *format, ...);
void	p_char(int c, int *count);
void	p_str(char *s, int *count);
void	p_num(int nb, int *count);
void	p_unum(unsigned int nb, int *count);
void	p_hexl(unsigned long n, int *count, bool a);
// void	p_hexu(size_t n, int *count, bool a);
void	p_add(unsigned long p, int *count);

#endif