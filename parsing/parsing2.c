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
	t_args		*node;
	t_global	*g_global;

	g_global = global_function();
	node = (t_args *)malloc(sizeof(t_args));
	if (!node)
		return (NULL);
	addback_node_free(&g_global->address, newnode_free(node));
	node->content = m_strdup(content);
	node->next = NULL;
	return (node);
}

t_redir	*redir_node(char *filename, t_redir_enum type)
{
	t_redir		*node;
	t_global	*g_global;

	g_global = global_function();
	node = (t_redir *)malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	addback_node_free(&g_global->address, newnode_free(node));
	node->filename = m_strdup(filename);
	node->type = type;
	node->next = NULL;
	return (node);
}

t_parse	*cmd_node(t_args *cmd_args, t_redir *redir_list)
{
	t_parse		*node;
	t_global	*g_global;

	g_global = global_function();
	node = (t_parse *)malloc(sizeof(t_parse));
	if (!node)
		return (NULL);
	addback_node_free(&g_global->address, newnode_free(node));
	node->cmd_args = cmd_args;
	node->redir_list = redir_list;
	node->red_in = 0;
	node->red_out = 1;
	node->is_false = 0;
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
