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

int check_Parenthesis(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')')
			count++;
		i++;
	}
	if (count != 0)
	{
		print_error("syntax error near unexpected token Parenthesis\n");
		g_global->exit_status = 2;
		return (-1);
	}
	return (0);
}

int	syntax_redirections(t_token **current)
{
	if ((*current)->type == TOKEN_OUT || (*current)->type == TOKEN_APPEND \
		|| (*current)->type == TOKEN_IN || (*current)->type == TOKEN_HERE)
	{
		if (!(*current)->next || (*current)->next->type != TOKEN_WORD)
		{
			print_error("Syntax error  invalid redirection\n");
			g_global->exit_status = 2;
			return (-1);
		}
	}
	if((*current)->type == TOKEN_WORD && check_Parenthesis((*current)->value) < 0)
		return (-1);
	return (0);
}

int	check_syntax_errors(t_token **head)
{
	t_token	*current;

	current = *head;
	if (current && current->type == TOKEN_PIPE)
	{
		print_error("syntax error near unexpected token pipes\n");
		g_global->exit_status = 2;
		return (-1);
	}
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!current->next || current->next->type == TOKEN_PIPE)
			{
				print_error("syntax error near unexpected token pipes\n");
				g_global->exit_status = 2;
				return (-1);
			}
		}
		else if (syntax_redirections(&current) < 0)
			return (-1);
		current = current->next;
	}
	return (0);
}
