#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdio_ext.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

void secreto_1(int pidmon);
void secreto_2(int pidmon);
void secretos_3_4(int pidmon);
void SIGUSR2_received();
void limpia_buffer();

int main(int argc, char **argv)
{
    int pidmon = atoi(argv[1]);   //atoi convierte el primer argumento de la linea de comandos a un entero
    secreto_1(pidmon);
    getchar();
    limpia_buffer();
    secreto_2(pidmon);
    getchar();
    limpia_buffer();
    secretos_3_4(pidmon);
  
    return (0);
}

void secreto_1(int pidmon)
{
    kill(pidmon, 10);            //envia al proceso monitor la señal SIGUSR1
    sleep(5);
    printf("Ejercicio1 terminado, introduce ENTER\n");
}

void secreto_2(int pidmon)
{
    kill(pidmon, 10);
    signal(SIGUSR2, SIGUSR2_received);  //configuro el proceso para recibir la señal SIGUSR2
    pause(); 
    kill(pidmon, SIGUSR2);
    printf("Ejercicio2 terminado, introduce ENTER\n");
}

void secretos_3_4(int pidmon)  //falta añadir comprobaciones
{
    //codigo del secreto 4
    kill(pidmon, 10); //señal de arranque
    sleep(1);
    int id1 = fork(); //creo hijo 1
    int id2;
    if (id1 != 0) //caundo el padre tiene el control
    {
        id2 = fork();     //crea un segundo hijo
        kill(pidmon, 10); //avisa al monitor de que se han creado dos hijos
        printf("Ejercicio3 terminado, introduce ENTER\n");
        wait(NULL);
    }

    //ahora ejecuta el secreto 4, revisar como separar esto en dos funciones
    getchar();
    limpia_buffer();
    if (id1 == 0) //si tiene el control el hijo1
    {
        signal(SIGUSR2, SIGUSR2_received);
        pause();
        printf("hijo 1 de proceso4 ha recibido la señal\n");
    }
}

void SIGUSR2_received(int pidmon)
{
    printf("Señal SIGUSR2 recibida de monitor\n");
}

void limpia_buffer()
{
    fflush(stdin);
    __fpurge(stdout);
}