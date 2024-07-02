#include "include/minishell.h"

// add_args
//create_parse_node
//create_redirection_node
//add_redirection
//t_args node

t_args *args_node(char *content) 
{
	t_args *node = (t_args *)malloc(sizeof(t_args));
	if (!node) 
	return NULL;
	node->content = strdup(content);
	node->next = NULL;
	return node;
}


t_redir *redir_node(char *filename, t_redir_enum type) 
{
	t_redir *node = (t_redir *)malloc(sizeof(t_redir));
	if (!node) return NULL;
	node->filename = strdup(filename);
	node->type = type;
	node->next = NULL;
	return node;
}


t_parse *cmd_node(t_args *cmd_args, t_redir *redir_list) 
{
	t_parse *node = (t_parse *)malloc(sizeof(t_parse));
	if (!node) 
	return NULL;
	node->cmd_args = cmd_args;
	node->redir_list = redir_list;
	node->next = NULL;
	return node;
}

void add_args_node(t_args **list, t_args *new_node) 
{
	t_args *temp;

	if (!*list) 
		*list = new_node;
	else 
	{
		temp = *list;
		while (temp->next) 
		temp = temp->next;
		temp->next = new_node;
	}
}


void add_redir_node(t_redir **list, t_redir *new_node)
{
	t_redir *temp;

	if (!*list) 
		*list = new_node;
	else 
	{
		temp = *list;
		while (temp->next) 
		temp = temp->next;
		temp->next = new_node;
	}
}


void add_cmd_node(t_parse **list, t_parse *new_node) 
{
	t_parse *temp;


	if (!*list)
		*list = new_node;
	else
	{
		temp = *list;
		while (temp->next) 
		temp = temp->next;
		temp->next = new_node;
	}
}


void parse_input(t_token *tokens, t_parse **parse) 
{
   t_parse *cmd_head;
	t_parse *cmd;
	t_args *args;;
	t_redir *redir;

	while (tokens)
     	{
		cmd = NULL;
		args = NULL;
		redir = NULL;
		
		while (tokens && tokens->type != TOKEN_PIPE)
		{
			if (tokens->type == TOKEN_IN)
			{
				add_redir_node(&redir, redir_node(tokens->next->value, REDIR_IN));
				tokens = tokens->next->next;
			}
			else if (tokens->type == TOKEN_OUT)
			{
				add_redir_node(&redir, redir_node(tokens->next->value, REDIR_OUT));
				tokens = tokens->next->next;
			}
			else if (tokens->type == TOKEN_APPEND)
			{
				add_redir_node(&redir, redir_node(tokens->next->value, REDIR_APPEND));
				tokens = tokens->next->next;
			}
			else if (tokens->type == TOKEN_HERE)
			{
				add_redir_node(&redir, redir_node(tokens->next->value, REDIR_HERE));
				tokens = tokens->next->next;
			}
			else
			{
				add_args_node(&args, args_node(tokens->value));
				tokens = tokens->next;
			}
		}
		add_cmd_node(&cmd_head, cmd_node( args, redir));
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}     	
	*parse = cmd_head;
}


