#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

}

void *client(void *arg)
{

}

int main(int argc, char *argv[])
{
	FILE *f=fopen(argv[1],"r");
	int n;
	if(!isfopen(f)){
		fprintf("error al abrir el fichero:%s\n",argv[1]);
	}
	else{
		
		fscanf(f,"%d",n);
		int *personas=malloc(sizeof(int)*n);
		for(int i=0;i<n;i++){
			fscanf(f,"%d",personas[i]);
		}
	}

	return 0;
}
