/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:25:42 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/22 20:25:43 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_redir_in(t_redir *redir, t_parse *temp, t_mini *prog)
{
	temp->red_in = open(redir->filename, O_RDONLY);
	if (temp->red_in < 0)
	{
		perror("minishell");
		g_global->exit_status = 1;
		temp->is_false = 1;
		return (-1);
	}
	ft_addback_fd(&prog->fd_head, ft_new_fd(temp->red_in));
	return (0);
}

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
	addback_node_free(&g_global->address, newnode_free(new_node));
	new_node->fd = fd;
	new_node->next = NULL;
	return (new_node);
}

void	ft_addback_fd(t_fd **head, t_fd *new_node)
{
	t_fd	*temp;

	if (!*head || !new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}
