/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:51:42 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/13 17:24:21 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
void	sort_exp(t_mini **start)
{
    int swapped;
	char *temp;
    t_list *current;
    t_list *last = NULL;

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

// int ft_add(t_args *tmp, char *var_name, int flag, char *new_var)
// {
// 	while (tmp)
// 		{
//             if (!ft_strncmp(tmp->content, var_name, ft_strlen(var_name)))
// 			{
//                 flag = 0;
//                 free(tmp->content);
//                 tmp->content = new_var;
//                 return (0);
//             }
//             tmp = tmp->next;
//         }
// 		return (1);
// }
void ft_export(t_args **env, t_args **export_list, char *var_name, char *var_value)
{
    char *new_var;
    t_args *tmp;
    int flag;

	if (!var_name && !var_value) //print export list
	{
		sort_exp(env);
		print_list(*env);
		return;
	}
    if (var_name && !var_value) //add variable to the export list without the env list
	{
        tmp = *export_list;
        while (tmp)
		{
            if (!ft_strncmp(tmp->content, var_name, ft_strlen(var_name)))
				return;
            tmp = tmp->next;
        }
        ft_lstadd_back(export_list, ft_lstnew(strdup(var_name)));
        return;
    }
    if (var_name && var_value) // add on both
	{
        new_var = ft_strjoin(var_name, var_value);
        tmp = *env;
        flag = 1;

        while (tmp)
		{
            if (!ft_strncmp(tmp->content, var_name, ft_strlen(var_name)))
			{
                flag = 0;
                free(tmp->content);
                tmp->content = new_var;
            }
            tmp = tmp->next;
        }
        if (flag == 1)
            ft_lstadd_back(env, ft_lstnew(new_var));
        else
            free(new_var);
    }
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

int	main(int ac, char **av, char **env)
{
	t_args *env_list = set_env(env);
	t_args *export_list = set_env(env);
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
	ft_export(&env_list, &export_list, "ana", 0);
	// ft_export(&env_list, &export_list, 0, 0);
	// ft_unset(&env_list, 0);
	// ft_export(&env_list, 0, 0);
	printf("=====================================================================================\n\n\n");
	// ft_env(&env_list);
	// ft_cd(&arg, env_list);
	// ft_pwd(0);
}
