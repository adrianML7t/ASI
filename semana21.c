#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

#define MAX_TAM 100

void get_message(char *buffer);
void SIGUSR1_received(int sign);

int main()
{
	int pid1, pid2;

    if ((pid1 = fork()) == -1) //se crea el hijo 1
    {
        printf("No se ha podido crear el hijo 1\n"); //fork devuelve -1 en caso de error
    }

    if (pid1 == 0)
    {
        char buffer[MAX_TAM];

        printf("Hijo 1\n");
        signal(SIGUSR1, SIGUSR1_received);
        pause();
        printf("Señal recibida\n");

        FILE *fd = fopen("Msg.txt", "r");
        fread(buffer, sizeof(char), MAX_TAM, fd);
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
        puts(msg);

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

    if (pid1 != 0 && pid2 != 0)
    {
        wait(NULL);
        wait(NULL);
        printf("Hola desde padre\n");
        return (0);
    }
}

void SIGUSR1_received(int sign)
{

}

void get_message(char *buffer)
{
    printf("Introduce la cadena a leer: ");
    fgets(buffer, MAX_TAM, stdin);

    if (buffer[strlen(buffer) - 1] == '\n')
    {
        buffer[strlen(buffer) - 1] = '\0';
    }
}
