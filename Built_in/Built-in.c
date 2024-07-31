/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:51:42 by mlamrani          #+#    #+#             */
/*   Updated: 2024/07/31 12:44:56 by mlamrani         ###   ########.fr       */
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
t_list	*find_var_in_list(t_list *list, const char *var_name)
{
	size_t var_name_len = ft_strlen(var_name);

	while (list)
	{
		char *content = (char *)list->content; // Cast to char *
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

void	ft_export(t_list **env, t_list **export_list, t_parse *cmd)
{
	char 	*equal;
	char	*plus_equal;
	char	*var_name;
	char	*var_value;
	t_args 	*cur;
	t_list	*env_var;
	int f;

	f = 0;
	var_name = NULL;
	var_value = NULL;
	cur = cmd->cmd_args;
	if (!ft_strncmp(cur->content, "export", 7))
		cur = cur->next;
	while (cur)
	{
		if (cur->content)
		{
			if (cur->content[0] == '-' && cur->content[1] != '\0')
			{
				printf("bash: export: '%c%c': invalid option\n", cur->content[0], cur->content[1]);
				return;
			}
			plus_equal = ft_strnstr(cur->content, "+=", ft_strlen(cur->content));
			equal = ft_strchr(cur->content, '=');
			if (equal && ft_isspace(*(equal - 1)) && equal > cur->content)
			{
				printf("bash: export: '%s': not a valid identifier\n", cur->content);
				return;
			}
			if (equal && *(equal + 1)== '\0')
			{
				var_name = m_substr(cur->content, 0, equal - cur->content + 1);
				var_value = NULL;
			}	
			if (equal)
			{
				var_name = m_substr(cur->content, 0, equal - cur->content + 1);
				var_value = m_strdup(equal + 1);
			}
			else
			{
				var_name = m_strdup(cur->content);
				var_value = m_strdup("");	
			}
			if (plus_equal)
			{
				f = 1;
				var_name = m_substr(cur->content, 0, plus_equal - cur->content);
				var_value = m_strdup(plus_equal + 2);
				env_var = find_var_in_list(*env, var_name);
				if (env_var)
				{
					char *existing_value = get_var_value((char *)env_var->content);
					var_value = m_strjoin(existing_value, var_value);
				}
			}
			if(f == 1)
				var_name = m_strjoin(var_name, "=");
			if (!is_valid_identifier_start(var_name[0]) || var_name[0] == '=')
			{
				printf("bash: export: '%s': not a valid identifier\n", cur->content);
				return;
			}
			if (has_invalid_characters(var_name))
			{
				print_invalid_identifier(cur->content);
				return;
			}
			add_to_exp(var_name, var_value, env, export_list);
		}
		cur = cur->next;
	}
	if (!var_name)
	{
		sort_exp(export_list);
		my_print_list(*export_list, cmd);
		return;
	}
}
void add_to_exp(char *var_name, char *var_value, t_list **env, t_list **export_list)
{
	if (var_name && !var_value) //adding variable to the export list
        add_var(*export_list, var_name, export_list);
	if (var_name && var_value) //adding the variable and the value to env and export list
		adding(env, export_list, var_name, var_value);
}

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
