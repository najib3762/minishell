/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:01:08 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/19 23:27:38 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void h_p_sig(int sig)
{ 
    if (sig == SIGINT)
    {
        // printf("im here\n");
        g_global->exit_status = 130;
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    // else if (sig == SIGQUIT)
    // {
    //     write(1, "Quit (core dumped)\n", 20);
    //     // rl_replace_line("", 0);
    //     // rl_on_new_line();
    //     // exit(EXIT_SUCCESS); 
    // }
}


// void void_sig(int sig)
// {
//     (void)sig;
// }


void handler_p_signal()
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, SIG_IGN);
}


char **conv_cmd(t_args *prog)
{
    t_args *cur;
    int i;
    char **env;
    t_args *tmp;
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
void execute(t_parse **redr, char **cmd, char **env)
{
    (void)redr;
    char *path;
    pid_t   pid;
    int status;

    path = get_path(cmd[0], env);
    if(!path)
        printf("no path\n");
    handler_p_signal();
    // signal(SIGINT, h_p_sig);
    // signal(SIGQUIT, SIG_DFL);
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return;
    }
    if (!pid)
    {
        
        // dup2(redr->red_in, 0);
        // dup2(redr->red_out, 1);
        printf("im here\n");
        signal(SIGINT, h_p_sig);
        signal(SIGQUIT, SIG_DFL);

        if(execve(path, cmd, env) == -1)
        {
            perror("execve");
            exit(g_global->exit_status = 1);
        }
        // close_fd_pipe(prog);
        // free_fd_pipe(prog);
        
    }
    else
    {
        signal(SIGINT, handle_sigint);
        waitpid(pid, &status, 0);
    }
}

void ft_executer(t_parse **parse, t_mini *prog)
{
    char **env;
    char **cmd;
    t_parse *tmp;
    // t_args *cmd_parse;

    env = conv_env(prog->env_head);
    cmd = conv_cmd((*parse)->cmd_args);
    tmp = *parse;
    // create_multiple_pipe(parse, prog);
    // set_pipe_fd(prog, parse);
    // redirection(parse, prog);
    // while (tmp)
    // {
    //     cmd_parse = tmp->cmd_args;
    //     while(cmd_parse)
    //     {
            if (!ft_strncmp(tmp->cmd_args->content, "exit", 5))
                ft_exit(tmp);
            if(!ft_strncmp(tmp->cmd_args->content, "echo", 5))
                ft_echo(tmp, 1);
            else if (!ft_strncmp(tmp->cmd_args->content, "cd", 3))
                ft_cd(tmp, &prog->env_head);
            else if (!ft_strncmp(tmp->cmd_args->content, "pwd", 4))
                ft_pwd(0);
            else if (!ft_strncmp(tmp->cmd_args->content, "export", 7))
                ft_export(&prog->env_head, &prog->export_head, tmp, NULL, NULL);
            else if (!ft_strncmp(tmp->cmd_args->content, "env", 4))
                ft_env(prog->env_head);
            else if (!ft_strncmp(tmp->cmd_args->content, "unset", 6))
                ft_unset(&prog->env_head, &prog->export_head, tmp);
        else
            execute(parse, cmd, env);
    //     cmd_parse = cmd_parse->content;
    //     }
    //     tmp = tmp->next;
    //     close_fd_pipe(prog);
    //     free_fd_pipe(prog);
        
    // }
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
    char    **s_cmd;

    i = -1;
    allpath = ft_split(get_env_value_char("PATH", env), ':');
    s_cmd = ft_split(cmd, ' ');
    while (allpath[++i])
    {
        path_part = ft_strjoin(allpath[i], "/");
        exec = ft_strjoin(path_part, s_cmd[0]);
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
