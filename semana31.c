//Esqueleto de un proceso con dos hilos

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>

void *pthread1_func();
void *pthread2_func();

int signal_received = 0;

int main()
{
    pthread_t th1, th2;

    if (pthread_create(&th1, NULL, pthread1_func, NULL) != 0)
    {
        printf("No se ha podido crear el primer hilo\n");
    }

    if (pthread_create(&th2, NULL, pthread2_func, NULL) != 0)
    {
        printf("No se ha podido crear el segundo hilo\n");
    }

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    printf("Ambos hilos han terminado\n");
    return (0);
}



void *pthread1_func()
{
    printf("Hilo 1 ejecutado\n");
    pthread_exit(NULL);
}

void *pthread2_func()
{
    printf("Hilo 2 ejecutado\n");
    pthread_exit(NULL);
}
