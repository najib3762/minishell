#ifndef MINISHELL_H
# define MINISHELL_H

# include "include/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
#include <sys/wait.h>

 typedef struct s_free
 {
	 void *address;
	 struct s_free *next;
 } t_free;

 typedef struct s_global
 {
	int g_qoutes;
	int g_status;
	t_free *address;
 } t_global;

extern t_global g_global;
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
	struct s_token	*next;
}					t_token;
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
   int red_in;
   int red_out;
  struct s_parse *next;
} t_parse;

typedef struct s_fd
{
	int fd;
	struct s_fd *next;
} t_fd;
typedef struct s_mini
{
	char			*line;
    t_list			*env_head;
	t_fd 			*fd_head;
	int 			**fd;
}					t_mini;

int					ft_isspace(char c);
char				*ft_strdup(const char *s);
void				addback_node(t_token **head, t_token *new_node);
t_token				*create_newnode(t_type new_type, char *new_value);
void				print_error(char *error);
void				init_data(int ac, char **env, t_mini *prog);
void				ft_lexer(t_mini *prog, t_token **head);
void				free_token_list(t_token **head);
int					check_quotes(t_mini *prog);
int					check_syntax_errors(t_token **head);
void				parse_input(t_token **tokens, t_parse **parse);
int					ft_here_doc(t_token **token, t_mini *prog);
char				*skip_quotes(char *str);
char				*is_qoutes(char *str, int *qoutes);
int					check_qoutes(char *str);
int					check_dollar(char *str);
char				*ft_expand(char *line, t_mini *prog);
void				change_value(t_token *token, char *filename);
char				*random_file(void);
void				free_address(t_free **head);
t_free				*newnode_free(void *content);
void				addback_node_free(t_free **head, t_free *new);
void				r_quotes(t_token **head);
int					calcule_qoutes(char *str);
int					check_qoutes(char *str);
char				*ft_strdup_char(char c);
char				*ft_strjoin_char(char *s1, char c);
char				*my_strjoin(char *s1, char *s2);
char				*my_getenv(char *name, char *env);
char				*get_env_value(char *key, t_list *env);
char				*take_var_name(char *str, int *i);
char				*my_strdup(char *str, int len);
void				real_expand(t_token **head, t_mini *prog);
char				*ft_expand(char *line, t_mini *prog);
int					*retur_value(int flag);
void				sig_here_doc(int sig);
int					my_handle(void);
char				*ft_pwd(int i);
void				ft_env(t_args **env);
void				ft_export(t_args **env, t_args **export_list, 
					char *var_name, char *var_value);


#endif
