#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define CAPACITY 5
#define VIPSTR(vip) ((vip) ? "  vip  " : "not vip")

pthread_mutex_t mutex;
pthread_cond_t vcAforo;

int aforoActual=0;
int nturno,vturno=0;
int vticket,nticket=0;
int n_vips_esperando = 0;

struct P{
	int id;
	int tipo;
};

void enter_normal_client(int id){
	int miturno;

	//mutex lock
	pthread_mutex_lock(&mutex);

	miturno = nticket++;

	while(aforoActual >= CAPACITY|| miturno != nturno || n_vips_esperando > 0){
		//wait
		pthread_cond_wait(&vcAforo, &mutex);
	}
	//descomentar para que surga el mal comportamiento
	//printf("No vip entrando\n"); 

	aforoActual++;
	nturno++;

	//broadcast
	pthread_cond_broadcast(&vcAforo);

	//mutex unlock
	pthread_mutex_unlock(&mutex);

}

void enter_vip_client(int id){
	int miturno;

	//mutex lock
	pthread_mutex_lock(&mutex);
	miturno = vticket++;
	n_vips_esperando++;
	while(aforoActual >= CAPACITY || miturno != vturno){
	//		wait(varcon, m);
		pthread_cond_wait(&vcAforo, &mutex);

	}

	//descomentar para que surga el mal comportamiento
	//printf("Vip entrando\n");
	n_vips_esperando--;
	aforoActual++;
	vturno++;

	//Broadcast
	pthread_cond_broadcast(&vcAforo);

	//mutex unlock
	pthread_mutex_unlock(&mutex);
}

void dance(int id, int isvip){
	printf("Client %2d (%s) dancing in disco\n", id, VIPSTR(isvip));
	sleep((rand() % 3) + 1);
}

void disco_exit(int id, int isvip){
	
	//Mutex lock
	pthread_mutex_lock(&mutex);
	
	aforoActual--;
	
	//Broadcast
	pthread_cond_broadcast(&vcAforo);

	//Mutex Unlock
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}

void *client(void *arg){
	struct P *p = (struct P *)arg;
	int isvip = p->tipo;
	if (isvip){
		enter_vip_client(p->id);
	}else{
		enter_normal_client(p->id);
	}
	dance(p->id, p->tipo);
	disco_exit(p->id, p->tipo);
}

int main(int argc, char *argv[]){
	FILE *f = fopen(argv[1], "r");

	int n;	//numero de hilos a crear
	if (f==NULL){
		printf("error al abrir el fichero:%s\n", argv[1]);
	}
	else{
		
		// lee del fichero los datos del tamaño del segundo argumento y los almacena en la variable o variables del tercer o siguientes argumentos
		fscanf(f, "%d", &n); 
		pthread_attr_t attr;
		pthread_t phs[n];
		
		pthread_mutex_init(&mutex,  NULL);
		pthread_cond_init(&vcAforo,NULL);
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		for (int i = 0; i < n; i++){

			struct P* ptrp=malloc(sizeof(struct P));
			
			fscanf(f, "%d", &ptrp->tipo);
			ptrp->id= i;
			pthread_create(&phs[i], &attr, client, ptrp);
		}

		for (int i = 0; i < n; i++){
			pthread_join(phs[i], NULL);
		}
		
		pthread_mutex_destroy(&mutex);
 		pthread_cond_destroy(&vcAforo);
	}

	return 0;
}