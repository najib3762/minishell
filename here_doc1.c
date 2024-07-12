#include "include/minishell.h"


#define FILENAME "/tmp/here_doc_"

char *random_file()
{
    char *filename;
    static int i;
    char *temp = NULL;

    temp = ft_itoa(i++);
    filename = ft_strjoin(FILENAME, temp);
    if (!filename)
    {
        perror("malloc");
        return (NULL);
    }
    return (free(temp), filename);
}

void change_value_node(t_token *token, char *filename)
{
    token->value = "<";
    token->type = TOKEN_IN;
    token->next->value = filename;
    token->next->type = TOKEN_WORD;
}

char *ft_expand(char *line, t_mini *prog)
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
        }
    
        if (line[i] == '$' && (ft_isalpha(line[i + 1]) || ft_isdigit(line[i + 1]))) 
        {
            i++;
            k = 0;
            while (ft_isalpha(line[i]) || ft_isdigit(line[i]) || line[i] == '_')
            {
                var_name[k++] = line[i++];
            }
            var_name[k] = '\0';

            var_value = get_env_value(var_name, prog->env_head);
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

int calcule_qoutes(char *str)
{
    int dflag = 0;
    int sflag = 0;
    int res = 0;
    int i = 0;

    while(str[i])
    {
        if( str[i] == '\"' && sflag == 0 )
                 {
                        res+=1;
                        dflag = !dflag;
                 }
         if( str[i] == '\'' && dflag == 0)
                    {
                         res+=1;
                        sflag = !sflag;
                    }
        i++;
    }
    return res;
}

void g_word( char *str, char *eof)
{
     int dflag = 0;
    int sflag = 0;
    int i;
    int j;

    i = 0;
    j = 0;
     while(str[i])
    {
        if( str[i] == '\"' && sflag == 0 && ++i)
                    dflag = !dflag;
         else if( str[i] == '\'' && dflag == 0 && ++i)
                    sflag = !sflag;
        else
            eof[j++] = str[i++];
    }
    eof[j] = '\0';
}

char *skip_quotes(char *str)
{
    char *eof;
    int len;
    int qoutes;

    qoutes = calcule_qoutes(str);
    len = ft_strlen(str) - qoutes;
    eof = malloc(sizeof(char) * (len + 1));
    if (!eof)
    {
        perror("malloc");
        exit(1);
    }
    g_word(str, eof);

    return (eof);   
}