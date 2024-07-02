#include "include/minishell.h"
#include "include/libft.h"


// void print_token(t_token *head)
// {
//     t_token *current = head;
//     while (current)
//     {
//       // if(current->flag == 1)
//       // printf("====[%s] double quotes\n", current->value);
//       // else if(current->flag == 2)
//       // printf("====[%s] single quotes\n", current->value);
//       // else
//       if((current->flag & (DOUBLE_QOUTE | HASH_SPACE)) == (DOUBLE_QOUTE | HASH_SPACE))
//       printf("word DOUBLE_QOUTES SPACE===>[%s]\n", current->value);
//       else if((current->flag & (SINGLE_QOUTE | HASH_SPACE)) == (SINGLE_QOUTE | HASH_SPACE))
//       printf("word SINGLE_QOUTES SPACE===>[%s]\n", current->value);
//       else if((current->flag & (SINGLE_QOUTE)) == (SINGLE_QOUTE))
//       printf("word SINGLE_QOUTES===>[%s]\n", current->value);
//       else if((current->flag & (DOUBLE_QOUTE)) == (DOUBLE_QOUTE))
//       printf("word DOUBLE_QOUTES==>[%s]\n", current->value);
//       else if (current->type == TOKEN_WORD)
//       printf("word==>%s\n", current->value);
//       else
//       printf("else==>%s\n", current->value);
//         current = current->next;
//     }
// }

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
            if(!check_syntax_errors(head))
            {
              // ft_expand(&head, &root);
            parse_input(head , &parse);
            print_parse(&parse);
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
