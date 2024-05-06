#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>	  /* For O_* constants */
#include <semaphore.h>
#include <signal.h>

#define M 10 //raciones que puede servir del caldero
#define MAX_DATOS_MEM_COMPARTIDA 100 //*sizeof(int) //raciones que puede servir del caldero

int *buf;
sem_t *racionesPreparadas;
sem_t *calderoVacio;

int finish = 0;

void putServingsInPot(int servings)
{
	//FOR SERVINGS SEMPOST RACINESPREPARADAS
}

void cook(void)
{
	while(!finish) {
		putServingsInPot(M);
	}
}

void handler(int signo)
{
	finish = 1;
}

int main(int argc, char *argv[])
{
	int shmC;
	signal(SIGINT,handler);
	signal(SIGTERM,handler);

	shmC=shm_open("/BUFFERC",O_CREAT|O_RDWR,S_IRUSR | S_IWUSR);// PREGUNTAR POR ESTOS FLAGS
	ftruncate(shmC,MAX_DATOS_MEM_COMPARTIDA*sizeof(int));

	buf=(int *)nmap(NULL, MAX_DATOS_MEM_COMPARTIDA*sizeof(int),PROT_WRITE,MAP_SHARED,shdC,0);
	*buf=0;
	
	//abrir semaforos
	racionesPreparadas=sem_open("/RACIONESP",O_CREAT, 0700,0);
	racionesPreparadas=sem_open("/VACIOCAL",O_CREAT, 0700,0);

	//cocinar
	cook();

	//cerrar semaforos y desmapeo
	munmap(buf,MAX_DATOS_MEM_COMPARTIDA*sizeof(int));
	close(shmC);
	unlink("/BUFFERC");
	sem_close(racionesPreparadas);
	sem_close(calderoVacio);
	sem_unlink("/RACIONESP");
	sem_unlink("VACIOCAL");
	return 0;
}
