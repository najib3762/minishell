/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_use.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:13:36 by mlamrani          #+#    #+#             */
/*   Updated: 2024/08/03 17:15:00 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*m_strndup(char *s, size_t n)
{
	size_t	len;
	char	*p;

	len = ft_strlen(s);
	if (n < len)
		len = n;
	p = (char *)malloc(len + 1);
	addback_node_free(&g_global->address, newnode_free(p));
	if (!p)
		return (NULL);
	ft_strncpy(p, s, len);
	p[len] = '\0';
	return (p);
}

void	my_print_list(t_list *export_list, t_parse *cmd)
{
	t_list	*current;
	char	*equal_sign;

	current = export_list;
	while (current)
	{
		equal_sign = ft_strchr(current->content, '=');
		if (equal_sign)
		{
			ft_putstr_fd(m_strjoin("declare -x ", m_substr(current->content, 0,
						ft_lengh_word(current->content))), cmd->red_out);
			ft_putstr_fd(m_strjoin("\"", m_substr(current->content,
						ft_lengh_word(current->content),
						ft_strlen(current->content))), cmd->red_out);
			ft_putendl_fd("\"", cmd->red_out);
		}
		else
			ft_putendl_fd(m_strjoin("declare -x ", (char *)current->content),
				cmd->red_out);
		current = current->next;
	}
}
