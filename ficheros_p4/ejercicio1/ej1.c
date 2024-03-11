#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

struct options
{
	char *progname;
	int recurse;
};

struct options opt;

void usage(void)
{
	printf("%s [options] [dirname]\n\n", opt.progname);
	printf("lists the contents of dirname (default .)\n");
	printf("options:\n"
				 "\t-h:\tshow this help\n"
				 "\t-R:\trecursive\n");
}

/* apartado b */
void list_dir(char *name)
{
	DIR *d;
	struct dirent *dinfo;
	d = opendir(name);
	while ((dinfo = readdir(d)) != NULL)
	{
		fprintf(stdout, "%s\n", dinfo->d_name);
	}
	closedir(d);
}

/* apartado c */
void process_recurse(char *dirname, char *name)
{
	pid_t pid;
	char path[PATH_MAX];
}

/* apartado c */
void list_dir_recurse(char *name)
{
	DIR *d;
	struct dirent *de;
	d = opendir(name);
	struct stat *info;
	while ((de = readdir(d)) != NULL){
		pid_t pid;
		if(strcmp(de-> d_name, ".") != 0 && strcmp(de-> d_name, "..") != 0 && de->d_type == DT_DIR){
			
			pid = fork();
			if (pid == 0){
				
				execlp(opt.progname, "-R", de->d_name);
			}
			else{
				wait(NULL);
				fprintf(stdout, "%s\n", de->d_name);
			}
		}else {
			fprintf(stdout, "%s\n", de->d_name);
		}
	}
	close(d);
}

int main(int argc, char **argv)
{
	char *dirname = argv[1];
	int o;

	opt.progname = argv[0];
	opt.recurse = 0;

	int option;

	/* Apartado a: procesar opciones con getopt */
	while ((option = getopt(argc, argv, "hR")) != -1)
	{
		switch (option)
		{
		case 'h':
			usage();
			break;
		case 'R':
			opt.recurse = 1;
			break;

		default:
			break;
		}
	}

	/********************************************/

	if (opt.recurse)
		printf("%s:\n", dirname);

	// list_dir(dirname);

	if (opt.recurse)
		list_dir_recurse(dirname);

	return 0;
}
