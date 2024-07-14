/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:51:37 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 15:51:38 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_env(char **env, t_list **head)
{
	int	i;

	i = 0;
	while (env[i])
		ft_lstadd_back(head, ft_lstnew(env[i++]));
}

void	init_data(int ac, char **env, t_mini *prog)
{
	prog->line = NULL;
	prog->env_head = NULL;
	if (ac != 1)
		exit(1);
	get_env(env, &prog->env_head);
}
