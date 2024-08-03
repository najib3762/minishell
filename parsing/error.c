/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 11:51:38 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 11:51:39 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *error)
{
	write(2, error, strlen(error));
}

int	check_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	handle_error(int flag, char *cmd)
{
	if (flag == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	if (flag == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	if (flag == 3)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Is a directory", 2);
	}
	return (0);
}

char	*check_command(char *cmd, t_mini *prog)
{
	struct stat	buf;
	(void)prog;

	if (check_slash(cmd) && access(cmd, F_OK) != 0 && !handle_error(1, cmd))
		exit(g_global->exit_status = 127);
	if (check_slash(cmd) && !stat(cmd, &buf) && access(cmd, F_OK) == 0)
	{
		if (S_ISREG(buf.st_mode) && access(cmd, X_OK) != 0 && !handle_error(2,
				cmd))
			exit(g_global->exit_status = 126);
		if (S_ISREG(buf.st_mode) && access(cmd, X_OK) == 0)
			return (cmd);
		if (S_ISDIR(buf.st_mode) && !handle_error(3, cmd))
			exit(g_global->exit_status = 126);
	}
	return (NULL);
}

int	my_lstsize(t_args *lst)
{
	int		count;
	t_args	*p;

	count = 0;
	if (!lst)
		return (count);
	p = lst;
	while (p)
	{
		count++;
		p = p->next;
	}
	return (count);
}
