/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:36:00 by mlamrani          #+#    #+#             */
/*   Updated: 2024/08/03 17:14:29 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_valid_identifier_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_valid_identifier_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	has_invalid_characters(char *str)
{
	while (*str)
	{
		if (!is_valid_identifier_char(*str) && *str != '=')
			return (1);
		str++;
	}
	return (0);
}

int	print_invalid_identifier(char *str, t_mini *prog)
{
	char	*ptr;

	(void)prog;
	ptr = str;
	while (*ptr && (isalnum(*ptr) || *ptr == '_'))
		ptr++;
	if (*ptr == '!')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putchar_fd(*ptr, 2);
		ft_putstr_fd(ptr + 1, 2);
		ft_putendl_fd(": event not found", 2);
		g_global->exit_status = 1;
		return (-1);
	}
	else
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		g_global->exit_status = 1;
		return (-1);
	}
	return (0);
}

void	p_exp(t_list **export_list, t_parse *cmd)
{
	sort_exp(export_list);
	my_print_list(*export_list, cmd);
	g_global->exit_status = 0;
	return ;
}
