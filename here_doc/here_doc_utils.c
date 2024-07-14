/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:28:34 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 18:28:35 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*retur_value(int flag)
{
	static int	ret;

	if (flag == 1)
		ret = -1;
	return (&ret);
}

void	sig_here_doc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	*retur_value(0) = dup(0);
	close(0);
}

int	check_qoutes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] && (str[i] == '\"' || str[i] == '\''))
			return (1);
		i++;
	}
	return (0);
}

char	*is_qoutes(char *str, int *qoutes)
{
	char	*eof;

	if (check_qoutes(str) == 1)
	{
		eof = skip_quotes(str);
		*qoutes = 1;
	}
	else
		eof = str;
	return (eof);
}

int	check_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
