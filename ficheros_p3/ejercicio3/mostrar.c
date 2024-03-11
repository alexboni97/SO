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

//int main()
int main(int argc,char *argv[])
{
	// int argc=5;
	// char *argv1="check_mostrar";
	// char *argv2="-n";
	// char *argv3="10";
	// char *argv4="-e";
	// char *argv[]={argv1,argv2,argv3,argv4};
	if (argc > 5 || argc < 4)
	{
		fprintf(stderr, "Usage %s <fileIn> [-n N] [-e]\n", argv[0]);
		exit(1);
	}
	int opt, N,tamN, fdo, pos;
	opt = getopt(argc, argv, "n");
	if (opt == 'n')
	{
		fdo = open(argv[1], O_RDONLY);
		if (fdo == -1)
		{
			fprintf(stderr, "no se pudo abrir fileIn");
			exit(1);
		}
		if (optind >= argc)
		{
			fprintf(stderr, "tiene que tener un valor la opcion -n");
			close(fdo);
			exit(1);
		}
		//N = atoi(optarg); //preguntar profe porque en el manual hay este ejemplo y no funciona
		////N=atoi(argv[optind]);
		// //N=*argv[optind]-'0';//valido si solo tiene un caracter
		//strtol((optarg,NULL,10))
		char *salto=argv[optind];
		tamN=strlen(salto);
		N=0;
		for(int i=0;i<tamN;i++){
			N= 10*N + salto[i]-'0';
		}
		opt = getopt(argc, argv, "e");
		if (opt == -1)
		{
			lseek(fdo, N, SEEK_SET);
			mostrar(fdo);
		}
		else if (opt == 'e')
		{
			pos = lseek(fdo, -N, SEEK_END);
			mostrar(fdo);
		}
		else
		{
			fprintf(stderr, "opcion invalida: %c", opt);
			close(fdo);
			exit(1);
		}
		close(fdo);
	}

	return 0;
}