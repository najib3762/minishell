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
	free_address(&g_global->address);
	write(1, "\n", 1);
}

void	handle_sigquit(int sig)
{
	(void)sig;
	free_address(&g_global->address);
	ft_putendl_fd("Quit (core dumped)", 2);
}

void	handle_sigint1(int sig)
{
	(void)sig;
	free_address(&g_global->address);
	g_global->exit_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
