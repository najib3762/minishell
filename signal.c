/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:06:05 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/18 09:16:00 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint2(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	handle_sigquit(int sig)
{
	(void)sig;
	ft_putendl_fd("Quit (core dumped)", 2);
}

void	handle_sigint1(int sig)
{
	(void)sig;
	t_global	*g_global;
	
	g_global = global_function();
	g_global->exit_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	ft_lengh_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i + 1);
}
