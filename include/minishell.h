#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
#include <sys/wait.h>

// # define DOUBLE_QOUTE 1
// # define  SINGLE_QOUTE 2
// # define HASH_SPACE 4
 
 typedef struct s_global
 {
	int g_qoutes;
	
 } t_global;

typedef enum
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_OUT,
	TOKEN_APPEND,
	TOKEN_HERE,
	TOKEN_IN,
}					t_type;

typedef struct s_token
{
	t_type			type;
  char			*value;
//   int 			flag;
	struct s_token	*next;
}					t_token;
/*-----------------------parsing---------------*/
typedef enum
{
	REDIR_IN,
	REDIR_HERE,
	REDIR_OUT,
	REDIR_APPEND
}		t_redir_enum;

typedef struct s_redir
{
   char *filename;
   t_redir_enum	type;
   int red_in;
   int red_out;
   struct s_redir *next;
} t_redir;

typedef struct s_args
{
	char *content;
	struct s_args *next;
}t_args;
typedef struct s_parse
{
  t_args	*cmd_args;
  t_redir	*redir_list;
  struct s_parse *next;
} t_parse;

typedef struct s_expand
{
	t_type	type;
	char	*value;
	struct s_expand *next;

} t_expand;

typedef struct s_mini
{
	char			*line;

}					t_mini;

int					ft_isspace(char c);
char				*ft_strdup(const char *s);
void				addback_node(t_token **head, t_type tnum, char *value);
t_token				*create_newnode(t_type new_type, char *new_value);
void				print_error(char *error);
void				init_data(t_mini *prog);
// void				ft_parsing(t_mini *prog, t_token **head);
void				ft_lexer(t_mini *prog, t_token **head);
// void				print_token(t_token *head);////////
void				free_token_list(t_token **head);
int					check_quotes(t_mini *prog);
int					check_syntax_errors(t_token *head);
void				parse_input(t_token *tokens, t_parse **parse);
int					ft_here_doc(t_token **token);
char				*concatenation(char *str);
char				*is_qoutes(char *str, int *qoutes);
int					check_qoutes(char *str);
int					check_dollar(char *str);
// int					special_char(char c);
char				*ft_expand(char *line);
void				change_value_node(t_token *token, char *filename);
char				*random_file(void);

#endif
