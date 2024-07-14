/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:56:11 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 15:56:13 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	close_free(t_fd **head)
{
	t_fd	*temp;

	if (!*head)
		return (0);
	while (*head)
	{
		temp = *head;
		*head = (*head)->next;
		close(temp->fd);
		free(temp);
	}
	return (0);
}

t_fd	*ft_new_fd(int fd)
{
	t_fd	*new_node;

	new_node = (t_fd *)malloc(sizeof(t_fd));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->next = NULL;
	return (new_node);
}

void	ft_addback_fd(t_fd **head, t_fd *new_node)
{
	t_fd	*temp;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void	redirection(t_parse **parse)
{
	t_parse	*temp;
	t_redir	*temp_redir;

	temp = *parse;
	while (temp)
	{
		temp_redir = temp->redir_list;
		while (temp_redir)
		{
			if (temp_redir->type == REDIR_IN)
			{
				temp->red_in = open(temp_redir->filename, O_RDONLY);
				ft_addback_fd(&temp->fd_head, ft_new_fd(temp->red_in));
			}
			else if (temp_redir->type == REDIR_OUT)
			{
				temp->red_out = open(temp_redir->filename,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
				ft_addback_fd(&temp->fd_head, ft_new_fd(temp->red_out));
			}
			else if (temp_redir->type == REDIR_APPEND)
			{
				temp->red_out = open(temp_redir->filename,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
				ft_addback_fd(&temp->fd_head, ft_new_fd(temp->red_out));
			}
			temp_redir = temp_redir->next;
		}
		temp = temp->next;
	}
}
