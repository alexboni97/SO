#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define CAPACITY 5
#define VIPSTR(vip) ((vip) ? "  vip  " : "not vip")

void enter_normal_client(int id)
{
}

void enter_vip_client(int id)
{
}

void dance(int id, int isvip)
{
	printf("Client %2d (%s) dancing in disco\n", id, VIPSTR(isvip));
	sleep((rand() % 3) + 1);
}

void disco_exit(int id, int isvip)
{
	pthread_exit(0);
}

void *client(void *arg)
{
	struct P *p = (struct P *)arg;
	int isvip = p->tipo;
	if (isvip)
		enter_vip_client(p->id);
	else
		enter_normal_client(p->id);
	dance(p->id, p->tipo);
	exit_client(p->id, p->tipo);
}
struct P
{
	int id;
	int tipo;
};
int main(int argc, char *argv[])
{
	FILE *f = fopen(argv[1], "r");
	int n;
	if (!isfopen(f))
	{
		fprintf("error al abrir el fichero:%s\n", argv[1]);
	}
	else
	{

		fscanf(f, "%d", n);
		pthread_attr_t attr;
		pthread_t phs[n];

		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		struct P p;
		for (int i = 0; i < n; i++)
		{

			fscanf(f, "%d", p->second);
			p->first = i;
			pthread_create(&phs[i], &attr, client(p), NULL);
		}
	}

	return 0;
}