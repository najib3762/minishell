/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built-in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:41:16 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/31 19:07:44 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	adding(t_list **env, t_list **export_list, char *var_name,
		char *var_value)
{
	char	*new_var;
	t_list	*tmp_exp;
	int		flag;
	t_list	*tmp;
	int		value;

	tmp = *env;
	tmp_exp = *export_list;
	new_var = m_strjoin(var_name, var_value);
	flag = 1;
	value = 1;
	while (tmp)
	{
		adding_env(&tmp, var_name, new_var, &value);
		tmp = tmp->next;
	}
	while (tmp_exp)
	{
		adding_exp(&tmp_exp, var_name, new_var, &flag);
		tmp_exp = tmp_exp->next;
	}
	if (value == 1)
		ft_lstadd_back(env, m_lstnew(new_var));
	if (flag == 1)
		ft_lstadd_back(export_list, m_lstnew(new_var));
}

void	adding_exp(t_list **tmp_exp, char *var_name, char *new_var, int *flag1)
{
	t_list	*tmp;
	char	**var;

	tmp = *tmp_exp;
	var = ft_split(var_name, '=');
	if (var_name && ft_strnstr(tmp->content, *var, ft_strlen(var_name)))
	{
		*flag1 = 0;
		free(tmp->content);
		tmp->content = new_var;
	}
}
void	adding_env(t_list **tmp, char *var_name, char *new_var, int *value)
{
	t_list	*t;

	t = *tmp;
	if (var_name && ft_strnstr(t->content, var_name, ft_strlen(var_name)))
	{
		*value = 0;
		free(t->content);
		t->content = new_var;
	}
}

void	add_var(t_list *tmp, char *var_name, t_list **export_list)
{
	while (tmp)
	{
		if (ft_strnstr((char *)tmp->content, var_name, ft_strlen(var_name)))
			return ;
		tmp = tmp->next;
	}
	ft_lstadd_back(export_list, ft_lstnew(m_strdup(var_name)));
	return ;
}

