/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:26:15 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 18:26:16 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//"sdfdsf""$USER"sdsfdsaf
//PATH=/bin/zsh
//USER = namoussa

char	*handle_dollar(char *str, int *i, t_mini *prog)
{
	char	*var_name;
	char	*var_value;

	var_name = NULL;
	var_value = NULL;
	(*i)++;
	if (str[*i] == '?')
	{
		var_name = m_itoa(g_global->exit_status);
		(*i)++;
		return (var_name);
	}
	if (ft_isalpha(str[*i]) || ft_isdigit(str[*i]))
		var_name = take_var_name(str, i);
	var_value = get_env_value(var_name, prog->env_head);
	if (var_value)
		return (free(var_name), var_value);
	return (free(var_name), NULL);
}

char	*handle_dquotes(char *str, int *i, t_mini *prog)
{
	char	*double_quote;
	char	*temp;

	double_quote = NULL;
	temp = NULL;
	double_quote = ft_strjoin_char(double_quote, str[*i]);
	(*i)++;
	while (str[*i] && (str[*i] != '\"' || str[*i] == '_'))
	{
		double_quote = ft_strjoin_char(double_quote, str[*i]);
		(*i)++;
	}
	double_quote = ft_strjoin_char(double_quote, str[*i]);
	(*i)++;
	temp = ft_expand(double_quote, prog);
	if (temp)
		return (free(double_quote), temp);
	return (free(double_quote), NULL);
}

char	*handle_squotes(char *str, int *i)
{
	char	*single_quote;

	single_quote = NULL;
	single_quote = ft_strjoin_char(single_quote, str[*i]);
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		single_quote = ft_strjoin_char(single_quote, str[*i]);
		(*i)++;
	}
	single_quote = ft_strjoin_char(single_quote, str[*i]);
	(*i)++;
	return (single_quote);
}

char	*dollar_expand(char *str, t_mini *prog)
{
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isdigit(str[i + 1])) && str[i + 2] != '\0')
			i += 2;
		else if (str[i] == '$' && (ft_isalpha(str[i + 1]) || ft_isdigit(str[i
						+ 1])))
			temp = my_strjoin(temp, handle_dollar(str, &i, prog));
		else if (str[i] == '\"')
			temp = my_strjoin(temp, handle_dquotes(str, &i, prog));
		else if (str[i] == '\'')
			temp = my_strjoin(temp, handle_squotes(str, &i));
		else if (str[i] != '\0')
		{
			temp = my_strjoin(temp, ft_strdup_char(str[i]));
			i++;
		}
		if (str[i] == '\0')
			break ;
	}
	return (temp);
}

void	real_expand(t_token **head, t_mini *prog)
{
	t_token	*temp;
	char	*new_str;

	temp = *head;
	new_str = NULL;
	while (temp)
	{
		if (temp->type == TOKEN_WORD)
		{
			if (check_dollar(temp->value))
			{
				new_str = dollar_expand(temp->value, prog);
				if (new_str)
					temp->value = new_str;
				else
					temp->value = "";
			}
		}
		temp = temp->next;
	}
}
