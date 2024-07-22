#include "../minishell"

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
	env = malloc(sizeof(char *) * (count + 1));
	while (cur)
	{
		env[i++] = cur->content;
		cur = cur->next;
	}
	env[i] = NULL;
	return (env);
}
int	execute(t_parse *redr, char **cmd, char **env, t_mini *prog)
{
	char	*path;
	pid_t	pid;

	path = get_path(cmd[0], env);
	if (!path)
		perror("no path");
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (!pid)
	{
		dup2(redr->red_in, 0);
		dup2(redr->red_out, 1);
		close_fd_pipe(prog);
		free_fd_pipe(prog);
		if (execve(path, cmd, env) == -1)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(cmd[0], 2);
			exit(g_global->exit_status = 1);
		}
	}
	if (redr->next == NULL)
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
	if (ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "cd") == 0 ||
		ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "export") == 0 ||
		ft_strcmp(cmd[0], "unset") == 0 || ft_strcmp(cmd[0], "env") == 0 ||
		ft_strcmp(cmd[0], "exit") == 0)
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
