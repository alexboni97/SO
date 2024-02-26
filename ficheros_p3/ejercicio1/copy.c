#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

const int TAM = 512;

void copy(int fdo, int fdd)
{
	char arr[512];
	int s;
	s = read(fdo, arr, TAM);
	while (s == TAM){
		write(fdd, arr, TAM);
		s = read(fdo, arr, TAM);
	}
	write(fdd, arr, s);
}

int main(int argc, char *argv[])
{
	int filein;
	int fileout;
	int c, ret;

	if (argc != 3)
	{
		fprintf(stderr, "usage: %s <file_in> <file_out>\n", argv[0]);
		exit(1);
	}

	/* Open file */
	if ((filein = open(argv[1], O_RDONLY)) == NULL)
		err(2, "The input file %s could not be opened", argv[1]);

	fileout = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);

	copy(filein, fileout);
	close(filein);
	close(fileout);
	return 0;
}
