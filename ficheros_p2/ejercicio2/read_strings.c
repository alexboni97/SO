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
	int r,tam;
	fread(&r,sizeof(char),1,file);
	tam=1;
	while (r!='\0')
	{
		fread(&r,sizeof(char),1,file);
		tam++;
		
	}
	fseek(file,-tam,SEEK_CUR);
	char*c=NULL;

	c=(char*)malloc(tam*sizeof(char));
	if(c==NULL){
		return NULL;
	}else
	fread(c,sizeof(char),tam,file);
	//c[tam-1]='\0';
	r=-1;
	return c;	
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
	while (!feof(file))
	{
		c = loadstr(file);
		printf("%s\n", c);
		free(c);
	}

	fclose(file);
	return 0;
}
