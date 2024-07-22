/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:56:11 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/15 12:15:21 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_redir_out(char *file_name, t_parse *temp, t_mini *prog)
{
	temp->red_out = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp->red_out < 0)
	{
		perror("minishell");
		g_global->exit_status = 1;
		return (-1);
	}
	ft_addback_fd(&prog->fd_head, ft_new_fd(temp->red_out));
	return (0);
}

int	handle_redir_append(char *file_name, t_parse *temp, t_mini *prog)
{
	temp->red_out = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (temp->red_out < 0)
	{
		perror("minishell");
		g_global->exit_status = 1;
		return (-1);
	}
	ft_addback_fd(&prog->fd_head, ft_new_fd(temp->red_out));
	return (0);
}

int	process_redir(t_redir *temp_redir, t_parse *temp, t_mini *prog)
{
	if (g_global->is_true == 1)
	{
		print_error("minishell: ambiguous redirect\n");
		g_global->is_true = 0;
		g_global->exit_status = 1;
		return (-1);
	}
	if (temp_redir->type == REDIR_IN && handle_redir_in(temp_redir, temp,
			prog) < 0)
		return (-1);
	if (temp_redir->type == REDIR_OUT && handle_redir_out(temp_redir->filename,
			temp, prog) < 0)
		return (-1);
	if (temp_redir->type == REDIR_APPEND
		&& handle_redir_append(temp_redir->filename, temp, prog) < 0)
		return (-1);
	return (0);
}

int	handle_redirection(t_parse *temp, t_mini *prog)
{
	t_redir	*temp_redir;

	temp_redir = temp->redir_list;
	while (temp_redir)
	{
		if (process_redir(temp_redir, temp, prog) < 0)
			return (-1);
		temp_redir = temp_redir->next;
	}
	return (0);
}

int	redirection(t_parse **parse, t_mini *prog)
{
	t_parse	*temp;

	temp = *parse;
	while (temp)
	{
		if (handle_redirection(temp, prog) < 0)
			return (-1);
		temp = temp->next;
	}
	return (0);
}
