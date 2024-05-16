#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define TAM 5

struct Datos{
	int num;
	char c;
};
void *thread_usuario(void *arg)
{
	struct Datos *datos=(struct Datos*)arg;
	printf("Soy el hilo %d con pthself: %ld y estoy ejecutandome, prioridad: %c \n",datos->num,pthread_self(),datos->c);
	pthread_exit(0);
}

int main(int argc, char* argv[])
{
	pthread_t hilos[TAM];
	pthread_attr_t attr;
	struct Datos datos[TAM];
	pthread_attr_init(&attr);
	for (int i = 0; i < TAM; i++)
	{
		datos[i].num=i;
		if (i % 2 == 0)
			datos[i].c = 'P';
		else
			datos[i].c = 'N';
		pthread_create(&hilos[i], &attr, thread_usuario, &datos[i]);
	}
	for (int i = 0; i < TAM; i++)
	{
		pthread_join(hilos[i],NULL);
	}
	
	pthread_attr_destroy(&attr);

	return 0;
}
