/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:07:29 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/26 12:07:31 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	nbr_args(t_args *args)
{
	int		i;
	t_args	*tmp;

	i = 0;
	tmp = args;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	executer_utils(t_mini *prog)
{
	close_fd_pipe(prog);
	free_fd_pipe(prog);
	close_free(&prog->fd_head);
	waitpid(prog->last_pid, &g_global->exit_status, 0);
	if (WIFEXITED(g_global->exit_status))
		g_global->exit_status = WEXITSTATUS(g_global->exit_status);
	while (wait(NULL) > 0)
	{
	}
}
