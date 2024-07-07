#include "include/minishell.h"


#define FILENAME "/tmp/here_doc_"

char *random_file()
{
    char *filename;
    static int i;
    char *temp = NULL;

    temp = ft_itoa(i++);
    filename = ft_strjoin(FILENAME, temp);
    return (free(temp), filename);
}

void change_value_node(t_token *token, char *filename)
{
    free(token->value);
    token->value = ft_strdup("<");
    token->type = TOKEN_IN;
    free(token->next->value);
    token->next->value = filename;
    token->next->type = TOKEN_WORD;
}

char *ft_expand(char *line)
{
    char *new_line;
    int i;
    int j;
    int k;
    char var_name[100];
    char *var_value;
    int len;


     new_line = malloc(BUFSIZ);
     i = 0;
     j = 0;
    while (line[i])
    {
        if(line[i] == '$' && (ft_isdigit(line[i + 1])) && line[i + 2] != '\0') 
        {
            i+=2;
            new_line[j++] = line[i++];
            // printf("line[i]: %c\n", line[i]);
        }
    
        if (line[i] == '$' && (ft_isalpha(line[i + 1]) || ft_isdigit(line[i + 1])))
        {
            i++;
            k = 0;
            while (ft_isalpha(line[i]) || ft_isdigit(line[i]))
            {
                var_name[k++] = line[i++];
            }
            var_name[k] = '\0';

            var_value = getenv(var_name);
            if (var_value)
            {
                len = strlen(var_value);
                strncpy(new_line + j, var_value, len);
                j += len;
            }
        }
        else
        {
            new_line[j++] = line[i++];
        }
    }
    new_line[j] = '\0';
    return new_line;
}

char *concatenation(char *str)
{
    char *eof;
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    len = ft_strlen(str);
    eof = malloc(sizeof(char) * (len + 1));
    if (!eof)
    {
        perror("malloc");
        exit(1);
    }
    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            i++;
            continue;
        }
        eof[j++] = str[i++];
    }
    eof[j] = '\0';
    return (eof);   
}