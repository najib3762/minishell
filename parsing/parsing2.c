/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:50:19 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 15:50:21 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_args	*args_node(char *content)
{
	t_args	*node;

	node = (t_args *)malloc(sizeof(t_args));
	addback_node_free(&g_global->address, newnode_free(node));
	if (!node)
		return (NULL);
	node->content = m_strdup(content);
	node->next = NULL;
	return (node);
}

t_redir	*redir_node(char *filename, t_redir_enum type)
{
	t_redir	*node;

	node = (t_redir *)malloc(sizeof(t_redir));
	addback_node_free(&g_global->address, newnode_free(node));
	if (!node)
		return (NULL);
	node->filename = m_strdup(filename);
	node->type = type;
	node->next = NULL;
	return (node);
}

t_parse	*cmd_node(t_args *cmd_args, t_redir *redir_list)
{
	t_parse	*node;

	node = (t_parse *)malloc(sizeof(t_parse));
	addback_node_free(&g_global->address, newnode_free(node));
	if (!node)
		return (NULL);
	node->cmd_args = cmd_args;
	node->redir_list = redir_list;
	node->red_in = 0;
	node->red_out = 1;
	node->next = NULL;
	return (node);
}

void	add_args_node(t_args **list, t_args *new_node)
{
	t_args	*temp;

	if (!*list)
		*list = new_node;
	else
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}
