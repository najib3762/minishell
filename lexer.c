#include "include/minishell.h"

    // if(prog->line[i] == quote && prog->line[i + 1])
            //         {
            //             while(prog->line[i + 1] && !ft_isspace(prog->line[i + 1]))
            //                 i++;
            //         }   

void ft_lexer(t_mini *prog, t_token **head)
{
    int i;
    int start;
    int length;
    char *ptr;
    int dflag;


    i = 0;
    dflag = 0;
   while(ft_isspace(prog->line[i]))
        i++;
  while (prog->line[i]) 
  {
    if (ft_isspace(prog->line[i])) 
    {
        i++;
        continue;
    }

    if (prog->line[i] == '|') 
    {
        addback_node(head, create_newnode(TOKEN_PIPE, "|"));
        i++;
    }
     else if (prog->line[i] == '>') 
     {
        if (prog->line[i + 1] == '>') {
            addback_node(head, create_newnode(TOKEN_APPEND, ">>"));
            i += 2;
        } 
        else 
        {   
            addback_node(head, create_newnode(TOKEN_OUT, ">"));
            i++;
        }
    } 
    else if (prog->line[i] == '<') 
    {
        if (prog->line[i + 1] == '<') 
        {
            addback_node(head, create_newnode(TOKEN_HERE , "<<"));
            i += 2;
        } 
        else 
        {
            addback_node(head, create_newnode(TOKEN_IN, "<"));
            i++;
        }
    } 
    else 
    {
         if(prog->line[i] == '\"' || prog->line[i] == '\'')
        {
            start = i;
          dflag = 1;
            i++;
        while(prog->line[i])
            {
                if(dflag == 0)
                {
                    if(ft_isspace(prog->line[i]) || !prog->line[i])
                         break;
                }
                if( prog->line[i] == '\"' || prog->line[i] == '\'')
                {
                    if(dflag == 0)
                       dflag++;
                    else
                      dflag--;
                }
                i++;
            }
                i++;
        }
        else
        {
            start = i;
        while (prog->line[i] && !ft_isspace(prog->line[i]) && prog->line[i] != '|' &&
               prog->line[i] != '>' && prog->line[i] != '<')
               i++;
        }
        length = i - start;
        ptr = malloc(sizeof(char) * (length + 1));
        if (!ptr) 
        {
            perror("malloc");
            exit(1);
        }
        ft_strncpy(ptr, prog->line + start, length + 1);
        ptr[length] = '\0';
        addback_node(head, create_newnode(TOKEN_WORD, ptr));
    }
}
}
