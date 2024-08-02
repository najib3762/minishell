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

int	helper_here_doc(int fd, char *eof, int qoutes, t_mini *prog)
{
	signal(SIGINT, sig_here_doc);
	signal(SIGQUIT, SIG_IGN);
	prog->line = readline(">");
	while (prog->line)
	{
		if (!ft_strncmp(prog->line, eof, ft_strlen(eof))
			&& (ft_strlen(prog->line) == ft_strlen(eof)))
			return (close(fd), 0);
		if (ft_strncmp(prog->line, eof, ft_strlen(eof)) && qoutes != 1
			&& check_dollar(prog->line))
		{
			prog->line = ft_expand(prog->line, prog);
			if (!prog->line)
				prog->line = m_strdup("");
		}
		ft_putendl_fd(prog->line, fd);
		prog->line = readline(">");
	}
	if (my_handle() < 0)
		return (-1);
	return (0);
}

int	fork_heredoc(char *eof, int fd, int qoutes, t_mini *prog)
{
	if (helper_here_doc(fd, eof, qoutes, prog))
		return (-1);
	else if (!prog->line)
	{
		printf("minishell: warning: here-doc delimited by EOF (wanted `%s')\n",
			eof);
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
	printf("heredoc: %s\n", filename);
	if (!filename)
		return (-1);
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (token->next->type == TOKEN_WORD)
	{
		if (read_here_doc(token->next->value, fd, prog) < 0)
			return (close(fd), -1);
		else
			return (close(fd), change_value(token, filename), 1);
	}
	else
		return (close(fd), -1);
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
