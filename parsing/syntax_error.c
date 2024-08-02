/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 11:53:32 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 11:53:33 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_redirections(t_token **current)
{
	t_global	*g_global;

	g_global = global_function();
	if ((*current)->type == TOKEN_OUT || (*current)->type == TOKEN_APPEND
		|| (*current)->type == TOKEN_IN || (*current)->type == TOKEN_HERE)
	{
		if (!(*current)->next || (*current)->next->type != TOKEN_WORD)
		{
			print_error("Syntax error  invalid redirection\n");
			g_global->exit_status = 2;
			return (-1);
		}
	}
	return (0);
}

int	check_syntax_errors(t_token **head)
{
	t_token		*current;
	t_global	*g_global;

	current = *head;
	g_global = global_function();
	if (current && current->type == TOKEN_PIPE)
	{
		print_error("syntax error near unexpected token pipes\n");
		return (g_global->exit_status = 2, -1);
	}
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!current->next || current->next->type == TOKEN_PIPE)
			{
				print_error("syntax error near unexpected token pipes\n");
				return (g_global->exit_status = 2, -1);
			}
		}
		else if (syntax_redirections(&current) < 0)
			return (-1);
		current = current->next;
	}
	return (0);
}
