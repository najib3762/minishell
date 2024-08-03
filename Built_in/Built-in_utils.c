/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built-in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:41:16 by mlamrani          #+#    #+#             */
/*   Updated: 2024/08/02 13:17:11 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int adding_exp(t_list **tmp_exp, t_exp_args *args, int *flag1, t_list **export_list);

void init_exp_args(t_list **export_list, char *var_name, char *new_var, t_exp_args *args)
{
    args->var_name = var_name;
    args->new_var = new_var;
	args->export_list = export_list;
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
	tmp = *export_list;
	while (tmp)
	{
		if (adding_exp(&tmp, &args, &flag, export_list) == 1)
			break;
		tmp = tmp->next;
	}
	if (value == 1)
        ft_lstadd_back(env, m_lstnew(new_var));
    if (flag == 1)
        ft_lstadd_back(export_list, m_lstnew(new_var));
}

void	del_node(t_list **head, t_list *node)
{
	t_list	*temp;
	t_list	*prev;

	temp = *head;
	prev = NULL;
	while (temp != NULL)
	{
	if(ft_strcmp(temp->next->content, node->content) == 0)
	{
		prev = temp->next;
		temp->next = temp->next->next;
		prev = NULL;
		return;
	}
	temp = temp->next;
		if (ft_strcmp(temp->next->content, node->content) == 0)
		{
			prev = temp->next;
			temp->next = temp->next->next;
			prev = NULL;
			return ;
		}
		temp = temp->next;
	}
}

int adding_exp(t_list **tmp_exp, t_exp_args *args, int *flag1, t_list **export_list)
{
	t_list *tmp;
	char *var_name1;
	int len;

	len = 0;
    tmp = *tmp_exp;
	len =  ft_lengh_word(tmp->content);
    var_name1 = m_substr(tmp->content, 0, len);
    if (args->var_name && ft_strncmp(var_name1, args->var_name, ft_strlen(var_name1)) == 0)
    {
        *flag1 = 0;
        del_node(export_list, tmp);
        ft_lstadd_back(export_list, ft_lstnew(args->new_var));
        return (1);
    }
    return (0);
}

void	adding_env(t_list **tmp, char *var_name, char *new_var, int *value)
{
	t_list	*t;

	t = *tmp;
	if (var_name && ft_strnstr(t->content, var_name, ft_strlen(var_name)))
	{
		*value = 0;
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


