#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void    func_hijo1();
void    func_hijo2();

int main()
{
	int pid1, pid2;

    if ((pid1 = fork()) == -1) //se crea el hijo 1
    {
        printf("No se ha podido crear el hijo 1\n"); //fork devuelve -1 en caso de error
    }

    if (pid1 == 0)
    {
        func_hijo1();
    }
    else
    {
        if ((pid2 = fork()) == -1) //se crea el hijo 2
        {
            printf("No se ha podido crear el hijo 2\n"); //fork devuelve -1 en caso de error
        }
    }
    if (pid2 == 0)
    {
        func_hijo2();
    }

    if (pid1 != 0 && pid2 != 0)
    {
        wait(NULL);
        wait(NULL);
        printf("Hola desde padre\n");
        return (0);
    }
}

void func_hijo1()
{
    printf("Hola desde hijo 1 con ID %d\n", getpid());
}

void func_hijo2()
{
    printf("Hola desde hijo 2 con ID %d\n", getpid());
}


/*
PRIMERA PARTE

H2 captura info por teclado, y hijo 1
avisa de que la informacion está lista,
la recoja y la traduzca a mayusculas para
imprimirla por pantalla

SEGUNDA PARTE

Monitor


SEÑALES

Metodos para comunicar de forma sencilla.
Informa a un proceso de que ha ocurrido un
evento. Un proceso puede asignar una acción
cuando reciba dicha señal. 

kill(), pause()..

signal(num_señal, rutina a ejecutar)

el hijo se prepara para convertir a mayusculas
tras recibir cierto numero de señal

SIGUSR puedens er usadas por el usuario

identifico las señales mediante numeros

kill(pid, num_señal)
Envia una señal a cierto proceso

pause()
Espera a recibir una señal
*/

/*
CODIGO

Hijo 1 hace un signal para prepararse y luego espera
con pause. Hijo 2 captura una cadena con fgets, crea un fichero
y escribe el string recibido, asegurando antes que el fichero
está bien creado. Manda la señal con kill y el hijo1 

exit() es la forma de salir, como un return() pero desde una funcion
*/
