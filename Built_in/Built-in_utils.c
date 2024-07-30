/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built-in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:41:16 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/30 13:24:52 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void adding(t_list **env, t_list **export_list, char *var_name, char *var_value)
{
	char *new_var;
	char **var;
	t_list *tmp_exp;
	int flag;
	int *flag1;
	t_list *tmp;
	int value;
	
	var = ft_split(var_name, '=');
	tmp = *env;
	tmp_exp = *export_list;
	new_var = m_strjoin(var_name, var_value);
	flag = 1;
	value = 1;
	flag1 = &flag;
	while (tmp)
	{
		if (var_name && ft_strnstr(tmp->content, var_name, ft_strlen(var_name)))
		{
			value = 0;
			free(tmp->content);
			tmp->content = new_var;
		}
		tmp = tmp->next;
	}
	while (tmp_exp)
	{
		adding_exp(&tmp_exp, var_name, *var, new_var, flag1);
		tmp_exp = tmp_exp->next;
	}
	if (value == 1)
			ft_lstadd_back(env, ft_lstnew(new_var));
	if (*flag1 == 1)
		ft_lstadd_back(export_list, ft_lstnew(new_var));
}

void adding_exp(t_list **tmp_exp, char *var_name, char *var, char *new_var, int *flag1)
{
	t_list *tmp;

	tmp = *tmp_exp;
	if (var_name && ft_strnstr(tmp->content, var, ft_strlen(var_name)))
    {
		*flag1 = 0;
        free(tmp->content);
        tmp->content = new_var;
    }
}

void add_var(t_list *tmp, char *var_name, t_list **export_list)
{
	while (tmp)
	{
		if (ft_strnstr((char *)tmp->content, var_name, ft_strlen(var_name)))
			return;
		tmp = tmp->next;
	}
	ft_lstadd_back(export_list, ft_lstnew(m_strdup(var_name)));
	return;
}

int ft_isnumeric(char *str)
{
    if (str == NULL || *str == '\0')
        return (1);
    if (*str == '+' || *str == '-')
        str++;
    while (*str)
    {
        if (!ft_isdigit((unsigned char)*str))
            return (0);
        str++;
    }
    return (1);
}

char *add_quotes(char *str)
{
    int len;
    char *quoted_str; 

	len = strlen(str);
	quoted_str = malloc(len + 3); // 2 for quotes and 1 for null terminator
    if (!quoted_str)
        return NULL;
    quoted_str[0] = '"';
    ft_strcpy(quoted_str + 1, str);
    quoted_str[len + 1] = '"';
    quoted_str[len + 2] = '\0';

    return quoted_str;
}