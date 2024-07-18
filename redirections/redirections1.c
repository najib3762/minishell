/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:56:11 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/15 12:15:21 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int handle_redir_in(t_redir *redir, t_parse *temp, t_mini *prog)
{
    char *str;
    
    temp->red_in = open(redir->filename, O_RDONLY);
    if (temp->red_in < 0)
    {
        str = strerror(errno);
        printf("minishell: %s: %s\n", redir->filename, str);
        g_global->exit_status = 1;
        return (-1);
    }
    ft_addback_fd(&prog->fd_head, ft_new_fd(temp->red_in));
    return (0);
}

int handle_redir_out(t_redir *redir, t_parse *temp, t_mini *prog)
{
    char *str;

    temp->red_out = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (temp->red_out < 0)
    {
        str = strerror(errno);
        printf("minishell: %s: %s\n", redir->filename, str);
        g_global->exit_status = 1;
        return (-1);
    }
    ft_addback_fd(&prog->fd_head, ft_new_fd(temp->red_out));
    return (0);
}

int handle_redir_append(t_redir *redir, t_parse *temp, t_mini *prog)
{
    char *str;

    temp->red_out = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (temp->red_out < 0)
    {
        str = strerror(errno);
        printf("minishell: %s: %s\n", redir->filename, str);
        g_global->exit_status = 1;
        return (-1);
    }
    ft_addback_fd(&prog->fd_head, ft_new_fd(temp->red_out));
    return (0);
}

int	num_words(char const *s, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (*s == sep)
			count = 0;
		else if (count == 0)
		{
			count = 1;
			i++;
		}
		s++;
	}
	return (i);
}

int handle_redirection(t_parse *temp, t_mini *prog)
{
    t_redir *temp_redir;
    int num_file;

    temp_redir = temp->redir_list;
    while (temp_redir)
    {
        num_file =  num_words(temp_redir->filename, ' ');
        if (num_file > 1 || num_file == 0)
        {
            printf("minishell: ambiguous redirect\n");
            g_global->exit_status = 1;
            break;
        }

        if (temp_redir->type == REDIR_IN)
        {
                 if (handle_redir_in(temp_redir, temp, prog) < 0)
                        break ;
        }
        else if (temp_redir->type == REDIR_OUT)
        {
                 if (handle_redir_out(temp_redir, temp, prog) < 0)
                        break ;
        }
        else if (temp_redir->type == REDIR_APPEND)
        {
                if (handle_redir_append(temp_redir, temp, prog) < 0)
                        break ;
        }
        temp_redir = temp_redir->next;
    }
    return (0);
}

int redirection(t_parse **parse, t_mini *prog)
{
    t_parse *temp;

    temp = *parse;
    while (temp)
    {
        handle_redirection(temp, prog);
        temp = temp->next;
    }
    return (0);
}
