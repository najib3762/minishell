#include "include/minishell.h"

void get_env(char **env, t_list **head)
{
    int i;

    i = 0;
    while(env[i])
    ft_lstadd_back(head,ft_lstnew(env[i++]));
}

void init_data(int ac, char **env, t_mini *prog) 
{
    prog->line = NULL;
    prog->env_head = NULL;
   if(ac != 1)
      exit(1);
    get_env(env, &prog->env_head);

//     *par = malloc(sizeof(t_parse));
//     if (*par == NULL) 
//     {
//         perror("malloc");
//         exit(1);
//     }
//     (*par)->cmd_args = NULL;
//     (*par)->redir_list = NULL;
//     (*par)->next = NULL;

//     *tok = malloc(sizeof(t_token));
//     if (*tok == NULL) 
//     {
//         perror("malloc");
//         exit(1);
//     }
//     (*tok)->value = NULL;
//     (*tok)->type = NULL;
//     (*tok)->next = NULL;

}


