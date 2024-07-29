/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:53:25 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/23 10:53:26 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	p = (char *)malloc(len + 1);
	addback_node_free(&g_global->address, newnode_free(p));
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, len + 1);
	ft_strlcat(p, s2, len + 1);
	return (p);
}

void	handle_execve_error(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

void	ft_exec(t_parse *redr, char **cmd, char **env, t_mini *prog)
{
	dup2(redr->red_in, 0);
	dup2(redr->red_out, 1);
	close_fd_pipe(prog);
	free_fd_pipe(prog);
	if (execve(prog->path, cmd, env) == -1)
	{
		handle_execve_error(cmd[0]);
		exit(g_global->exit_status = 127);
	}
}
