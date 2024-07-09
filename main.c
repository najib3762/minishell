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
    t_args *temp_args;
    t_redir *temp_redir;

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

int main ()
{
   t_mini prog;
   t_token  *head;
   t_parse  *parse;

  head = NULL;
  parse = NULL;
   init_data(&prog);
    prog.line = readline("Minishell: ");
    if (!prog.line)
    {
        perror("readline");
        exit(1);
    }
   
    while (1)
    {
        if(ft_strncmp(prog.line, "exit", ft_strlen("exit")) == 0)
        {
            free(prog.line);
            free_token_list(&head);
            free_parse_list(&parse);
          break;
        }
        if (check_quotes(&prog) == 1)
        {
             ft_lexer(&prog, &head);
            //  ft_here_doc(&head);
            
               print_lexer(head);
                break;
            if(!check_syntax_errors(head))
            {
              // ft_expand(&head);
              concatenate_lexer(&head);
              printf("\n\n\n\n");
              print_lexer(head);     
              break;
              // printf("\n\n\n"); 
            parse_input(head , &parse);
            print_parse(&parse);
            free_parse_list(&parse);
            }
            free_token_list(&head);
        }
        add_history(prog.line);
        prog.line = readline("Minishell: ");
        if (!prog.line)
            exit(1);
    
  
    }
  return (0);  
}
