#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>//para pid_t
#include <sys/wait.h>
#include <signal.h> //para signaction
#include <unistd.h>
#include <errno.h>
#define TAM 28

/*programa que temporiza la ejecución de un proceso hijo */

	pid_t hijo;
void usage(){
	fprintf(stderr, "Usage ./signalsyfork <command> [-opt]\n");
}
void killnow(){
	kill(hijo,SIGKILL);
}
void crearProcesoHijo(char * comando,char **opciones){
	hijo=fork();
	if(hijo==0){
		//while (1); descomentar para que se pare con la alarma
		execvp(comando,opciones);
	}
	else {
		struct sigaction signalhijo= {0};
		signalhijo.sa_sigaction=killnow;
		sigaction(SIGALRM, &signalhijo, NULL);

		struct sigaction signalIgnored;
		signalIgnored.sa_handler=SIG_IGN;
		sigaction(SIGINT,&signalIgnored,NULL);
		alarm(5);
		int i,estado;
		while ((i=wait(&estado))==-1&&errno==EINTR);

		if(WIFEXITED(estado)){
			printf("Proceso finalizado sin señal\n");
		}else
			printf("Proceso finalizado con la señal\n");
		
	}
}

int main(int argc, char **argv)
{
	if (argc <= 1){
		usage();
		exit(EXIT_FAILURE);
	}
	int opt;
	while((opt=getopt(argc,argv,"abcdefghijclmnopqrstuvwxyz"))!=-1);

	char *comando=argv[optind];
	if(optind!=1){
		argv[optind] = argv[1];
		argv[1] = comando;
	}
	crearProcesoHijo(comando,argv+1);
	
	return 0;
}
