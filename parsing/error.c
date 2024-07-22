/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 11:51:38 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 11:51:39 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *error)
{
	write(2, error, strlen(error));
}

int	my_lstsize(t_args *lst)
{
	int		count;
	t_args	*p;

	count = 0;
	if (!lst)
		return (count);
	p = lst;
	while (p)
	{
		count++;
		p = p->next;
	}
	return (count);
}
