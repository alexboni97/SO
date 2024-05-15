#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
/* Forward declaration */
int get_size_dir(char *fname, size_t *blocks);

/* Gets in the blocks buffer the size of file fname using lstat. If fname is a
 * directory get_size_dir is called to add the size of its contents.
 */
int get_size(char *fname, size_t *blocks)
{
	//auto t=*blocks;
	struct stat info;
	if(lstat(fname,&info)==0){
		switch (info.st_mode &S_IFMT)//S_IFMT mascara para que solo compruebe los bits correspondientes al modo
		{
		case S_IFDIR:
			int t;
			get_size_dir(fname,blocks);
			break;
		case S_IFREG:
			*blocks+=info.st_blocks;
			break;
		default:
			break;
		}
	}
	return 0;
}


/* Gets the total number of blocks occupied by all the files in a directory. If
 * a contained file is a directory a recursive call to get_size_dir is
 * performed. Entries . and .. are conveniently ignored.
 */
int get_size_dir(char *dname, size_t *blocks)
{
	//int t=*blocks;
	DIR *d;
	struct dirent *dinfo;
	d=opendir(dname);
	while((dinfo=readdir(d))!=NULL){
		//if(dinfo->d_name!="." && dinfo->d_name!=".."){//preguntar porque no funciona de esta manera
		if(strcmp(dinfo->d_name, ".") == 0 || strcmp(dinfo->d_name, "..") == 0){
			continue;
		}
			get_size(dinfo->d_name,blocks);
	}
	closedir(d);
	return 0;
}

/* Processes all the files in the command line calling get_size on them to
 * obtain the number of 512 B blocks they occupy and prints the total size in
 * kilobytes on the standard output
 */
//int main()
int main(int argc, char *argv[])
{
	// int argc=5;
	// char *argv1="check_mostrar";

	if (argc < 2)
	{
		fprintf(stderr, "Usage %s <file1> <file2> <...>\n", argv[0]);
		exit(1);
	}
	size_t *blocks=malloc(sizeof(int));
	for (int i = 1; i<argc; i++){
		*blocks=0;
		get_size(argv[i],blocks);
		*blocks/=2;
		fprintf(stdout,"%ld		%s\n",*blocks,argv[i]);
	}
	free(blocks);
	return 0;
}
