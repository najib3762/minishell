/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:47:39 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/31 19:07:35 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void export_check(char *var_name, char *content)
{
	if (!is_valid_identifier_start(var_name[0]) || var_name[0] == '=')
	{
		printf("bash: export: '%s': not a valid identifier\n", content);
		return;
	}
	if (has_invalid_characters(var_name))
	{
		print_invalid_identifier(content);
		return;
	}
}

int check_dash(char *content)
{
    if (content[0] == '-' && content[1] != '\0')
	{
		printf("bash: export: '%c%c': invalid option\n", content[0], content[1]);
        return(1);
    }
    return(0);
}

void handle_plus_equal(t_list **env, char **var_name, char **var_value, char *content)
{
    char *plus_equal;
    char *existing_value;
    t_list *env_var;

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

int ft_isnumeric(char *str)
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
