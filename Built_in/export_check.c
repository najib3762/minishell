/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:47:39 by mlamrani          #+#    #+#             */
/*   Updated: 2024/08/03 09:01:22 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_check(char *var_name, char *content, t_mini *prog)
{
	t_global	*g_global;

	g_global = global_function();
	(void)prog;
	if (!is_valid_identifier_start(var_name[0]) || var_name[0] == '=')
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(content, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		g_global->exit_status = 1;
		return (1);
	}
	if (has_invalid_characters(var_name))
	{
		if (print_invalid_identifier(content, prog) < 0)
			return (1);
	}
	return (0);
}

int	check_dash(char *content, int i)
{
	t_global	*g_global;
	
	g_global = global_function();
	if (content[0] == '-' && content[1] != '\0')
	{
		if (i == 1)
		{
			ft_putstr_fd("minishell: pwd: '", 2);
			g_global->exit_status = 2;
		}
		else
		{
			ft_putstr_fd("minishell: export: '", 2);
			g_global->exit_status = 1;
		}		
		write(2, content, 2);
		ft_putendl_fd("': invalid option", 2);
		return (1);
	}
	return (0);
}

void	handle_plus_equal(t_list **env, char **var_name, char **var_value,
		char *content)
{
	char	*plus_equal;
	char	*existing_value;
	t_list	*env_var;

	plus_equal = ft_strnstr(content, "+=", ft_strlen(content));
	if (plus_equal)
	{
		free(*var_name);
		*var_name = m_substr(content, 0, plus_equal - content);
		*var_value = m_strdup(plus_equal + 2);
		env_var = find_var_in_list(*env, *var_name);
		if (env_var)
		{
			existing_value = get_var_value((char *)env_var->content);
			*var_value = m_strjoin(existing_value, *var_value);
		}
		*var_name = m_strjoin(*var_name, "=");
	}
}

int	ft_isnumeric(char *str)
{
	if (str == NULL || *str == '\0')
		return (1);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}
