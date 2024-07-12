/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:51:42 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/12 19:45:28 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/Minishell.h"

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



void get_env(t_args **env)
{
	t_args *cur;
	
	cur = *env;
	while(cur)
	{
		printf("%s\n", (char *)cur->content);
		cur = cur->next;
	}
}
char *ft_pwd(int i)
{
	char	wd[1024];
	int		len;
	char	*cwd;

	cwd = getcwd(wd, sizeof(wd));
	if (i == 0 && cwd)
	{
		len = ft_strlen(cwd);
		printf("%s\n", cwd);
	}
	else
		return(cwd);
	return (NULL);
}

void print_list(t_args *head)
{
    while (head)
    {
        printf("%s\n", head->content);
        head = head->next;
    }
}
void	sort_exp(t_args **start)
{
    int swapped;
	char *temp;
    t_args *current;
    t_args *last = NULL;

    swapped = 1;
    while (swapped)
	{
        swapped = 0;
        current = *start;
        while (current->next != last)
		{
            if (ft_strcmp(current->content, current->next->content) > 0)
			{
                temp = current->content;
    			current->content = current->next->content;
    			current->next->content = temp;
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    }
}

void ft_export(t_args **env, char *var_name, char *var_value)
{
	char *new_var;
	t_args *new_node;
	t_args *tmp = *env;
	t_args *exist;
	int flag;

	flag = 1;	
	if (!var_name && !var_value)
	{
		sort_exp(env);
        return (print_list(*env));
	}
	while(tmp)
	{
		if (!ft_strncmp(tmp->content, var_name, ft_strlen(var_name)))
		{
			flag = 0;
			free(tmp->content);
			new_var = ft_strjoin(var_name, var_value);
			tmp->content = new_var;
		}
		tmp = tmp->next;
	}
	if (flag == 1)
	{
		new_var = ft_strjoin(var_name, var_value);
		ft_lstadd_back(env, ft_lstnew(new_var));
	}
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
		ft_export(&env, "OLDPWD=", ft_pwd(1));
		chdir(path + 7);
	}
	else
		if (chdir(arg->cmd_args->content) < 0)
			printf("cd: no such file or directory: %s\n", arg->cmd_args->content);
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
        append_node(&env_list, ft_strdup(*env));
        env++;
    }
    return env_list;
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
			printf("enter\n");
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
int	main(int ac, char **av, char **env)
{
	t_args *env_list = set_env(env);
	t_parse arg;
	t_args *current;
	int i;

	arg.cmd_args = ft_lstnew(av[1]);
	current = arg.cmd_args;
	i = 2;
	while (i < ac)
	{
		current->next = ft_lstnew(av[i]);
		current = current->next;
		i++;
	}

	//  ft_echo(&arg);
	ft_export(&env_list, "simo=", "nfs/rca");
	// ft_export(&env_list, 0, 0);
	ft_unset(&env_list, 0);
	// ft_export(&env_list, 0, 0);
	// get_env(&env_list);
	// ft_cd(&arg, env_list);
	// ft_pwd(0);
}