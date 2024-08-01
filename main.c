/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:17:49 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/19 11:15:49 by mlamrani         ###   ########.fr       */
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

void	free_all(t_mini *prog)
{
	free_token_list(&prog->token);
	free_address(&g_global->address);
	free_fd_pipe(prog);
	close_fd_pipe(prog);
}

int	main2(t_mini *prog, t_token **head, t_parse **parse)
{
	while (1)
	{
		signal(SIGINT, handle_sigint1);
		signal(SIGQUIT, SIG_IGN);
		prog->line = readline(PROMPT);
		if (!prog->line)
			return (ft_putendl_fd("\033[31mexit\033[0m", 1));
		if (prog->line[0] == '\0' && set_status(0))
			continue ;
		signal(SIGINT, handle_sigint2);
		signal(SIGQUIT, handle_sigquit);
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
		return (1);
	free_all(&prog);
	return (0);
}
