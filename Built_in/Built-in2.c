/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built-in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:42:47 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/16 00:03:23 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_parse *arg)
{
	int		n_line;
	t_args	*tmp;

	n_line = 1;
	tmp = arg->cmd_args;
	if (!ft_strncmp(tmp->content, "echo", 5))
		tmp = tmp->next;
	while (tmp && ft_strncmp(tmp->content, "-n", 2) == 0)
	{
		n_line = 0;
		tmp = tmp->next;
	}
	while (tmp)
	{
		write(1, tmp->content, ft_strlen(tmp->content));
		if (tmp->next)
			write(1, " ", 1);
		tmp = tmp->next;
	}
	if (n_line)
		write(1, "\n", 1);
}

void ft_env(t_args **env)
{
	t_args *cur;
	
	cur = *env;
	while(cur)
	{
		printf("%s\n", (char *)cur->content);
		cur = cur->next;
	}
}

char *g_env(t_args *env, char *str)
{
	while(env)
	{
		if(ft_strnstr((char *)env->content, str, sizeof(env)))
			return(env->content);
		env = env->next;
	}
	return(NULL);
}

void	ft_cd(t_parse *arg, t_args *env)
{
	char *path;
	
	if (!ft_strncmp(arg->cmd_args->content, "cd", 3))
		arg->cmd_args = arg->cmd_args->next;
	if(!arg->cmd_args->content)
	{
		path = g_env(env, "HOME=");
		chdir(path + 5);
	}
	else if (ft_strncmp(arg->cmd_args->content,"-", 2) == 0)
	{
		path = g_env(env, "OLDPWD=");
		// ft_export((t_mini **)env, (t_mini **)env, "OLDPWD=", ft_pwd(1));
		if (chdir(path + 7) == 0)
			printf("%s\n", path + 7);
	}
	else
		if (chdir(arg->cmd_args->content) < 0)
			printf("cd: no such file or directory: %s\n", arg->cmd_args->content);
}

void ft_unset(t_args **head, char *var_name) {
    t_args *current;
    t_args *prev;

	current = *head;
	prev = NULL;
	if (!var_name)
		return;
    while (current)
	{
        if (ft_strnstr(current->content, var_name, ft_strlen(var_name)))
		{
			if (prev == NULL)
                *head = current->next;
            else
                prev->next = current->next;
            free(current->content);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}
