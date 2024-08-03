/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:42:47 by mlamrani          #+#    #+#             */
/*   Updated: 2024/08/03 23:54:49 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_parse *arg, int n_line)
{
	int		i;
	t_args	*tmp;

	tmp = arg->cmd_args;
	if (!ft_strncmp(tmp->content, "echo", 5))
		tmp = tmp->next;
	while (tmp && !ft_strncmp(tmp->content, "-n", 2))
	{
		i = 2;
		while (tmp->content[i] == 'n')
			i++;
		if (tmp->content[i] != '\0')
			break ;
		n_line = 0;
		tmp = tmp->next;
	}
	while (tmp)
	{
		write(arg->red_out, tmp->content, ft_strlen(tmp->content));
		if (tmp->next)
			write(arg->red_out, " ", 1);
		tmp = tmp->next;
	}
	if (n_line && set_status(0))
		write(arg->red_out, "\n", 1);
}

void	ft_env(t_list *prog, t_parse *cmd)
{
	t_list	*env;

	env = prog;
	if (g_global->env_null == 1)
	{
		ft_env_null(prog, cmd);
	}
	else
	{
		while (env)
		{
			ft_putendl_fd((char *)env->content, cmd->red_out);
			env = env->next;
		}
	}
}

int	ft_unset(t_list **env, t_list **exp_list, t_parse *cmd, int flag)
{
	t_args	*cur;
	char	*var_name;

	cur = cmd->cmd_args;
	if (!ft_strncmp(cur->content, "unset", 6))
		cur = cur->next;
	while (cur)
	{
		var_name = m_strdup(cur->content);
		if (!var_name)
			return (g_global->exit_status = 1, 1);
		if (unset_check(var_name, cur->content) || check_dash(cur->content, 3))
			flag = 1;
		else
		{
			set_unset(env, var_name);
			set_unset(exp_list, var_name);
		}
		cur = cur->next;
	}
	if (flag)
		g_global->exit_status = 1;
	return (g_global->exit_status = 0, 0);
}

void	set_unset(t_list **head, char *var_name)
{
	t_list	*current;
	t_list	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (ft_strnstr(current->content, var_name, ft_strlen(var_name)))
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			break ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_exit(t_parse *cmd, t_mini *prog)
{
	t_args	*cur;
	int		content;

	cur = cmd->cmd_args;
	if (!ft_strncmp(cur->content, "exit", 5))
		cur = cur->next;
	if (my_lstsize(cmd->cmd_args) > 2 && ft_isnumeric(cur->content))
		return (g_global->exit_status = 1,
			ft_putendl_fd("exit: too many arguments", 2));
	if (cur && cur->content)
	{
		content = ft_atoi(cur->content);
		if (ft_isnumeric(cur->content) && free_all(prog)
			&& ft_putendl_fd("exit", 1))
			exit(content % 256);
		else if (!ft_isnumeric(cur->content) && free_all(prog)
			&& ft_putendl_fd("exit", 2)
			&& ft_putendl_fd("exit: numeric argument required", 2))
			exit(2);
	}
	else if ((!cur || !cur->content) && free_all(prog) && ft_putendl_fd("exit",
			1))
		exit(0);
	return (0);
}
