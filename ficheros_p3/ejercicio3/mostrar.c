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

int main(int argc, char *argv[])
{
	if (argc > 5 || argc < 4)
	{
		fprintf(stderr, "Usage %s <fileIn> [-n N] [-e]\n", argv[0]);
		exit(1);
	}
	int opt, N, fdo, pos;
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
		N = argv[optind];
		fprintf(stderr, "salto de : %d", N);
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
