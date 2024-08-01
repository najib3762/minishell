/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:36:00 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/31 13:42:53 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_valid_identifier_start(char c)
{
    return (ft_isalpha(c) || c == '_');
}

int is_valid_identifier_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}

int has_invalid_characters(char *str)
{
    while (*str)
    {
        if (!is_valid_identifier_char(*str) && *str != '=')
            return 1;
        str++;
    }
    return 0;
}

void print_invalid_identifier(char *str)
{
    char *ptr;

	ptr = str;
    while (*ptr && (isalnum(*ptr) || *ptr == '_'))
        ptr++;
    if (*ptr == '!')
        printf("bash: %c%s: event not found\n", *ptr, ptr + 1);
    else
        printf("bash: export: '%s': not a valid identifier\n", str);
}

void p_exp(t_list **export_list, t_parse *cmd)
{
	sort_exp(export_list);
	my_print_list(*export_list, cmd);
	return;
}
