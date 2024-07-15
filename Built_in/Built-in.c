/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:51:42 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/15 18:20:13 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// t_args	*ft_lstnew(void *content)
// {
// 	t_args	*node;

// 	node = malloc(sizeof(t_args));
// 	if (!node)
// 		return (NULL);
// 	node->content = content;
// 	node->next = NULL;
// 	return (node);
// }

// void	ft_lstadd_back(t_args **lst, t_args *new)
// {
// 	t_args	*last;

// 	if (!lst || !new)
// 		return ;
// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	last = *lst;
// 	while (last->next)
// 		last = last->next;
// 	last->next = new;
// }

char	*ft_pwd(int i)
{
	char	wd[1024];
	int		len;
	char	*cwd;

	cwd = getcwd(wd, sizeof(wd));
	if (i == 0 && cwd)
	{
		len = ft_strlen(cwd);
		printf("%s\n", cwd);
	}
	else
		return (cwd);
	return (NULL);
}

void	my_print_list(t_mini *head)
{
	while (head)
	{
		printf("%s\n", (char *)head->env_head->content);
		head = (t_mini *)head->env_head->next;
	}
}
void	sort_exp(t_mini **start)
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
		current = (*start)->env_head;
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

void	ft_export(t_mini **env, t_mini **export_list, t_parse **cmd)
{
	char	*new_var;
	t_mini	*tmp;
	char *var_name;
	char *var_value;
	char *equal;
	int		flag;
	t_args *cur;

	cur = cmd->cmd_args;
	if (!ft_strncmp(cur->content, "export", 7))
		cur = cur->next;
	var_name = NULL;
	var_value = NULL;
	if (cur && cur->content)
	{
		equal = ft_strchr(cur->content, '=');
		if (equal)
		{
			var_name = ft_substr(cur->content, 0, equal - cur->content);
			var_value = ft_strdup(equal + 1);
		}
		else
			var_name = ft_strdup(cur->content);
	}
	if (!var_name && !var_value)
	{
		sort_exp(env);
		my_print_list(*env);
		return ;
	}
	if (var_name && !var_value)
	{
		tmp = *export_list;
		while (tmp)
		{
			if (!ft_strncmp(tmp->env_head->content, var_name, ft_strlen(var_name)))
				return ;
			tmp = (t_mini *)tmp->env_head->next;
		}
		ft_lstadd_back((t_list **)export_list, ft_lstnew(strdup(var_name)));
		return ;
	}
	if (var_name && var_value)
	{
		new_var = ft_strjoin(var_name, var_value);
		tmp = *env;
		flag = 1;
		while (tmp)
		{
			if (!ft_strncmp(tmp->env_head->content, var_name, ft_strlen(var_name)))
			{
				flag = 0;
				free(tmp->env_head->content);
				tmp->env_head->content = new_var;
			}
			tmp = (t_mini *)tmp->env_head->next;
		}
		if (flag == 1)
			ft_lstadd_back((t_list **)env, ft_lstnew(new_var));
		else
			free(new_var);
	}
}

// void	append_node(t_args **head, char *content)
// {
// 	t_args	*new_node;
// 	t_args	*temp;

// 	new_node = ft_lstnew(content);
// 	if (!new_node)
// 		return ;
// 	temp = *head;
// 	if (!*head)
// 	{
// 		*head = new_node;
// 		return ;
// 	}
// 	while (temp->next)
// 		temp = temp->next;
// 	temp->next = new_node;
// }
// t_args	*set_env(char **env)
// {
// 	t_args	*env_list;

// 	env_list = NULL;
// 	while (*env)
// 	{
// 		append_node(&env_list, ft_strdup(*env));
// 		env++;
// 	}
// 	return (env_list);
// }
