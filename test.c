#include "include/minishell.h"

char *remove_quotes(char *str)
{
    char *ptr;
    int i;
    int start;
    int length;
    char quote;

     
    i = 0;

        if(str[i] == '\"' || str == '\'')
        {
            start = i;
            if(str == '\"')
                 quote = '\"';
            else
                 quote = '\'';
                i++;
            while(str[i] && str[i] != quote && !ft_isspace(str[i + 1]))
                     i++;
            i++;
        }
             length = i - start;
        ptr = malloc(sizeof(char) * (length + 1));
        if (!ptr)
        {
            perror("malloc");
            exit(1);
        }
        ft_strncpy(ptr, str + start, length + 1);
        ptr[length] = '\0';
        return ptr;
}

int main()
{
    char *str = "\"hello world\"";
    char *new_str;

    new_str = remove_quotes(str);
    printf("%s\n", new_str);
    return 0;
}