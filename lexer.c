#include "include/minishell.h"

int quote_word(t_mini *prog, t_token **head, int i)
{
    char *ptr;
    int dflag = 0;
    int sflag = 0;
    int len = 0;



    //"'helllo"sdfadsf"world"
    while(prog->line[i + len])
    {
        if(dflag == 0 && sflag == 0)
          {
            if(ft_isspace(prog->line[i + len]))
                break;
          }
        if( prog->line[i + len] == '\"' && sflag == 0)
                 dflag = !dflag;
         if(  prog->line[i + len] == '\'' && dflag == 0)
               sflag = !sflag;
        len++;
    }
    ptr = malloc(sizeof(char) * (len + 1));
    if (!ptr) 
    {
        perror("malloc");
        exit(1);
    }
    ft_strncpy(ptr, prog->line + i, len + 1);
    ptr[len] = '\0';
    addback_node(head, create_newnode(TOKEN_WORD, ptr));
    return (len);
}

int le_word(t_mini *prog, t_token **head, int i)
{
    char *ptr;
    int len;

      len = 0;
    while (prog->line[i + len] && !ft_isspace(prog->line[i + len]) && prog->line[i + len] != '|' &&
           prog->line[i + len] != '>' && prog->line[i + len] != '<')
           {
                   len++;
           }
    ptr = malloc(sizeof(char) * (len + 1));
    if (!ptr) 
    {
        perror("malloc");
        exit(1);
    }
    ft_strncpy(ptr, prog->line + i, len + 1);
       ptr[len] = '\0';
    addback_node(head, create_newnode(TOKEN_WORD, ptr));

    return (len);
}

void ft_lexer(t_mini *prog, t_token **head)
{
    int i;

   i = 0;
  while (prog->line[i]) 
  {
    while(ft_isspace(prog->line[i]))
              i++;
    if (prog->line[i] == '\0')
        break;
    
    if (prog->line[i] == '|') 
            addback_node(head, create_newnode(TOKEN_PIPE, "|"));
    else if (prog->line[i] == '>' && prog->line[i + 1] == '>' && ++i) 
            addback_node(head, create_newnode(TOKEN_APPEND, ">>"));
    else if (prog->line[i] == '>' && prog->line[i + 1] != '>')
            addback_node(head, create_newnode(TOKEN_OUT, ">"));
    else if (prog->line[i] == '<' && prog->line[i + 1] == '<' && ++i) 
            addback_node(head, create_newnode(TOKEN_HERE , "<<"));
    else if (prog->line[i] == '<' && prog->line[i + 1] != '<')
            addback_node(head, create_newnode(TOKEN_IN, "<"));
    else if (prog->line[i] == '\"' || prog->line[i] == '\'')
           i += quote_word(prog, head, i) - 1;
    else if (prog->line[i] != '\0')
               i += le_word(prog, head, i) - 1;                
    i++;
    }
}
