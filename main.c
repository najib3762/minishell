/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:17:49 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/19 22:44:04 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	*g_global;

void	print_lexer(t_token **head)
{
	t_token	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->type == TOKEN_WORD)
			printf("word: %s\n", temp->value);
		else if (temp->type == TOKEN_PIPE)
			printf("pipe: %s\n", temp->value);
		else if (temp->type == TOKEN_OUT)
			printf("out: %s\n", temp->value);
		else if (temp->type == TOKEN_APPEND)
			printf("append: %s\n", temp->value);
		else if (temp->type == TOKEN_HERE)
			printf("here: %s\n", temp->value);
		else if (temp->type == TOKEN_IN)
			printf("in: %s\n", temp->value);
		temp = temp->next;
	}
}

void	free_parse_list(t_parse **head)
{
	t_parse	*temp_parse;
	t_args	*temp_args;
	t_redir	*temp_redir;

	while (*head)
	{
		temp_parse = *head;
		*head = (*head)->next;
		while (temp_parse->cmd_args)
		{
			temp_args = temp_parse->cmd_args;
			temp_parse->cmd_args = temp_parse->cmd_args->next;
			if (temp_args->content)
			{
				free(temp_args->content);
				temp_args->content = NULL;
			}
			free(temp_args);
		}
		while (temp_parse->redir_list)
		{
			temp_redir = temp_parse->redir_list;
			temp_parse->redir_list = temp_parse->redir_list->next;
			if (temp_redir->filename)
			{
				free(temp_redir->filename);
				temp_redir->filename = NULL;
			}
			free(temp_redir);
		}
		free(temp_parse);
	}
	*head = NULL;
}

void	print_parse(t_parse **parse)
{
	t_parse	*temp;
	t_args	*args;
	t_redir	*redir;

	temp = *parse;
	while (temp)
	{
		args = temp->cmd_args;
		redir = temp->redir_list;
		printf("args: ");
		while (args)
		{
			printf("%s ---> ", args->content);
			args = args->next;
		}
		printf("\n");
		printf("redir:");
		while (redir)
		{
			printf(" value :%s ---> ", redir->filename);
			printf("type: %u ", redir->type);
			redir = redir->next;
		}
		printf("\n");
		temp = temp->next;
	}
}

void	main2(t_mini *prog, t_token **head, t_parse **parse)
{
	
	while (1)
	{
		prog->line = readline(PROMPT);
	     addback_node_free(&g_global->address, newnode_free(prog->line));
	        if (!prog->line)
		         break ;
			if(prog->line[0] == '\0')
				continue;
		add_history(prog->line);
		if (check_quotes(prog) == 1)
		{
			ft_lexer(prog, head);
			if(ft_here_doc(head, prog) < 0)
			{
				free_token_list(head);
				  continue;
			}
			if (!check_syntax_errors(head))
			{
				real_expand(head, prog);
				r_quotes(head);
				parse_input(head, parse);
				print_parse(parse);
				ft_executer(parse, prog);
			}
		}
		free_token_list(head);
		free_parse_list(parse);
	}
}

void	print_list(t_list *head)
{
	while (head)
	{
		printf("%s\n", (char *)head->content);
		head = head->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_mini	prog;
	t_token	*head;
	t_parse	*parse;

	head = NULL;
	parse = NULL;
	(void)av;
	// signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	init_data(ac, env, &prog);
	main2(&prog, &head, &parse);
	// free_address(&g_global->address);
	return (0);
}
