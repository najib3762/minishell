#include "include/minishell.h"



//   if(ft_strncmp(prog.line, "exit", ft_strlen("exit")) == 0)
//         {
//             free(prog.line);
//             free_token_list(&head);
//             free_parse_list(&parse);
//           break;
//         }

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
}

char	*my_getenv(char *name, char *env)
{
	int		i;
    char    *value;
    int j;

	i = 0;
    j = 0;
    value = malloc(BUFSIZ);

		while (env[i] && env[i] != '=')
                value[j++] = env[i++];
        value[j] = '\0';
		if (ft_strcmp(value, name) == 0)
		{
            free(value);
            return (&env[i] + 1);
		
		}
		free(value);
	return (NULL);
}

char *get_env_value(char *key, t_list *env)
{
    t_list *temp;
    char *value;

    temp = env;
    while (temp)
    {
        value = my_getenv(key, temp->content);
        if (value)
            return (value);
         
        temp = temp->next;
    }
    return (NULL);
}

int main (int ac, char **av, char **env)
{
    t_mini prog;
    char *key;
    char *value;
     init_data(ac, env, &prog);

     key = "HOME";
    value = get_env_value(key, prog.env_head);
    printf("Value of %s is %s\n", key, value);

    key = "USER";
    value = get_env_value(key, prog.env_head);
    printf("Value of %s is %s\n", key, value);

    key = "PATH";
    value = get_env_value(key, prog.env_head);
    printf("Value of %s is %s\n", key, value);

    return 0;

}