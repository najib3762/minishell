/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:51:42 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/11 17:33:29 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_args	*ft_lstnew(void *content)
{
	t_args	*node;

	node = malloc(sizeof(t_args));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(t_args **lst, t_args *new)
{
	t_args	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	ft_echo(t_parse *arg)
{
	int		n_line;
	t_args	*tmp;

	n_line = 1;
	tmp = arg->cmd_args;
	if (tmp && ft_strncmp(tmp->content, "-n", 2) == 0)
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
	
	if(!arg->cmd_args->content)
	{
		path = g_env(env, "HOME=");
		chdir(path + 5);
	}
	else if (ft_strncmp(arg->cmd_args->content,"-", 2) == 0)
	{
		path = g_env(env, "OLDPWD=");
		chdir(path + 7);
	}
	else
		if (chdir(arg->cmd_args->content) < 0)
			printf("cd: no such file or directory: %s\n", arg->cmd_args->content);
}


void get_env(t_args *env, t_args **head)
{
	while(env)
	{
		printf("%s\n", (char *)env->content);
		env = env->next;
	}
}
void	ft_pwd(void)
{
	char	wd[1024];
	int		len;
	char	*cwd;

	cwd = getcwd(wd, sizeof(wd));
	if (cwd)
	{
		len = ft_strlen(cwd);
		printf("%s\n", cwd);
	}
	// else
	// {
	// 	perror("getcwd");
	// 	exit(1);
	// }
}
void append_node(t_args **head, char *content)
{
    t_args *new_node;
	t_args *temp;
	
	new_node  = ft_lstnew(content);
    if (!new_node)
        return;
    temp = *head;
    if (!*head)
    {
        *head = new_node;
        return;
    }
    while (temp->next)
        temp = temp->next;
    
    temp->next = new_node;
}
t_args *set_env(char **env)
{
    t_args *env_list = NULL;
    while (*env)
    {
        append_node(&env_list, *env);
        env++;
    }
    return env_list;
}
int	main(int ac, char **av, char **env)
{
	t_args *env_list = set_env(env);
	// t_parse arg;
	// t_args *current;
	// int i;

	// arg.cmd_args = ft_lstnew(av[1]);
	// current = arg.cmd_args;
	// i = 2;
	// while (i < ac)
	// {
	// 	current->next = ft_lstnew(av[i]);
	// 	current = current->next;
	// 	i++;
	// }
	t_args *saver = set_env(env);
    get_env(saver, &env_list);
	
	//  ft_echo(&arg);
	// ft_cd(&arg, env_list);
	// ft_pwd();

}