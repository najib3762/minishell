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


char **conv_cmd(t_args *prog)
{
    t_args *cur;
    int i;
    char **env;
    t_args *tmp;
    int count;

    i = 0;
	if(prog == NULL)
		return (NULL);
    cur = prog;
    count = 0;
    tmp = prog;
    while(tmp)
    {
        count++;
        tmp = tmp->next;
    }
    env = malloc(sizeof(char *) * (count + 1));
    while(cur)
    {
        env[i++] = cur->content;
        cur = cur->next;
    }
    env[i] = NULL;
    return(env);
}

char **conv_env(t_list *prog)
{
    t_list *cur;
    int i;
    char **env;
    t_list *tmp;
    int count;


    i = 0;
    cur = prog;
    count = 0;
    tmp = prog;
    while(tmp)
    {
        count++;
        tmp = tmp->next;
    }
    env = malloc(sizeof(char *) * (count + 1));
    while(cur)
    {
        env[i++] = cur->content;
        cur = cur->next;
    }
    env[i] = NULL;
    return(env);
}
int execute(t_parse *redr, char **cmd, char **env, t_mini *prog)
{
    char *path;
    pid_t   pid;
    
   
    path = get_path(cmd[0], env);
    if(!path)
        perror("no path");
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    if (!pid)
    {
        dup2(redr->red_in, 0);
        dup2(redr->red_out, 1);
        close_fd_pipe(prog);
        free_fd_pipe(prog);
        if(execve(path, cmd, env) == -1)
        {
            ft_putstr_fd("minishell: command not found: ", 2);
		    ft_putendl_fd(cmd[0], 2);
            exit(g_global->exit_status = 1);
        }
    }
    if(redr->next == NULL)
        prog->last_pid = pid;
    return 0;

}

int count_cmd(t_parse *prog)
{
    int i;
    t_parse *tmp;

    i = 0;
    tmp = prog;
    while(tmp)
    {
        i++;
        tmp = tmp->next;
    }
    return(i);
}

int ft_executer(t_parse **parse, t_mini *prog)
{
    char **env;
    char **cmd;
    t_parse *tmp;
   
    
	if(*parse == NULL || (*parse)->cmd_args == NULL || (*parse)->cmd_args->content == NULL )
		return(-1);
    prog->nbr_cmd = count_cmd(*parse);
    env = conv_env(prog->env_head);
    tmp = *parse;
    if(create_multiple_pipe(parse, prog) < 0)
        return(-1);
    if(set_pipe_fd(prog, parse) < 0)
        return(-1);
    if(redirection(parse, prog) < 0)
        return(-1);
    while (tmp)
    {
        cmd = conv_cmd(tmp->cmd_args);
		if (!ft_strncmp(tmp->cmd_args->content, "exit", 5))
			ft_exit(tmp);
		else if(!ft_strncmp(tmp->cmd_args->content, "echo", 5))
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
		else
			execute(tmp, cmd, env, prog);
        tmp = tmp->next;
    }
    close_fd_pipe(prog);
    free_fd_pipe(prog);
    close_free(&prog->fd_head);
    waitpid(prog->last_pid, &g_global->exit_status, 0);
    if(WIFEXITED(g_global->exit_status))
        g_global->exit_status = WEXITSTATUS(g_global->exit_status);
    while(wait(NULL) > 0)
    {}
      return (0);
}    

char	*get_env_value_char(char *key, char **env)
{
	char	*value;
    int i;

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

char    *get_path(char *cmd, char **env)
{
    int        i;
    char    *exec;
    char    **allpath;
    char    *path_part;

    i = -1;
    allpath = ft_split(get_env_value_char("PATH", env), ':');
    while (allpath[++i])
    {
        path_part = ft_strjoin(allpath[i], "/");
        exec = ft_strjoin(path_part, cmd);
        free(path_part);
        if (access(exec, F_OK | X_OK) == 0)
        {
            // ft_free_tab(allpath);
            // ft_free_tab(s_cmd);
            return (exec);
        }
        free(exec);
    }
    // ft_free_tab(allpath);
    // ft_free_tab(s_cmd);
    return (cmd);
}

