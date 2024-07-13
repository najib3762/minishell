#include <stdio.h>
#include <stdlib.h>


int main (int ac, char **av)

{

    char *ptr;


    ptr = getenv(av[1]);
    if(ptr == NULL)
          {
                printf("The value of %s is %s\n", av[1], ptr);
                return (0);
          }

    printf("%s\n", ptr);


    return (0);
}