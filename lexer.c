#include "include/minishell.h"

int ft_sp(char c)
{
    return ((c == '>' || c == '<' || c == '|' || ft_isspace(c)));
}

int word_token(t_mini *prog, t_token **head, int i)
{
    char *ptr;
    int dflag;
    int sflag;
    int len;
    
    dflag = 0;
    sflag = 0;
    len = -1;
    while(prog->line[i + (++len)])
    {
        if(dflag == 0 && sflag == 0)
                if(prog->line[i + len] && ft_sp(prog->line[i + len]) == 1)
                      break;
        if( prog->line[i + len] == '\"' && sflag == 0)
                 dflag = !dflag;
        if(  prog->line[i + len] == '\'' && dflag == 0)
                 sflag = !sflag;
    }
    ptr = malloc(sizeof(char) * (len + 1));
    if (!ptr) 
        exit(1);
    ft_strncpy(ptr, prog->line + i, len + 1);
    ptr[len] = '\0';
    addback_node(head, create_newnode(TOKEN_WORD, ptr));
    return (len - 1);
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
    else if (prog->line[i] != '\0')
           i +=word_token(prog, head, i);              
    i++;
    }
}
