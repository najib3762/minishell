/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:04:44 by mlamrani          #+#    #+#             */
/*   Updated: 2024/08/03 17:14:11 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export(t_mini *prog, t_parse *cmd, char *var_name, char *var_value)
{
	char	*equal;
	t_args	*cur;

	cur = cmd->cmd_args;
	while (cur)
	{
		if (cur->content)
		{
			if (check_dash(cur->content, 0))
				return ;
			equal = ft_strchr(cur->content, '=');
			check_equal(&var_name, &var_value, cur->content, equal);
			handle_plus_equal(&prog->env_head, &var_name, &var_value,
				cur->content);
			if (export_check(var_name, cur->content, prog))
				return ;
			add_to_exp(var_name, var_value, &prog->env_head,
				&prog->export_head);
		}
		cur = cur->next;
	}
	if (!var_name)
		p_exp(&prog->export_head, cmd);
	g_global->exit_status = 0;
}

void	add_to_exp(char *var_name, char *var_value, t_list **env,
		t_list **export_list)
{
	if (var_name && !var_value)
		add_var(*export_list, var_name, export_list);
	if (var_name && var_value)
		adding(env, export_list, var_name, var_value);
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

void	adding(t_list **env, t_list **export_list, char *var_name,
		char *var_value)
{
	char	*new_var;
	int		flag;
	t_list	*tmp;
	int		value;
	t_exp_args args;

	new_var = m_strjoin(var_name, var_value);
	flag = 1;
	value = 1;
	tmp = *env;
	init_exp_args(export_list, var_name, new_var, &args);
	while (tmp)
	{
		adding_env(&tmp, var_name, new_var, &value);
		tmp = tmp->next;
	}
	update_export_list(export_list, &args, &flag);
	if (value == 1)
        ft_lstadd_back(env, m_lstnew(new_var));
    if (flag == 1)
        ft_lstadd_back(export_list, m_lstnew(new_var));
}

void init_exp_args(t_list **export_list, char *var_name, char *new_var, t_exp_args *args)
{
    args->var_name = var_name;
    args->new_var = new_var;
	args->export_list = export_list;
}
