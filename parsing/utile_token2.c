/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_token2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 11:52:55 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 11:52:56 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

t_token	*create_newnode(t_type new_type, char *new_value)
{
	t_token	*ptr;

	ptr = malloc(sizeof(t_token));
	if (!ptr)
	{
		perror("malloc");
		return (NULL);
	}
	ptr->type = new_type;
	ptr->value = new_value;
	ptr->next = NULL;
	return (ptr);
}

void	addback_node(t_token **head, t_token *new_node)
{
	t_token	*current;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}

int	check_quotes(t_mini *prog)
{
	int		i;
	char	quote;
	int		res;

	quote = '\0';
	res = 1;
	i = 0;
	while (prog->line[i])
	{
		if (prog->line[i] == '"' || prog->line[i] == '\'')
		{
			if (quote == '\0')
				quote = prog->line[i];
			else if (prog->line[i] == quote)
				quote = '\0';
		}
		i++;
	}
	if (quote != '\0')
	{
		print_error("Syntax error quotes\n");
		res = 0;
	}
	return (res);
}

int	free_token_list(t_token **head)
{
	t_token	*tmp;

	while (*head != NULL)
	{
		tmp = NULL;
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
	*head = NULL;
	return (0);
}
