#include "minishell.h"
#include <pthread.h>

int num = 0;
pthread_mutex_t mutex;

void *routine(void *arg)
{
    int i = 0;
    int *res = (int *)arg;

   pthread_mutex_lock(&mutex);
    while (i < 1000000)
    {
         num++;
        i++;
    }
     printf("value : %d res = %d\n", num, *res);
    pthread_mutex_unlock(&mutex);
   
    return NULL;
}
int main ()
{

    pthread_t pthread[2];

    int *res;
    int i = 0;
     pthread_mutex_init(&mutex, NULL);
    while(i < 2)
    {
        pthread_create(&pthread[i], NULL, &routine, &i);
        i++;
    }
    
    i = 0;
    while(i < 2)
    {
        pthread_join(pthread[i], NULL);
        i++;
    }
      pthread_mutex_destroy(&mutex);
 
    // printf("num = %d\n", num);
     
    return 0;


}