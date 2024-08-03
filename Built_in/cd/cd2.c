/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:01:40 by mlamrani          #+#    #+#             */
/*   Updated: 2024/08/03 17:24:03 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_env_old(t_list **env, char *name, t_list **export_list)
{
	t_list	*tmp;
	size_t	name_len;
	char	*pwd_content;

	name_len = ft_strlen(name);
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
		if (!ft_strncmp((char *)tmp->content, name, name_len)
			&& ((char *)(tmp->content))[name_len] == '=')
			tmp->content = m_strjoin("OLDPWD=", pwd_content);
		tmp = tmp->next;
	}
	if (tmp)
		ft_lstadd_back(env, m_lstnew(pwd_content));
	update_export_list_with_old(export_list, name, pwd_content);
}

void update_export_list_with_old(t_list **export_list, char *name, char *pwd_content)
{
    t_list *tmp;
    size_t name_len;

	tmp = *export_list;
	name_len = ft_strlen(name);
    while (tmp)
    {
        if (!ft_strncmp((char *)tmp->content, name, name_len) && ((char *)(tmp->content))[name_len] == '=')
        {
            tmp->content = m_strjoin("OLDPWD=", pwd_content);
            return;
        }
        tmp = tmp->next;
    }
    ft_lstadd_back(export_list, m_lstnew(pwd_content));
}

char	*g_env(t_list *env, char *str)
{
	while (env)
	{
		if (ft_strnstr((char *)env->content, str, sizeof(env)))
			return (env->content);
		env = (env)->next;
	}
	return (NULL);
}
