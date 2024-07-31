/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:51:42 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/31 19:06:46 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_pwd(int i, t_parse *cmd)
{
	char	wd[1024];
	int		len;
	char	*cwd;

	cwd = getcwd(wd, sizeof(wd));
	if (i == 0 && cwd)
	{
		len = ft_strlen(cwd);
		ft_putendl_fd( cwd, cmd->red_out);
	}
	else
		return (cwd);
	return (NULL);
}

char *m_strndup(char *s, size_t n)
{
    size_t len;
    char *p;

    len = ft_strlen(s);
    if (n < len)
        len = n;
    p = (char *)malloc(len + 1);
	addback_node_free(&g_global->address, newnode_free(p));
    if (!p)
        return NULL;
    ft_strncpy(p, s, len);
    p[len] = '\0';
    return (p);
}

void my_print_list(t_list *export_list, t_parse *cmd)
{
    t_list *current;
    char *equal_sign;
    char *quoted_value;
    char *var_name;
    char *new_var;

	current = export_list;
    while (current)
    {
        equal_sign = ft_strchr(current->content, '=');
        if (equal_sign)
        {
            var_name = m_strndup(current->content, equal_sign - (char *)current->content + 2);
            quoted_value = add_quotes(equal_sign + 1);
            new_var = m_strjoin(var_name, quoted_value);
            ft_putendl_fd(ft_strjoin("declare -x ", new_var), cmd->red_out);
        }
        else
            ft_putendl_fd(m_strjoin("declare -x ", (char *)current->content), cmd->red_out);
        current = current->next;
    }
}

void	ft_export(t_list **env, t_list **export_list, t_parse *cmd, char *var_name)
{
	char 	*equal;
	char	*var_value;
	t_args 	*cur;

	var_value = NULL;
	cur = cmd->cmd_args;
	if (!ft_strncmp(cur->content, "export", 7))
		cur = cur->next;
	while (cur)
	{
		if (cur->content)
		{  
            if (check_dash(cur->content))
                return;
			equal = ft_strchr(cur->content, '=');
			check_equal(&var_name, &var_value, cur->content, equal);
			handle_plus_equal(env, &var_name, &var_value, cur->content);
			export_check(var_name, cur->content);
			add_to_exp(var_name, var_value, env, export_list);
		}
		cur = cur->next;
	}
	if (!var_name)
		p_exp(export_list, cmd);
}
void add_to_exp(char *var_name, char *var_value, t_list **env, t_list **export_list)
{
	if (var_name && !var_value) //adding variable to the export list
        add_var(*export_list, var_name, export_list);
	if (var_name && var_value) //adding the variable and the value to env and export list
		adding(env, export_list, var_name, var_value);
}



