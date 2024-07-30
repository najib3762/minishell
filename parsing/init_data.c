/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:51:37 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/19 10:36:35 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_env(char **env, t_list **head)
{
	int	i;

	i = 0;
	if (env[0] == NULL)
	{
		g_global->env_null = 1;
		ft_lstadd_back(head, m_lstnew(ENV1));
		ft_lstadd_back(head, m_lstnew(ENV2));
		ft_lstadd_back(head, m_lstnew(ENV3));
		ft_lstadd_back(head, m_lstnew(m_strjoin("PATH=", ENV4)));
		return ;
	}
	while (env[i])
		ft_lstadd_back(head, m_lstnew(env[i++]));
}

void	export_env(char **env, t_list **head)
{
	int	i;

	i = 0;
	if (env[0] == NULL)
	{
		ft_lstadd_back(head, m_lstnew(ENV1));
		ft_lstadd_back(head, m_lstnew(ENV2));
		ft_lstadd_back(head, m_lstnew(ENV3));
		return ;
	}
	while (env[i])
		ft_lstadd_back(head, m_lstnew(env[i++]));
}

void	init_data(int ac, char **env, t_mini *prog)
{
	prog->line = NULL;
	prog->env_head = NULL;
	prog->fd_head = NULL;
	prog->export_head = NULL;
	prog->fd = NULL;
	prog->env = NULL;
	prog->path = NULL;
	prog->last_pid = 0;
	prog->nbr_cmd = 0;
	if (ac != 1)
		exit(1);
	g_global = malloc(sizeof(t_global));
	if (!g_global)
		exit(1);
	g_global->exit_status = 0;
	g_global->is_true = 0;
	g_global->env_null = 0;
	g_global->address = NULL;
	get_env(env, &prog->env_head);
	export_env(env, &prog->export_head);
}
