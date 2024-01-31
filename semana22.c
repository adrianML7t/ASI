//Adrián Martínez, ASI 1ª práctica 

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

#define MAX_TAM 100                 //defino el tamaño maximo a escribir

void get_message(char *buffer);     //funcion que lee un string por pantalla con fgets de forma adecuada
void to_upper(char *str);           //funcion que convierte un string entero a mayusculas
void SIGUSR1_received(int sign);    //funcion que se ejecuta al recibir la señal SIGUSR1

int main()
{
	int pid1, pid2;

    if ((pid1 = fork()) == -1)      //se crea el hijo 1
    {
        printf("No se ha podido crear el hijo 1\n"); //fork devuelve -1 en caso de error
    }

    //Codigo que ejecuta el Hijo 1 al tener control de la CPU:
    //abrimos el fichero en modo lectura, cargamos a un buffer para posteriormente imprimir el texto por pantalla, en mayusculas
    if (pid1 == 0)                 
    {
        char buffer[MAX_TAM];

        signal(SIGUSR1, SIGUSR1_received);      //se configura la accion a realizar al recibir cierta señal
        pause();                                //se queda a la espera de recibir la señal SIGUSR1

        FILE *fd = fopen("Msg.txt", "r");       
        fread(buffer, sizeof(char), MAX_TAM, fd);
        fclose(fd);

        to_upper(buffer);
        puts(buffer);
        exit(1);
    }
    else
    {
        if ((pid2 = fork()) == -1) //se crea el hijo 2
        {
            printf("No se ha podido crear el hijo 2\n"); //fork devuelve -1 en caso de error
        }
    }

    //El hijo 2 recibe la cadena y la escribe en un fichero
    if (pid2 == 0)
    {
        char msg[MAX_TAM];
        get_message(msg);

        FILE *fd;
        fd = fopen("Msg.txt", "w");
        if (fd != NULL)
        {
            fwrite(msg, sizeof(char), sizeof(msg), fd);   
        } 

        else
        {
            printf("No se ha podido crear el fichero\n");
        }
        fclose(fd);
        kill(pid1, SIGUSR1);
        exit(2);  
    }

    //El proceso padre espera a que terminen los dos procesos antes de salir del programa
    if (pid1 != 0 && pid2 != 0)
    {
        wait(NULL);
        wait(NULL);
        return (0);
    }
}

void SIGUSR1_received(int sign)
{
    //codigo que realiza un proceso al
    //recibir la señal SIGUSR1
}

void get_message(char *buffer)
{
    printf("Introduce la cadena a leer: ");
    fgets(buffer, MAX_TAM, stdin);
    fflush(stdin);

    if (buffer[strlen(buffer) - 1] == '\n')
    {
        buffer[strlen(buffer) - 1] = '\0';
    }
}

void to_upper(char *str)
{
    while (*str != '\0')
    {
        if(*str >= 'a' && *str <= 'z')
        {
            *str = *str - 32;
        }
        str++;
    }
}