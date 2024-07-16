/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:01:08 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/15 18:19:33 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char **conv_env(t_mini *prog)
{
    t_list *cur;
    int i;
    char **env;
    t_list *tmp;
    int count;


    i = 0;
    cur = prog->env_head;
    count = 0;
    tmp = prog->env_head;
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
void print_char(char **env)
{
   int i = 0;
   
   while(env[i])
   {
    printf("%s\n", env[i]);
    i++;
   }
}

void ft_executer(t_parse *parse, t_mini *prog)
{
    char **env;
    t_parse *tmp;
    int pid;
    
    env = conv_env(prog);
    tmp = parse;
    pid = fork();
    if(!pid)
    {
        if(!ft_strncmp(tmp->cmd_args->content, "echo", 5))
            ft_echo(tmp);
        else if (!ft_strncmp(tmp->cmd_args->content, "cd", 3))
            ft_cd(tmp, (t_args *)prog);
        else if (!ft_strncmp(tmp->cmd_args->content, "pwd", 4))
            ft_pwd(0);
        else if (!ft_strncmp(tmp->cmd_args->content, "export", 7))
            ft_export(&prog, &prog, &tmp);
    }
    else
        wait(NULL);
}

