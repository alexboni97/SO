#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

int main(int argc, char* argv[])
{
	FILE* file=NULL;
	int c,tam;
	

	if (argc<3) {
		fprintf(stderr,"Usage: %s <file_name> <text>\n",argv[0]);
		exit(1);
	}
	
	file = fopen(argv[1], "w+");
	for(int i=2;i<argc;i++){
		tam=strlen(argv[i]);
		fwrite(argv[i],sizeof(char),tam+1,file);
		//fputc('\0',file); no es necesario
	}
	fclose(file);
	/* To be completed */
	return 0;
}
