/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:52:33 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/23 10:52:34 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**conv_env(t_list *prog)
{
	t_list	*cur;
	int		i;
	char	**env;
	t_list	*tmp;
	int		count;

	i = 0;
	cur = prog;
	count = 0;
	tmp = prog;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	env = (char **)malloc(sizeof(char *) * (count + 1));
	addback_node_free(&g_global->address, newnode_free(env));
	while (cur)
	{
		env[i++] = cur->content;
		cur = cur->next;
	}
	env[i] = NULL;
	return (env);
}

int	execute(t_parse *parse, char **cmd, char **env, t_mini *prog)
{
	pid_t	pid;

	prog->path = get_path(cmd[0], env);
	if (prog->path == NULL)
	   {
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (g_global->exit_status = 127);
	   }
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (!pid)
	{
		ft_exec(parse, cmd, env, prog);
	}
	if (parse->next == NULL)
		prog->last_pid = pid;
	return (0);
}

int	count_cmd(t_parse *prog)
{
	int		i;
	t_parse	*tmp;

	i = 0;
	tmp = prog;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	check_builtin(char **cmd)
{
	if (cmd[0] == NULL || cmd == NULL || cmd[0][0] == '\0')
		return (0);
	if (ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "cd") == 0
		|| ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "export") == 0
		|| ft_strcmp(cmd[0], "unset") == 0 || ft_strcmp(cmd[0], "env") == 0
		|| ft_strcmp(cmd[0], "exit") == 0)
		return (1);
	return (0);
}

void	builtin1(t_mini *prog, t_parse *tmp)
{
	if (!ft_strncmp(tmp->cmd_args->content, "exit", 5))
		ft_exit(tmp);
	else if (!ft_strncmp(tmp->cmd_args->content, "echo", 5))
		ft_echo(tmp, 1);
	else if (!ft_strncmp(tmp->cmd_args->content, "cd", 3))
		ft_cd(tmp, &prog->env_head);
	else if (!ft_strncmp(tmp->cmd_args->content, "pwd", 4))
		ft_pwd(0, tmp);
	else if (!ft_strncmp(tmp->cmd_args->content, "export", 7))
		ft_export(&prog->env_head, &prog->export_head, tmp);
	else if (!ft_strncmp(tmp->cmd_args->content, "env", 4))
		ft_env(prog->env_head, tmp);
	else if (!ft_strncmp(tmp->cmd_args->content, "unset", 6))
		ft_unset(&prog->env_head, &prog->export_head, tmp);
}
