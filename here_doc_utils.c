#include "include/minishell.h"





int check_qoutes(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] && (str[i] == '\"' || str[i] == '\''))
            return (1);
        i++;
    }
    return (0);
}

char *is_qoutes(char *str, int *qoutes)
{
    char *eof;
    
   
    if(check_qoutes(str) == 1)
       {    
        eof = concatenation(str);
        *qoutes = 1;
       }
    else
       eof = str;

    return (eof);
}

int check_dollar(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
            return (1);
        i++;
    }
    return (0);
}

// int special_char(char c)
// {
//     if (c == '?' || c == '_')
//         return (1);
//     return (0);
// }
