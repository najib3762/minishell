/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:43:06 by mlamrani          #+#    #+#             */
/*   Updated: 2024/08/01 09:56:09 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*find_var_in_list(t_list *list, const char *var_name)
{
	size_t var_name_len = ft_strlen(var_name);

	while (list)
	{
		char *content = (char *)list->content;
        if (!ft_strncmp(content, var_name, var_name_len) &&
            content[var_name_len] == '=')
			return (list);
		list = list->next;
	}
	return (NULL);
}

char	*get_var_value(const char *var)
{
	char *equal = ft_strchr(var, '=');
	if (equal)
		return (equal + 1);
	return (NULL);
}

void	sort_exp(t_list **start)
{
	int		swapped;
	char	*temp;
	t_list	*current;
	t_list	*last;

	last = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *start;
		while (current->next != last)
		{
			if (ft_strcmp(current->content, current->next->content) > 0)
			{
				temp = current->content;
				current->content = current->next->content;
				current->next->content = temp;
				swapped = 1;
			}
			current = current->next;
		}
		last = current;
	}
}

void check_equal(char **var_name, char **var_value, char *content, char	*equal)
{
	if (equal && *(equal + 1)== '\0')
	{
		*var_name = m_substr(content, 0, equal - content + 1);
		*var_value = NULL;
	}	
	else if (equal)
	{
		*var_name = m_substr(content, 0, equal - content + 1);
		*var_value = m_strdup(equal + 1);
	}
	else
	{
		*var_name = m_strdup(content);
		*var_value = NULL;	
	}
}