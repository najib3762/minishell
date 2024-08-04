/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:09:06 by mlamrani          #+#    #+#             */
/*   Updated: 2024/08/04 12:31:10 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	adding_exp(t_list **tmp_exp, t_exp_args *args, int *flag1,
				t_list **export_list);

void	update_export_list(t_list **export_list, t_exp_args *args, int *flag)
{
	t_list	*tmp;

	tmp = *export_list;
	while (tmp)
	{
		if (adding_exp(&tmp, args, flag, export_list) == 1)
			break ;
		tmp = tmp->next;
	}
}

void	del_node(t_list **head, t_list *node)
{
	t_list	*temp;
	t_list	*prev;

	temp = *head;
	prev = NULL;
	if (temp != NULL && ft_strcmp(temp->content, node->content) == 0)
	{
		*head = temp->next;
		return ;
	}
	while (temp != NULL && ft_strcmp(temp->content, node->content) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
}

int	adding_exp(t_list **tmp_exp, t_exp_args *args, int *flag1,
		t_list **export_list)
{
	t_list	*tmp;
	char	*var_name1;
	int		len;

	len = 0;
	tmp = *tmp_exp;
	len = ft_lengh_word(tmp->content);
	var_name1 = m_substr(tmp->content, 0, len);
	if (args->var_name && ft_strncmp(var_name1, args->var_name,
			ft_strlen(var_name1)) == 0)
	{
		*flag1 = 0;
		del_node(export_list, tmp);
		ft_lstadd_back(export_list, m_lstnew(args->new_var));
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
