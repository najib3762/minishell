#include "include/minishell.h"


char *concatunation(char *str)
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
            i++;
        eof[j] = str[i];
        i++;
        j++;
    }
    eof[j] = '\0';
    return (eof);   
}

int main (int ac, char **av)

{

    char *str = av[1];
    char *eof;  
    eof = concatunation(str);
    printf("%s\n", eof);
    return (0);
}