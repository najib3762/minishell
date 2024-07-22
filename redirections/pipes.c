/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:54:04 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/19 11:35:38 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fd_pipe(t_mini *prog)
{
	int	**fd;
	int	i;

	i = 0;
	if (prog->fd == NULL)
		return ;
	fd = prog->fd;
	while (fd[i])
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	free_fd_pipe(t_mini *prog)
{
	int	**fd;
	int	i;

	i = 0;
	if (prog->fd == NULL)
		return ;
	fd = prog->fd;
	while (fd[i])
	{
		free(fd[i]);
		i++;
	}
	free(fd);
	prog->fd = NULL;
}

int	set_pipe_fd(t_mini *prog, t_parse **parse)
{
	int		**fd_arr;
	t_parse	*temp;
	int		i;

	i = 1;
	if (prog->fd == NULL)
		return (0);
	fd_arr = prog->fd;
	temp = *parse;
	temp->red_out = fd_arr[0][1];
	temp = temp->next;
	while (fd_arr[i])
	{
		temp->red_in = fd_arr[i - 1][0];
		temp->red_out = fd_arr[i][1];
		temp = temp->next;
		i++;
	}
	temp->red_in = fd_arr[i - 1][0];
	return (0);
}

int	create_multiple_pipe(t_parse **parse, t_mini *prog)
{
	t_parse	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = *parse;
	i = prog->nbr_cmd;
	if (i == 1 || i == 0)
		return (prog->fd = NULL, 0);
	prog->fd = (int **)malloc(sizeof(int *) * i);
	addback_node_free(&g_global->address, newnode_free(prog->fd));
	if (!prog->fd)
		return (-1);
	while (j < i - 1)
	{
		prog->fd[j] = (int *)malloc(sizeof(int) * 2);
		addback_node_free(&g_global->address, newnode_free(prog->fd[j]));
		if (!prog->fd[j])
			return (-1);
		pipe(prog->fd[j++]);
	}
	return (prog->fd[j] = NULL, 0);
}
