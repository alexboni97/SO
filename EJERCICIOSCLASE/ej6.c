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
#define N 2 //numero de personas que quiere entrar a la gasolinera y repostar
#define MAX_DATOS_MEM_COMPARTIDA 1 //*sizeof(int) //raciones que puede servir del caldero


int *buf;
sem_t sem_surtidor;//semaforo para los dos surtidores
sem_t sem_gasolinera;//semaforo para la gasolinera


int finish = 0;

void cliente(int dinero){
    int surtidor;
    sem_gasolinera.wait();
    sem_surtidor.wait();
    /*
    poner 0 en el surtidor
    despues post semaforo surtido
    */
    
}
void(){}
void(){}


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
