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
static int	adding_exp(t_list **tmp_exp, char *var_name, char *new_var, int *flag1,t_list **export_list);
 
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
		if(adding_exp(&tmp_exp, var_name, new_var, &flag, export_list) == 1)
			return ;
		tmp_exp = tmp_exp->next;
	}
	if (value == 1)
		ft_lstadd_back(env, m_lstnew(new_var));
	if (flag == 1)
		ft_lstadd_back(export_list, m_lstnew(new_var));
}

void del_node(t_list **head, t_list *node)
{
    t_list *temp = *head;
    t_list *prev = NULL;

    while (temp != NULL)
   {
	if(ft_strcmp(temp->next->content, node->content) == 0)
	{
		prev = temp->next;
		temp->next = temp->next->next;
		free(prev->content);
		free(prev);
		return;
	}
	temp = temp->next;
   }
}

int	adding_exp(t_list **tmp_exp, char *var_name, char *new_var, int *flag1, t_list **export_list)
{
	t_list	*tmp;
	char *var_name1;	

	tmp = *tmp_exp;
	var_name1 = m_substr(tmp->content, 0, ft_lengh_word(tmp->content));
	if (var_name && ft_strcmp(var_name1, var_name) == 0)
	{
		*flag1 = 0;
		del_node(export_list, tmp);
		ft_lstadd_back(export_list, ft_lstnew(new_var));
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

