/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:51:42 by mlamrani          #+#    #+#             */
/*   Updated: 2024/08/03 17:16:50 by mlamrani         ###   ########.fr       */
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
