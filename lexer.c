#include "include/minishell.h"


void ft_lexer(t_mini *prog, t_token **head)
{
    int i;
    int start;
    int length;
    char *ptr;


    i = 0;
   while(ft_isspace(prog->line[i]))
        i++;

  while (prog->line[i]) 
  {
    if (ft_isspace(prog->line[i])) 
    {
        i++;
        continue;
    }

   
    //   if (prog->line[i] == '"' || prog->line[i] == '\'') 
    // {
    //     quote = prog->line[i];
    //     i++;
    //     start = i;
    //     while (prog->line[i] && prog->line[i] != quote)  
    //         i++;
    //    if (prog->line[i] && prog->line[i + 1] && !ft_isspace(prog->line[i + 1])) 
    //    {
    //     while (prog->line[i] && !ft_isspace(prog->line[i])) 
    //         i++;
    //     }
    //      length = i - start;
    //         ptr = malloc(sizeof(char) * (length + 1));
    //         if (!ptr) 
    //         {
    //             perror("malloc");
    //             exit(1);
    //         }
    //         ft_strncpy(ptr, prog->line + start, length + 1);
    //         ptr[length] = '\0';
    //         if(quote == '\'')
    //         addback_node(head, TOKEN_WORD, ptr, SINGLE_QOUTE | HASH_SPACE);
    //         else
    //         addback_node(head, TOKEN_WORD, ptr, DOUBLE_QOUTE | HASH_SPACE);
    //         free(ptr);
    //         if(prog->line[i] == quote)
    //         i++;
    // } 
    if (prog->line[i] == '|') 
    {
        addback_node(head, TOKEN_PIPE, "|");
        i++;
    }
     else if (prog->line[i] == '>') 
     {
        if (prog->line[i + 1] == '>') {
            addback_node(head, TOKEN_APPEND, ">>");
            i += 2;
        } 
        else 
        {   
            addback_node(head, TOKEN_OUT, ">");
            i++;
        }
    } 
    else if (prog->line[i] == '<') 
    {
        if (prog->line[i + 1] == '<') 
        {
            addback_node(head, TOKEN_HERE, "<<");
            i += 2;
        } 
        else 
        {
            addback_node(head, TOKEN_IN, "<");
            i++;
        }
    } 
    else 
    {
        start = i;
        while (prog->line[i] && !ft_isspace(prog->line[i]) && prog->line[i] != '|' &&
               prog->line[i] != '>' && prog->line[i] != '<')
               i++;
        length = i - start;
        ptr = malloc(sizeof(char) * (length + 1));
        if (!ptr) 
        {
            perror("malloc");
            exit(1);
        }
        ft_strncpy(ptr, prog->line + start, length + 1);
        ptr[length] = '\0';
        addback_node(head, TOKEN_WORD, ptr);
        free(ptr);
    }
}
}
