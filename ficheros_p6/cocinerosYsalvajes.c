#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>	  /* For O_* constants */
#include <semaphore.h>
#include <signal.h>
#include <pthread.h>

#define M 10 //raciones que puede servir del caldero 
#define N 5 //numero de cocinero mas salvajes
#define MAX_DATOS_MEM_COMPARTIDA 1 //*sizeof(int) //raciones que puede servir del caldero


/*
SOLUCION EN UN SOLO PROCESO CON MULTIHILOS
*/
int *buf;
sem_t *vacio;
sem_t *lleno;
sem_t *lock;

int finish = 0;

void putServingsInPot(int servings){
	//FOR SERVINGS SEMPOST RACINESPREPARADAS
	for(int i = 0; i < M; i++){
		
	}
}

void cook(void){
	while(!finish) {
		putServingsInPot(M);
	}
}
void eat(void)
{
	unsigned long id = (unsigned long) getpid();
	printf("Savage %lu eating\n", id);
	sleep(rand() % 5);
}
int getServingsFromPot(void)
{
	//INTENTO SERVIRME 

	//SI ESTA EL CALDERO VACIO NOTIFICO

	//ESPERO QUE ME SIRVAN LA RACION
	//MENORO UNA RACION AL COCINERO
}
void savages(void *arg){
	getServingsFromPot();
	eat();
	//PIDO COMIDA Y DESPUES COMO
}

void handler(int signo){
	finish = 1;
}

int main(int argc, char *argv[]){
	int shmC;
	signal(SIGINT,handler);
	signal(SIGTERM,handler);
	
	pthread_attr_t attr;
	pthread_t phs[N];
	sem_init(vacio);
	sem_init(lleno);
	sem_init(lock);
	int* ptrp=malloc(sizeof(int));
    pthread_create(&phs[0], &attr, cook, ptrp);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	cook();
	for (int i = 1; i < N; i++){
			*ptrp=i;
			pthread_create(&phs[i], &attr, savages, ptrp);
	}


	return 0;
}
