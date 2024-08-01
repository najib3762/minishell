/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:16:27 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 18:16:28 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_address(t_free **head)
{
	t_free	*temp;

	while (*head)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->address);
		free(temp);
	}
	*head = NULL;
}

t_free	*newnode_free(void *content)
{
	t_free	*new;

	new = malloc(sizeof(t_free));
	if (!new)
	{
		perror("malloc");
		return (NULL);
	}
	new->address = content;
	new->next = NULL;
	return (new);
}

void	addback_node_free(t_free **head, t_free *new)
{
	t_free	*temp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
