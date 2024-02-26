#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

const int TAM = 512;
void copy(int fdo, int fdd){
	char arr[512];
	int s;
	s = read(fdo, arr, TAM);
	while (s == TAM)	{
		write(fdd, arr, TAM);
		s = read(fdo, arr, TAM);
	}
	write(fdd, arr, s);
}

void copy_regular(char *orig, char *dest){
	int fdo, fdd;
	fdo = open(orig, O_RDONLY);
	if (fdo == -1){
		fprintf(stderr, "no se pudo abrir fileIn");
		exit(1);
	}
	fdd = open(dest, O_RDWR | O_CREAT | O_TRUNC, 0666);
	copy(fdo, fdd);
}

void copy_link(char *orig, char *dest){
	struct stat info;
	lstat(orig, &info);
	size_t t=info.st_size+1;
	char *l=malloc(t);
	readlink(orig,l,info.st_size);
	l[t-1]='\0';
	symlink(l,dest);
	free(l);
}

int main(int argc, char *argv[]){
	if (argc != 3){
		fprintf(stderr, "Usage: ./%s <fileIn> <fileOut>\n", argv[0]);
		exit(1);
	}
	struct stat info;
	if (lstat(argv[1], &info) == -1){
		perror("stat");
		exit(1);
	}
	if (S_ISLNK(info.st_mode)){
		copy_link(argv[1], argv[2]);
	}
	else if (S_ISREG(info.st_mode))	{
		copy_regular(argv[1], argv[2]);
	}
	else{
		perror("es otro tipo");
		exit(1);
	}

	return 0;
}
