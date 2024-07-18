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
		ft_lstadd_back(head, m_lstnew(env[i++]));
}

void	init_data(int ac, char **env, t_mini *prog)
{
	prog->line = NULL;
	prog->env_head = NULL;
	prog->fd_head = NULL;
	if (ac != 1)
		exit(1);
    g_global = malloc(sizeof(t_global));
	if (!g_global)
		exit(1);
	g_global->exit_status = 0;
	g_global->address = NULL;
	get_env(env, &prog->env_head);
}
