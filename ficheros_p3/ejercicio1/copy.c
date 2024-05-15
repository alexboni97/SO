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

		/*
		EJEMPLO: "0765"
		Owner: 7 (Lectura, Escritura y Ejecución) = 7 en decimal
		Group: 6 (Lectura y Escritura) = 6 en decimal
		Others: 5 (Lectura y Ejecución) = 5 en decimal

		Descripcion de todos los permisos posibles para cada uno
		0: No permisos (0 en decimal)
		1: Ejecución (1 en decimal)
		2: Escritura (2 en decimal)
		3: Escritura y Ejecución (3 en decimal)
		4: Lectura (4 en decimal)
		5: Lectura y Ejecución (5 en decimal)
		6: Lectura y Escritura (6 en decimal)
		7: Lectura, Escritura y Ejecución (7 en decimal)
		Para 0666 en formato octal:
	

		*/
	fileout = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);//permisos cuando se cree para los usuarios
	copy(filein, fileout);
	close(filein);
	close(fileout);
	return 0;
}
