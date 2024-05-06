#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>	  /* For O_* constants */
#include <semaphore.h>
#include <signal.h>

#define NUMITER 3

int getServingsFromPot(void)
{
	//INTENTO SERVIRME 

	//SI ESTA EL CALDERO VACIO NOTIFICO

	//ESPERO QUE ME SIRVAN LA RACION
	//MENORO UNA RACION AL COCINERO
}

void eat(void)
{
	unsigned long id = (unsigned long) getpid();
	printf("Savage %lu eating\n", id);
	sleep(rand() % 5);
}

void savages(void)
{
	//PIDO COMIDA Y DESPUES COMO
}

int main(int argc, char *argv[])
{
	//ABRO SEMAFORO COCINERO SINO ERROR

	//ABRO SEMAFOROS Y MAPEO A LA MEMORIA COMPARTIDA

	//HAGO QUE COMA EL SALVAJE

	//LIBERO Y CIERRO SEMAFOROS

	return 0;
}
