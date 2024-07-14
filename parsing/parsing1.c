#include "../minishell.h"

// add_args
//create_parse_node
//create_redirection_node
//add_redirection
//t_args node

t_args	*args_node(char *content)
{
	t_args	*node;

	node = (t_args *)malloc(sizeof(t_args));
	if (!node)
		return (NULL);
	node->content = ft_strdup(content);
	node->next = NULL;
	return (node);
}

t_redir	*redir_node(char *filename, t_redir_enum type)
{
	t_redir	*node;

	node = (t_redir *)malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->filename = ft_strdup(filename);
	node->type = type;
	node->next = NULL;
	return (node);
}

t_parse	*cmd_node(t_args *cmd_args, t_redir *redir_list)
{
	t_parse	*node;

	node = (t_parse *)malloc(sizeof(t_parse));
	if (!node)
		return (NULL);
	node->cmd_args = cmd_args;
	node->redir_list = redir_list;
	node->red_in = 0;
	node->red_out = 1;
	node->next = NULL;
	return (node);
}

void	add_args_node(t_args **list, t_args *new_node)
{
	t_args	*temp;

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

void	add_redir_node(t_redir **list, t_redir *new_node)
{
	t_redir	*temp;

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

void	add_cmd_node(t_parse **list, t_parse *new_node)
{
	t_parse	*temp;

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

void	parse_redirection(t_token **temp, t_redir **redir)
{
	if ((*temp)->type == TOKEN_IN)
	{
		add_redir_node(redir, redir_node((*temp)->next->value, REDIR_IN));
		*temp = (*temp)->next->next;
	}
	else if ((*temp)->type == TOKEN_OUT)
	{
		add_redir_node(redir, redir_node((*temp)->next->value, REDIR_OUT));
		*temp = (*temp)->next->next;
	}
	else if ((*temp)->type == TOKEN_APPEND)
	{
		add_redir_node(redir, redir_node((*temp)->next->value, REDIR_APPEND));
		*temp = (*temp)->next->next;
	}
	else if ((*temp)->type == TOKEN_HERE)
	{
		add_redir_node(redir, redir_node((*temp)->next->value, REDIR_HERE));
		*temp = (*temp)->next->next;
	}
}

void	parse_token(t_token **temp, t_args **args, t_redir **redir)
{
	while (*temp && (*temp)->type != TOKEN_PIPE)
	{
		if ((*temp)->type == TOKEN_IN || (*temp)->type == TOKEN_OUT ||
			(*temp)->type == TOKEN_APPEND || (*temp)->type == TOKEN_HERE)
			parse_redirection(temp, redir);
		else
		{
			add_args_node(args, args_node((*temp)->value));
			*temp = (*temp)->next;
		}
	}
}

void	parse_input(t_token **tokens, t_parse **parse)
{
	t_parse	*cmd_head;
	t_token	*temp;
	t_args	*args;
	t_redir	*redir;

	cmd_head = NULL;
	temp = *tokens;
	while (temp)
	{
		args = NULL;
		redir = NULL;
		parse_token(&temp, &args, &redir);
		add_cmd_node(&cmd_head, cmd_node(args, redir));
		if (temp && temp->type == TOKEN_PIPE)
			temp = temp->next;
	}
	*parse = cmd_head;
}
