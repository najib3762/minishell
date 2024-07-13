#include "include/minishell.h"



//   if(ft_strncmp(prog.line, "exit", ft_strlen("exit")) == 0)
//         {
//             free(prog.line);
//             free_token_list(&head);
//             free_parse_list(&parse);
//           break;
//         }


//   if(str[i] == '$' && (ft_isdigit(str[i + 1])) && str[i + 2] != '\0') 
//         {
//             i+=2;
//             new_str[j++] = str[i++];
//         }
//         if (str[i] == '$' && (ft_isalpha(str[i + 1]) || ft_isdigit(str[i + 1])))
//         {
//             i++;
//             k = 0;
//             while (ft_isalpha(str[i]) || ft_isdigit(str[i]))
//             {
//                 key[k++] = str[i++];
//             }
//             key[k] = '\0';
//             value = get_env_value(key, env);
//             if (value)
//             {
//                 l = ft_strlen(value);
//                 ft_strncpy(new_str + j, value, l);
//                 j += l;
//             }
//         }
// void get_env(char **env, t_list **head)
// {
//     int i;

//     i = 0;
//     while(env[i])
//     ft_lstadd_back(head,ft_lstnew(env[i++]));
// }

// void init_data(int ac, char **env, t_mini *prog) 
// {
//     prog->line = NULL;
//     prog->env_head = NULL;
//    if(ac != 1)
//       exit(1);
//     get_env(env, &prog->env_head);
// }

// char	*my_getenv(char *name, char *env)
// {
// 	int		i;
//     char    *value;
//     int j;

// 	i = 0;
//     j = 0;
//     value = malloc(BUFSIZ);

// 		while (env[i] && env[i] != '=')
//                 value[j++] = env[i++];
//         value[j] = '\0';
// 		if (ft_strcmp(value, name) == 0)
// 		{
//             free(value);
//             return (&env[i] + 1);
		
// 		}
// 		free(value);
// 	return (NULL);
// }

// char *get_env_value(char *key, t_list *env)
// {
//     t_list *temp;
//     char *value;

//     temp = env;
//     while (temp)
//     {
//         value = my_getenv(key, temp->content);
//         if (value)
//             return (value);
         
//         temp = temp->next;
//     }
//     return (NULL);
// }

// int main (int ac, char **av, char **env)
// {
//     t_mini prog;
//     char *key;
//     char *value;
//      init_data(ac, env, &prog);

//      key = "HOME";
//     value = get_env_value(key, prog.env_head);
//     printf("Value of %s is %s\n", key, value);

//     key = "USER";
//     value = get_env_value(key, prog.env_head);
//     printf("Value of %s is %s\n", key, value);

//     key = "PATH";
//     value = get_env_value(key, prog.env_head);
//     printf("Value of %s is %s\n", key, value);

//     return 0;

// }



// char *dollar_expand( char *str, t_mini *prog)
// {
//     char *new_str;
//     char var_name[100];
//     char *var_value;
//     char  double_quote[100];
//     int i;
//     int j;
//     int k;
//     int len;
//     int l;

//     i = 0;
//     j = 0;
//     k = 0;
//     len = 0;
//     new_str = malloc(BUFSIZ);

//     while(str[i])
//     {
//         if(str[i] == '$' && (ft_isdigit(str[i + 1])) && str[i + 2] != '\0') 
//         {
//             i+=2;
//             new_str[j++] = str[i++];
//         }
    
//         if (str[i] == '$' && (ft_isalpha(str[i + 1]) || ft_isdigit(str[i + 1])))
//         {
//             i++;
//             k = 0;
//             while (ft_isalpha(str[i]) || ft_isdigit(str[i]))
//             {
//                 var_name[k++] = str[i++];
//             }
//             var_name[k] = '\0';

//             var_value = get_env_value(var_name, prog->env_head);
//             if (var_value)
//             {
//                 len = ft_strlen(var_value);
//                 strncpy(new_str + j, var_value, len);
//                 j += len;
//             }
//         }
//         else if (str[i] == '\"')
//         {
//             l = 0;
//             double_quote[l++] = str[i++];
//             while(str[i] != '"')
//             {
//                 double_quote[l++] = str[i++];
//             }
//             double_quote[l++] = str[i++];
//             double_quote[l] = '\0';
           

//             char *temp = ft_expand(double_quote, prog);
//             if(temp)
//             {
//                 int l = ft_strlen(temp);
//                 strncpy(new_str + j, temp, l);
//                 j += l;
//                 free(temp);
//             }
//         }
//         else if (str[i] == '\'')
//         {
//             new_str[j++] = str[i++];
//             while(str[i] != '\'')
//             {
//                 new_str[j++] = str[i++];
//             }
//             new_str[j++] = str[i++];
//         }
//         else
//         {
//             new_str[j++] = str[i++];
//         }
//     }
//          new_str[j] = '\0';

//        return new_str;
// }



void handle_token_in(t_token **temp, t_redir **redir)
{
    add_redir_node(redir, redir_node((*temp)->next->value, REDIR_IN));
    *temp = (*temp)->next->next;
}

void handle_token_out(t_token **temp, t_redir **redir)
{
    add_redir_node(redir, redir_node((*temp)->next->value, REDIR_OUT));
    *temp = (*temp)->next->next;
}

void handle_token_append(t_token **temp, t_redir **redir)
{
    add_redir_node(redir, redir_node((*temp)->next->value, REDIR_APPEND));
    *temp = (*temp)->next->next;
}

void handle_token_here(t_token **temp, t_redir **redir)
{
    add_redir_node(redir, redir_node((*temp)->next->value, REDIR_HERE));
    *temp = (*temp)->next->next;
}

void handle_token_default(t_token **temp, t_args **args)
{
    add_args_node(args, args_node((*temp)->value));
    *temp = (*temp)->next;
}

void parse_args(t_token **temp, t_args **args, t_redir **redir)
{
    while (*temp && (*temp)->type != TOKEN_PIPE)
    {
        switch ((*temp)->type)
        {
            case TOKEN_IN:
                handle_token_in(temp, redir);
                break;
            case TOKEN_OUT:
                handle_token_out(temp, redir);
                break;
            case TOKEN_APPEND:
                handle_token_append(temp, redir);
                break;
            case TOKEN_HERE:
                handle_token_here(temp, redir);
                break;
            default:
                handle_token_default(temp, args);
                break;
        }
    }
}

void parse_input(t_token **tokens, t_parse **parse)
{
    t_parse *cmd_head = NULL;
    t_args *args = NULL;
    t_redir *redir = NULL;
    t_token *temp = *tokens;

    while (temp)
    {
        args = NULL;
        redir = NULL;
        parse_args(&temp, &args, &redir);
        add_cmd_node(&cmd_head, cmd_node(args, redir));
        if (temp && temp->type == TOKEN_PIPE)
            temp = temp->next;
    }
    *parse = cmd_head;
}







   temp->red_in = fd[i - 1][0];
        if(temp->next)
            temp->red_out = fd[i][1];
        temp = temp->next;