/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:01:08 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/19 11:45:31 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_builtin(t_mini *prog, t_parse *tmp)
{
	pid_t	pid;

	if (prog->nbr_cmd > 1)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return ;
		}
		if (pid == 0)
		{
			builtin1(prog, tmp);
			exit(g_global->exit_status);
		}
		waitpid(pid, &g_global->exit_status, 0);
	}
	else
		builtin1(prog, tmp);
}

int	helper_executer(t_mini *prog, t_parse **parse)
{
	if (*parse == NULL || (*parse)->cmd_args == NULL
		|| (*parse)->cmd_args->content == NULL)
		return (-1);
	prog->nbr_cmd = count_cmd(*parse);
	prog->env = conv_env(prog->env_head);
	if (create_multiple_pipe(parse, prog) < 0)
		return (-1);
	if (set_pipe_fd(prog, parse) < 0)
		return (-1);
	if (redirection(parse, prog) < 0)
		return (-1);
	return (0);
}

int	ft_executer(t_parse **parse, t_mini *prog)
{
	char	**cmd;
	t_parse	*tmp;

	if (helper_executer(prog, parse) < 0)
		return (-1);
	tmp = *parse;
	while (tmp)
	{
		cmd = conv_cmd(tmp->cmd_args);
		if (check_builtin(cmd))
			handle_builtin(prog, tmp);
		else
			execute(tmp, cmd, prog->env, prog);
		tmp = tmp->next;
	}
	close_fd_pipe(prog);
	free_fd_pipe(prog);
	close_free(&prog->fd_head);
	waitpid(prog->last_pid, &g_global->exit_status, 0);
	if (WIFEXITED(g_global->exit_status))
		g_global->exit_status = WEXITSTATUS(g_global->exit_status);
	while (wait(NULL) > 0)
	{
	}
	return (0);
}

char	*get_env_value_char(char *key, char **env)
{
	char	*value;
	int		i;

	i = 0;
	while (env[i])
	{
		value = my_getenv(key, env[i]);
		if (value)
			return (value);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;

	i = -1;
	allpath = ft_split(get_env_value_char("PATH", env), ':');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmd);
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
		free(exec);
	}
	return (cmd);
}
