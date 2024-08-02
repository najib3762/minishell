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

void	executer_utils(t_mini *prog, t_parse *cmd)
{
	t_global	*g_global;

	g_global = global_function();
	(void)cmd;
	close_fd_pipe(prog);
	free_fd_pipe(prog);
	close_free(&prog->fd_head);
	if (prog->last_pid == 0)
		return ;
	waitpid(prog->last_pid, &g_global->exit_status, 0);
	if (WIFEXITED(g_global->exit_status))
		g_global->exit_status = WEXITSTATUS(g_global->exit_status);
	else if (WIFSIGNALED(g_global->exit_status))
		g_global->exit_status = WTERMSIG(g_global->exit_status) + 128;
	while (wait(NULL) > 0)
	{
	}
}

void	g_word2(char *str, char *eof)
{
	int	dflag;
	int	sflag;
	int	i;
	int	j;

	dflag = 0;
	sflag = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\"' && sflag == 0 && ++i)
			dflag = !dflag;
		else if (str[i] == '\'' && dflag == 0 && ++i)
			sflag = !sflag;
		else
			eof[j++] = str[i++];
	}
	eof[j] = '\0';
}

char	*skip_quotes2(char *str)
{
	t_global	*g_global;
	char	*eof;
	int		len;
	int		qoutes;

	if (!str)
		return (NULL);
	g_global = global_function();
	qoutes = calcule_qoutes(str);
	len = ft_strlen(str) - qoutes;
	eof = malloc(sizeof(char) * (len + 1));
	if (!eof)
	{
		perror("malloc");
		return (NULL);
	}
	addback_node_free(&g_global->address, newnode_free(eof));
	g_word2(str, eof);
	return (eof);
}
