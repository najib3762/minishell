/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:28:43 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 18:28:44 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_value(t_token *token, char *filename)
{
	token->value = "<";
	token->type = TOKEN_IN;
	token->next->value = filename;
	token->next->type = TOKEN_WORD;
}

int	calcule_qoutes(char *str)
{
	int	dflag;
	int	sflag;
	int	res;
	int	i;

	dflag = 0;
	sflag = 0;
	res = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' && sflag == 0)
		{
			res += 1;
			dflag = !dflag;
		}
		if (str[i] == '\'' && dflag == 0)
		{
			res += 1;
			sflag = !sflag;
		}
		i++;
	}
	return (res);
}

void	g_word(char *str, char *eof)
{
	int	dflag;
	int	sflag;
	int	i;
	int	j;

	dflag = 0;
	sflag = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\"' && sflag == 0 && ++i)
			dflag = !dflag;
		else if (str[i] == '\'' && dflag == 0 && ++i)
			sflag = !sflag;
		else if ((str[i] == '$' && dflag == 0) && (str[i] == '$' && sflag == 0)
			&& (str[i + 1] == '\"' || str[i + 1] == '\''))
			i++;
		else
			eof[j++] = str[i++];
	}
	eof[j] = '\0';
}

char	*skip_quotes(char *str)
{
	char	*eof;
	int		len;
	int		qoutes;
	t_global	*g_global;

	if (!str)
		return (NULL);
	g_global = global_function();
	qoutes = calcule_qoutes(str);
	len = ft_strlen(str) - qoutes;
	eof = malloc(sizeof(char) * (len + 1));
	if (!eof)
	{
		perror("malloc");
		return (NULL);
	}
	addback_node_free(&g_global->address, newnode_free(eof));
	g_word(str, eof);
	return (eof);
}
