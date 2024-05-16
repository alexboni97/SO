#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>	  /* For O_* constants */
#include <semaphore.h>
#include <signal.h>

#define NUMITER 3

int *buf;
sem_t *racionesPreparadas;
sem_t *calderoVacio;

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
	getServingsFromPot();
	eat();
	//PIDO COMIDA Y DESPUES COMO
}

int main(int argc, char *argv[])
{
	//ABRO SEMAFORO COCINERO SINO ERROR
	int shmC;
	//ABRO SEMAFOROS Y MAPEO A LA MEMORIA COMPARTIDA
	
	racionesPreparadas=sem_open("/RACIONESP",O_RDWR, 0700,0);
	calderoVacio=sem_open("/VACIOCAL",O_RDWR, 0700,0);
	if(racionesPreparadas==-1||calderoVacio==-1){
		printf("NO HAY COCINERO\n");
		exit(-1);
	}
	shmC = shm_open("/BUFFERC", O_RDWR, S_IRUSR | S_IWUSR);// PREGUNTAR POR ESTOS FLAGS
	ftruncate(shmC,MAX_DATOS_MEM_COMPARTIDA*sizeof(int));

	buf=(int *)nmap(NULL, MAX_DATOS_MEM_COMPARTIDA * sizeof(int),PROT_WRITE,MAP_SHARED,shmC,0);

	//HAGO QUE COMA EL SALVAJE
	savages();

	//LIBERO Y CIERRO SEMAFOROS
	
	
	return 0;
}
