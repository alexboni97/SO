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
	fprintf(stdout, "%s:\n", name);
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
	fprintf(stdout, "%s:\n", name);
	while ((de = readdir(d)) != NULL){
		pid_t pid;
		if(strcmp(de-> d_name, ".") != 0 && strcmp(de-> d_name, "..") != 0 && de->d_type == DT_DIR){
			
			pid = fork();
			if (pid == 0){
				fprintf(stdout, "\n");
				char * subdir=malloc((strlen(de->d_name)+strlen(name))*sizeof(char));
				strcat(subdir,name);
				strcat(subdir,"/");
				strcat(subdir,de->d_name);
				execlp(opt.progname,opt.progname, "-R", subdir, NULL);
			}
			else{
				wait(NULL);
				fprintf(stdout, "%s\n", de->d_name);
			}
		}else {
			fprintf(stdout, "%s\n", de->d_name);
		}
	}
	closedir(d);
}

int main(int argc, char **argv)
{
	char *dirname ;

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
	if (optind >= argc)
		dirname=".";
	else
		 dirname = argv[optind];
		/********************************************/

	if (!opt.recurse)
		list_dir(dirname);
	else if (opt.recurse)
		list_dir_recurse(dirname);

	return 0;
}
