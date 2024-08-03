/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:58:25 by mlamrani          #+#    #+#             */
/*   Updated: 2024/08/03 17:23:56 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd(t_parse *arg, t_list **env, t_list **export_list)
{
	t_args	*current;

	current = arg->cmd_args;
	if (my_lstsize(current) > 2)
	{
		g_global->exit_status = 1;
		return (ft_putendl_fd("cd: too many arguments", 2));
	}
	if (!ft_strncmp(current->content, "cd", 3))
		current = current->next;
	if (!current || !current->content)
		change_to_home(env);
	else if (chdir(current->content) < 0)
	{
		perror("cd");
		g_global->exit_status = 1;
	}
	update_pwd_and_oldpwd(env, export_list);
	if (g_global->exit_status != 0)
		return (1);
	return (g_global->exit_status = 0, 0);
}

void	change_to_home(t_list **env)
{
	char	*path;

	path = g_env(*env, "HOME=");
	if (path)
	{
		if (chdir(path + 5) < 0)
		{
			perror("cd");
			g_global->exit_status = 1;
		}
	}
	else
	{
		ft_putendl_fd("cd: HOME not set", 2);
		g_global->exit_status = 1;
	}
}

void	update_pwd_and_oldpwd(t_list **env, t_list **export_list)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (current_pwd)
	{
		set_env_old(env, "OLDPWD", export_list);
		set_env_pwd(env, export_list, current_pwd);
		free(current_pwd);
	}
	else
	{
		g_global->exit_status = 1;
	}
}

void	set_env_pwd(t_list **env, t_list **export_list, char *new_pwd)
{
	t_list	*tmp;
	size_t	name_len;
	char	*pwd_content;

	name_len = ft_strlen("PWD=");
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "PWD=", 4))
			pwd_content = m_substr(tmp->content, 4, ft_strlen(tmp->content)
					- 4);
		tmp = tmp->next;
	}
	tmp = *env;
	while (tmp)
	{
		if (strncmp(tmp->content, "PWD=", name_len) == 0)
			tmp->content = m_strjoin("PWD=", new_pwd);
		tmp = tmp->next;
	}
	if (tmp)
		ft_lstadd_back(env, m_lstnew(new_pwd));
	update_export_list_with_pwd(export_list, new_pwd);
}

void update_export_list_with_pwd(t_list **export_list, char *new_pwd)
{
    t_list *tmp;
    size_t name_len;
    
	tmp = *export_list;
	name_len = ft_strlen("PWD=");
    while (tmp)
    {
        if (ft_strncmp(tmp->content, "PWD=", name_len) == 0)
        {
            tmp->content = m_strjoin("PWD=", new_pwd);
            return;
        }
        tmp = tmp->next;
    }
    ft_lstadd_back(export_list, m_lstnew(new_pwd));
}
