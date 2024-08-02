/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:51:42 by mlamrani          #+#    #+#             */
/*   Updated: 2024/08/02 11:04:04 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_pwd(int i, t_parse *cmd)
{
	char	wd[1024];
	int		len;
	char	*cwd;
	t_args *cur;

	cwd = getcwd(wd, sizeof(wd));
	cur = cmd->cmd_args;
	if (cur && !ft_strncmp(cur->content, "pwd", 7))
		cur = cur->next;
	if (cur && check_dash(cur->content, 1))
		return(NULL);
	if (i == 0 && cwd)
	{
		len = ft_strlen(cwd);
		ft_putendl_fd(cwd, cmd->red_out);
	}
	else
		return (cwd);
	return (NULL);
}

char	*m_strndup(char *s, size_t n)
{
	t_global	*g_global;
	size_t	len;
	char	*p;
	
	g_global = global_function();
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

void	ft_export(t_mini *prog, t_parse *cmd, char *var_name)
{
	char	*equal;
	char	*var_value;
	t_args	*cur;
	t_global	*g_global;

	var_value = NULL;
	g_global = global_function();
	cur = cmd->cmd_args;
	if (!ft_strncmp(cur->content, "export", 7))
		cur = cur->next;
	while (cur)
	{
		if (cur->content)
		{
			if (check_dash(cur->content, 0))
				return ;
			equal = ft_strchr(cur->content, '=');
			check_equal(&var_name, &var_value, cur->content, equal);
			handle_plus_equal(&prog->env_head, &var_name, &var_value,
					cur->content);
			if (export_check(var_name, cur->content, prog))
				return ;
			add_to_exp(var_name, var_value, &prog->env_head,
					&prog->export_head);
		}
		cur = cur->next;
	}
	if (!var_name)
		p_exp(&prog->export_head, cmd);
	g_global->exit_status = 0;
}
void	add_to_exp(char *var_name, char *var_value, t_list **env,
		t_list **export_list)
{
	if (var_name && !var_value)
		add_var(*export_list, var_name, export_list);
	if (var_name && var_value)
		adding(env, export_list, var_name, var_value);
}
