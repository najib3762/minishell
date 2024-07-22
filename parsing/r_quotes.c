/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:52:34 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 15:52:36 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	r_quotes(t_parse **head)
{
	t_parse	*temp;
	t_args	*temp_args;
	t_redir	*temp_redir;

	temp = *head;
	while (temp)
	{
		temp_args = temp->cmd_args;
		while (temp_args)
		{
			if (check_qoutes(temp_args->content))
				temp_args->content = skip_quotes(temp_args->content);
			temp_args = temp_args->next;
		}
		temp_redir = temp->redir_list;
		while (temp_redir)
		{
			if (check_qoutes(temp_redir->filename))
				temp_redir->filename = skip_quotes(temp_redir->filename);
			temp_redir = temp_redir->next;
		}
		temp = temp->next;
	}
}
