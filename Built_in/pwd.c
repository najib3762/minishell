/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:51:42 by mlamrani          #+#    #+#             */
/*   Updated: 2024/08/03 23:39:57 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_pwd(int i, t_parse *cmd, t_mini *prog)
{
	char	wd[1024];
	int		len;
	char	*cwd;
	t_args	*cur;

	cur = cmd->cmd_args;
	if (cur && !ft_strncmp(cur->content, "pwd", 7))
		cur = cur->next;
	if (cur && check_dash(cur->content, 1))
		return (NULL);
	cwd = getcwd(wd, sizeof(wd));
	if (!cwd)
	{
		ft_putendl_fd(prog->pwd, cmd->red_out);
		return (NULL);
	}
	else
	{
		if (i == 0)
		{
			len = ft_strlen(cwd);
			ft_putendl_fd(cwd, cmd->red_out);
		}
		return (cwd);
	}
}

int	unset_check(char *var_name, char *content)
{
	char	*pos;

	(void)content;
	pos = ft_strchr(var_name, '!');
	if (ft_strchr(var_name, '!') != NULL)
	{
		ft_putstr_fd("minishell: unset: '", 2);
		ft_putstr_fd(pos, 2);
		ft_putendl_fd("': event not found", 2);
		g_global->exit_status = 1;
		return (1);
	}
	return (0);
}
