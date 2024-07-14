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

void	r_quotes(t_token **head)
{
	t_token	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->type == TOKEN_WORD)
		{
			if (check_qoutes(temp->value))
				temp->value = skip_quotes(temp->value);
		}
		temp = temp->next;
	}
}
