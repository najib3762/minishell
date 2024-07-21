/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:40:31 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 15:40:32 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_redir_node(t_redir **list, t_redir *new_node)
{
	t_redir	*temp;

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

void	add_cmd_node(t_parse **list, t_parse *new_node)
{
	t_parse	*temp;

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

void	parse_redirection(t_token **temp, t_redir **redir)
{
	if ((*temp)->type == TOKEN_IN)
	{
		add_redir_node(redir, redir_node((*temp)->next->value, REDIR_IN));
		*temp = (*temp)->next->next;
	}
	else if ((*temp)->type == TOKEN_OUT)
	{
		add_redir_node(redir, redir_node((*temp)->next->value, REDIR_OUT));
		*temp = (*temp)->next->next;
	}
	else if ((*temp)->type == TOKEN_APPEND)
	{
		add_redir_node(redir, redir_node((*temp)->next->value, REDIR_APPEND));
		*temp = (*temp)->next->next;
	}
	else if ((*temp)->type == TOKEN_HERE)
	{
		add_redir_node(redir, redir_node((*temp)->next->value, REDIR_HERE));
		*temp = (*temp)->next->next;
	}
}

void	parse_token(t_token **temp, t_args **args, t_redir **redir)
{
	while (*temp && (*temp)->type != TOKEN_PIPE)
	{
		if ((*temp)->type == TOKEN_IN || (*temp)->type == TOKEN_OUT
			|| (*temp)->type == TOKEN_APPEND || (*temp)->type == TOKEN_HERE)
			parse_redirection(temp, redir);
		else
		{
			word_token2(args, (*temp)->value);
			*temp = (*temp)->next;
		}
	}
}

void	parse_input(t_token **tokens, t_parse **parse)
{
	t_parse	*cmd_head;
	t_token	*temp;
	t_args	*args;
	t_redir	*redir;

	cmd_head = NULL;
	temp = *tokens;
	while (temp)
	{
		args = NULL;
		redir = NULL;
		parse_token(&temp, &args, &redir);
		add_cmd_node(&cmd_head, cmd_node(args, redir));
		if (temp && temp->type == TOKEN_PIPE)
			temp = temp->next;
	}
	*parse = cmd_head;
}
