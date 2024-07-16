/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:27:52 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 18:27:53 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_handle(void)
{
	if (*retur_value(0) != 0)
	{
		dup2(*retur_value(0), 0);
		close(*retur_value(0));
		*retur_value(0) = 0;
		g_global->exit_status = 130;
		return (-1);
	}
	return (0);
}

int	fork_heredoc(char *eof, int fd, int qoutes, t_mini *prog)
{
	char	*line;

	signal(SIGINT, sig_here_doc);
	line = readline(">");
	while (line)
	{
		if (!ft_strncmp(line, eof, ft_strlen(eof))
			&& (ft_strlen(line) == ft_strlen(eof)))
			return (free(line), close(fd), 0);
		if (ft_strncmp(line, eof, ft_strlen(eof)) && qoutes != 1
			&& check_dollar(line))
		{
			line = ft_expand(line, prog);
			if (!line)
				line = ft_strdup("");
		}
		ft_putendl_fd(line, fd);
		free(line);
		line = readline(">");
	}
	if (my_handle() < 0)
		return (-1);
	if(!line)
	    {
		printf("minishell: warning: here-doc delimited by EOF (wanted `%s')\n", eof);
		return (0);
	    }
	return (0);
}

int	read_here_doc(char *eof, int fd, t_mini *prog)
{
	char	*limiter;
	int		qoutes;

	qoutes = 0;
	limiter = is_qoutes(eof, &qoutes);
	if (!limiter)
		return (-1);
	if (fork_heredoc(limiter, fd, qoutes, prog) < 0)
		return (-1);
	return (0);
}

int	here_doc2(t_token *token, t_mini *prog)
{
	char	*filename;
	int		fd;

	filename = random_file();
	if (!filename)
		return (-1);
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (free(filename), -1);
	if (token->next->type == TOKEN_WORD)
	{
		if (read_here_doc(token->next->value, fd, prog) < 0)
			return (close(fd), free(filename), -1);
		else
			return (close(fd), change_value(token, filename), 1);
	}
	else
		return (close(fd), free(filename), -1);
	return (0);
}

int	ft_here_doc(t_token **token, t_mini *prog)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == TOKEN_HERE && tmp->next && here_doc2(tmp, prog) < 0)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
