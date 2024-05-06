#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>	  /* For O_* constants */
#include <semaphore.h>
#include <signal.h>

#define M 10 //raciones que puede servir del caldero
#define MAX_DATOS_MEM_COMPARTIDA 1 //*sizeof(int) //raciones que puede servir del caldero

int *buf;
sem_t *lleno;
sem_t *vacio;

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
	
	
	//abrir semaforos
	lleno=sem_open("/LLENO",O_CREAT, 0700,0);
	vacio=sem_open("/VACIO",O_CREAT, 0700,0);

	shmC = shm_open("/BUFFERC", O_CREAT|O_RDWR, S_IRUSR | S_IWUSR);// PREGUNTAR POR ESTOS FLAGS
	ftruncate(shmC, MAX_DATOS_MEM_COMPARTIDA * sizeof(int));

	buf=(int *)nmap(NULL, MAX_DATOS_MEM_COMPARTIDA * sizeof(int),PROT_WRITE,MAP_SHARED,shmC,0);
	*buf=0;

	//cocinar
	cook();

	//cerrar semaforos y desmapeo
	munmap(buf,MAX_DATOS_MEM_COMPARTIDA*sizeof(int)); // FREE DE LA MEMORIA COMPARTIDA
	close(shmC);
	unlink("/BUFFERC");
	sem_close(lleno);
	sem_close(vacio);
	sem_unlink("/LLENO");//ELIMINA EL SEMAFORO DEL PROCESO
	sem_unlink("VACIO");
	
	
	return 0;
}
