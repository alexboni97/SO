#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

/** Loads a string from a file.
 *
 * file: pointer to the FILE descriptor
 *
 * The loadstr() function must allocate memory from the heap to store
 * the contents of the string read from the FILE.
 * Once the string has been properly built in memory, the function returns
 * the starting address of the string (pointer returned by malloc())
 *
 * Returns: !=NULL if success, NULL if error
 */
char *loadstr(FILE *file)
{
	char r;
	int tam=1;
	while (fread(&r,sizeof(char),1,file)==1&&r!='\0')
	{
		tam++;
	}
	fseek(file,-tam,SEEK_CUR);
	char*c=NULL;
	if(tam>1){
		c=(char*)malloc(tam*sizeof(char));
		fread(c,sizeof(char),tam,file);
		return c;	
	}else 
		return NULL;
}

int main(int argc, char *argv[])
{
	if(argc!=2){
		fprintf(stderr,"Usage: %s <fichero>\n",argv[0]);
		exit(1);
	}
	FILE *file=NULL;
	file=fopen(argv[1],"r");
	if(file==NULL){
		err(2,"fichero <%s>no existe ",argv[1]);
	}
	char *c;
	c = loadstr(file);
	if(c==NULL){
		printf("HA SUCEDIDO UN ERROR AL LEER LA PRIMERA PALABRA	\n");
	}
	while (c!=NULL)
	{
		printf("%s\n", c);
		free(c);
		c = loadstr(file);
	}

	fclose(file);
	return 0;
}
