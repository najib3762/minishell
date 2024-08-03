/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:17:49 by namoussa          #+#    #+#             */
/*   Updated: 2024/08/03 15:13:43 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	*g_global;

int	set_status(int status)
{
	g_global->exit_status = status;
	return (1);
}

void	main3(t_mini *prog, t_token **head, t_parse **parse)
{
	g_global->is_true = 0;
	real_expand(head, prog);
	parse_input(head, parse);
	r_quotes(parse);
	ft_executer(parse, prog);
}

int	free_all(t_mini *prog)
{
	free_address(&g_global->address);
	free(g_global);
	free_token_list(&prog->token);
	close_fd_pipe(prog);
	free_fd_pipe(prog);
	close_free(&prog->fd_head);
	free(prog->line);
	return (1);
}

int	main2(t_mini *prog, t_token **head, t_parse **parse)
{
	while (1)
	{
		hand_sig(1);
		prog->line = readline(PROMPT);
		if (!prog->line)
			return (ft_putendl_fd("\033[31mexit\033[0m", 1));
		if (prog->line[0] == '\0' && set_status(0))
			continue ;
		hand_sig(0);
		getcwd(prog->pwd, sizeof(prog->pwd));
		add_history(prog->line);
		if (check_quotes(prog) == 1)
		{
			ft_lexer(prog, head);
			if (!check_syntax_errors(head))
			{
				if (ft_here_doc(head, prog) < 0 && free_token_list(head))
					continue ;
				main3(prog, head, parse);
			}
		}
		free_token_list(head);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_mini	prog;
	t_parse	*parse;

	parse = NULL;
	(void)av;
	init_data(ac, env, &prog);
	if (main2(&prog, &prog.token, &parse))
	{
		free_all(&prog);
		return (1);
	}
	return (0);
}
