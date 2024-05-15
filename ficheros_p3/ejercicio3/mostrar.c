#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

const int TAM = 1;
void mostrar(int fdo)
{
	char *arr;
	int s;
	s = read(fdo, arr, TAM);
	while (s == TAM)
	{
		write(STDOUT_FILENO, arr, TAM);
		s = read(fdo, arr, TAM);
	}
	// write(fdd, arr, s);
}
void usage(){
	fprintf(stderr, "Usage ./mostrar <fileIn> [-n N > 0 | -e]\n");
}

//int main()
int main(int argc,char *argv[])
{
	// int argc=5;
	// char *argv1="check_mostrar";
	// char *argv2="-n";
	// char *argv3="10";
	// char *argv4="-e";
	// char *argv[]={argv1,argv2,argv3,argv4};

	int opt, N,tamN, fdo, pos,end;
	N=0;
	while ((opt = getopt(argc, argv, "n:e")) != -1)
	{
		switch (opt)
		{
		case 'n':
			N=atoi(optarg);
			if(N==0){
				usage();
				exit(EXIT_FAILURE);
			}
			break;
		case 'e':
			end=SEEK_END;
			break;
		default:
			break;
		}
	}
	if(optind>=argc){
		fprintf(stderr,"Invalid FileIn\n");
		usage();
		exit(EXIT_FAILURE);
	}
	fdo=open(argv[optind],O_RDONLY);
	if (fdo == -1)
	{
		fprintf(stderr, "no se pudo abrir fileIn\n");
		exit(EXIT_FAILURE);
	}
	if(end!=SEEK_END)
		lseek(fdo, N, SEEK_SET);
	else
		lseek(fdo, -N, SEEK_END);
	mostrar(fdo);
	close(fdo);

	return 0;
}
