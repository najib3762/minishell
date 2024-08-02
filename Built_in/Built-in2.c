/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built-in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:42:47 by mlamrani          #+#    #+#             */
/*   Updated: 2024/08/02 12:56:07 by mlamrani         ###   ########.fr       */
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
	t_list	*env_null;
	t_global	*g_global;

	g_global = global_function();
	if (g_global->env_null == 1)
	{
		env_null = prog;
		while (env_null)
		{
			if (ft_strncmp(env_null->content, "PATH", 4) == 0)
			{
				env_null = env_null->next;
				continue ;
			}
			else
				ft_putendl_fd((char *)env_null->content, cmd->red_out);
			env_null = env_null->next;
		}
	}
	else
	{
		env = prog;
		while (env)
		{
			ft_putendl_fd((char *)env->content, cmd->red_out);
			env = env->next;
		}
	}
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

int	ft_cd(t_parse *arg, t_list **env)
{
	char	*path;
	t_args	*current;
	t_global	*g_global;

	g_global = global_function();
	current = arg->cmd_args;
	if (my_lstsize(current) > 2)
	{
		g_global->exit_status = 1;
		return (ft_putendl_fd("cd: too many arguments", 2));
	}
	if (!ft_strncmp(current->content, "cd", 3))
		current = current->next;
	if (!current || !current->content)
	{
		path = g_env(*env, "HOME=");
		if (path)
			chdir(path + 5);
		else
			printf("cd: HOME not set\n");
	}
	else if (chdir(current->content) < 0)
	{
		perror("cd");
		g_global->exit_status = 1;
	}
	return (0);
}

int	ft_unset(t_list **env, t_list **exp_list, t_parse *cmd)
{
	t_args	*cur;
	char	*var_name;
	t_global	*g_global;

	(void)exp_list;
	g_global = global_function();
	cur = cmd->cmd_args;
	if (!ft_strncmp(cur->content, "unset", 6))
		cur = cur->next;
	var_name = NULL;
	if (cur && cur->content)
		var_name = m_strdup(cur->content);
	if (!var_name)
		return (g_global->exit_status = 0, 1);
	set_unset(env, var_name);
	set_unset(exp_list, var_name);
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
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_exit(t_parse *cmd, t_mini *prog)
{
	t_args	*cur;
	t_global	*g_global;
	int content;

	cur = cmd->cmd_args;
	g_global = global_function();
	if (!ft_strncmp(cur->content, "exit", 5))
		cur = cur->next;
	if (my_lstsize(cmd->cmd_args) > 2 && ft_isnumeric(cur->content))
		return (g_global->exit_status = 1, ft_putendl_fd("exit: too many arguments", 2));
	if (cur && cur->content)
	{
			content = ft_atoi(cur->content);
		if (ft_isnumeric(cur->content) && free_all(prog))
		{
		  ft_putendl_fd("exit", 1);
		  exit(content % 256);
		}
		else
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			free_all(prog);
			exit(2);
		}
	}
	else
	{
		ft_putendl_fd("exit", 1);
		free_all(prog);
		exit(0);
	}
	return (0);
}
