#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>	  /* For O_* constants */
#include <semaphore.h>
#include <signal.h>

#define NUMITER 20
#define MAX_DATOS_MEM_COMPARTIDA 1 //*sizeof(int) //tamaño del buffer que van a compartir y modificar los procesos 

int *buf;
sem_t *lleno;
sem_t *vacio;

int getServingsFromPot(void)
{
	//SI ESTA EL CALDERO VACIO NOTIFICO
	if(*buf<=0){
		sem_post(vacio);
		sem_wait(lleno);
	}
	//MENORO UNA RACION AL COCINERO
	*buf -= 1;
	//ESPERO QUE ME SIRVAN LA RACION
	unsigned long id = (unsigned long) getpid();
	printf("Savage %lu. servings pot n %d .\n", id, *buf);
}

void eat(void)
{
	unsigned long id = (unsigned long) getpid();
	printf("Savage %lu eating\n", id);
	sleep(rand() % 5);
}

void savages(void)
{
	for (int i = 0; i < NUMITER; i++)
	{
		//me sirvo COMIDA Y DESPUES COMO
		getServingsFromPot();
		eat();
	}
	
	kill(-1,SIGINT);
}

int main(int argc, char *argv[])
{
	//ABRO SEMAFORO COCINERO SINO ERROR
	int shmC;
	//ABRO SEMAFOROS Y MAPEO A LA MEMORIA COMPARTIDA
	
	if((shmC = shm_open("/BUF", O_RDWR, S_IRUSR | S_IWUSR))==-1){
		printf("NO HAY COCINERO\n");
		exit(-1);
	} // PREGUNTAR POR ESTOS FLAGS
	lleno=sem_open("/LLENO",0);
	vacio=sem_open("/VACIO",0);
	ftruncate(shmC,MAX_DATOS_MEM_COMPARTIDA*sizeof(int));

	buf=(int *)mmap(NULL, MAX_DATOS_MEM_COMPARTIDA * sizeof(int),PROT_WRITE,MAP_SHARED,shmC,0);

	//HAGO QUE COMA EL SALVAJE
	savages();

	//LIBERO Y CIERRO SEMAFOROS
	munmap(buf,MAX_DATOS_MEM_COMPARTIDA*sizeof(int));
	close(shmC);
	sem_close(lleno);
	sem_close(vacio);
	
	return 0;
}
