/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:51:42 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/03 22:02:41 by mlamrani         ###   ########.fr       */
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

void ft_echo(t_parse *arg)
{
   int n_line;
   t_args *tmp;
   
   n_line = 1;
   tmp = arg->cmd_args;

   if (tmp && ft_strncmp(tmp->content, "-n", 2) == 0)
   {
        n_line = 0;
        tmp = tmp->next;
   }
   while(tmp)
   {
    write(1, tmp->content, ft_strlen(tmp->content));
    if (tmp->next)
     write(1, " ", 1);
    tmp = tmp->next;
   }
   if(n_line)
    write(1, "\n", 1);
}
int main(int ac, char **av)
{
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
     ft_echo(&arg);
}