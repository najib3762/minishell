#include <stdio.h>
#include <stdlib.h>


int main (int ac, char **av)

{

    char *ptr;


    ptr = getenv(av[1]);
    printf("%s\n", ptr);


    return (0);
}