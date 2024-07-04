#include "include/minishell.h"
#include "include/libft.h"

void print_lexer(t_token *head)
{
    t_token *temp = head;

    while (temp)
    {
      if(temp->type == TOKEN_WORD)
        printf("word: %s\n",temp->value);
      else if(temp->type == TOKEN_PIPE)
        printf("pipe: %s\n",temp->value);
      else if(temp->type == TOKEN_OUT)
        printf("out: %s\n",temp->value);
      else if(temp->type == TOKEN_APPEND)
        printf("append: %s\n",temp->value);
      else if(temp->type == TOKEN_HERE)
        printf("here: %s\n",temp->value);
      else if(temp->type == TOKEN_IN)
        printf("in: %s\n",temp->value);
        temp = temp->next;
    }
}
void free_parse_list(t_parse **head)
{
  t_parse *temp_parse;

  while (*head)
  {
    temp_parse = *head;
    *head = (*head)->next;

    t_args *temp_args;
    while (temp_parse->cmd_args)
    {
      temp_args = temp_parse->cmd_args;
      temp_parse->cmd_args = temp_parse->cmd_args->next;
      free(temp_args->content);
      free(temp_args);
    }

    t_redir *temp_redir;
    while (temp_parse->redir_list)
    {
      temp_redir = temp_parse->redir_list;
      temp_parse->redir_list = temp_parse->redir_list->next;
      free(temp_redir->filename);
      free(temp_redir);
    }

    free(temp_parse);
  }
}

void print_parse(t_parse **parse) 
{
	t_parse *temp = *parse;
	t_args *args;
	t_redir *redir;

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
			printf("%s ---> ", redir->filename);
			redir = redir->next;
		}
    printf("\n");
		temp = temp->next;
	}
}

int main (int ac, char **av, char **envp)
{
   t_mini prog;
   t_token  *head;
   t_parse  *parse;
  //  t_expand *root;

  (void)envp;
  (void)ac;
  (void)av;
  head = NULL;
   init_data(&prog);
    prog.line = readline("Minishell: ");
    if (!prog.line)
    {
        perror("readline");
        exit(1);
    }
   
    while (1)
    {
        if(ft_strcmp(prog.line, "exit") == 0)
        {
            free(prog.line);
            free_token_list(&head);
          break;
        }
        if (check_quotes(&prog) == 1)
        {
            ft_lexer(&prog, &head);
            print_lexer(head);
            // here_doc(&head);
            if(!check_syntax_errors(head))
            {
              // ft_expand(&head, &root);
            parse_input(head , &parse);
            // print_parse(&parse);
            free_parse_list(&parse);
            }
            free_token_list(&head);
        }
        add_history(prog.line);
        free(prog.line);
        prog.line = readline("Minishell: ");
        if (!prog.line)
        {
            perror("readline");
            exit(1);
        }
    }
  return (0);  
}
