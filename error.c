#include "include/minishell.h"


void print_error(char *error)
{
    write(2, error, strlen(error));
}



