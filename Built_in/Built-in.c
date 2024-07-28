/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:51:42 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/19 11:20:27 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_pwd(int i, t_parse *cmd)
{
	char	wd[1024];
	int		len;
	char	*cwd;

	cwd = getcwd(wd, sizeof(wd));
	if (i == 0 && cwd)
	{
		len = ft_strlen(cwd);
		ft_putendl_fd( cwd, cmd->red_out);
	}
	else
		return (cwd);
	return (NULL);
}

void	my_print_list(t_list *head, t_parse *cmd)
{
	while (head)
	{
		ft_putendl_fd(ft_strjoin("declare -x ",(char *)head->content), cmd->red_out);
		head = head->next;
	}
}

void	sort_exp(t_list **start)
{
	int		swapped;
	char	*temp;
	t_list	*current;
	t_list	*last;

	last = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *start;
		while (current->next != last)
		{
			if (ft_strcmp(current->content, current->next->content) > 0)
			{
				temp = current->content;
				current->content = current->next->content;
				current->next->content = temp;
				swapped = 1;
			}
			current = current->next;
		}
		last = current;
	}
}

void	ft_export(t_list **env, t_list **export_list, t_parse *cmd)
{
	char	*var;
	char 	*equal;
	char	*var_name;
	char	*var_value;
	t_args 	*cur;


	var_name = NULL;
	var_value = NULL;
	cur = cmd->cmd_args;
	if (!ft_strncmp(cur->content, "export", 7))
		cur = cur->next;
	if (cur && cur->content)
	{
		equal = ft_strchr(cur->content, '=');
		if (equal)
		{
			var_name = m_substr(cur->content, 0, equal - cur->content + 1);
			var = m_substr(cur->content, 0, equal - cur->content);
			var_value = m_strdup(equal + 1);
		}
		else
			var_name = m_strdup(cur->content);
	}
	if (!var_name)
	{
		sort_exp(export_list);
		my_print_list(*export_list, cmd);
		return;
	}
	add_to_exp(var_name, var_value, env, export_list);
}
void add_to_exp(char *var_name, char *var_value, t_list **env, t_list **export_list)
{
	if (var_name && !var_value) //adding variable to the export list
        add_var(*export_list, var_name, export_list);
	if (var_name && var_value) //adding the variable and the value to env and export list
		adding(*env, export_list, var_name, var_value, env);
}
