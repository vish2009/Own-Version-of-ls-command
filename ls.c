#include <stdio.h>
#include <sys/types.h>	
#include <dirent.h>	
#include <stdlib.h>	
#include <sys/stat.h>
#include <unistd.h>	
#include <string.h>

int main(int argc, char * argv[])
{

	if(argc != 2){
		printf("Invalid command line arguments.Please give directory path only.\n");
		exit(1);	
	}
	
	char path[100];
        strcpy(path,argv[1]);
	struct stat mystat;

	DIR * mydir = opendir(argv[1]);
	if(mydir == NULL){
		perror("opendir failed");
		exit(1);	
	}

	struct dirent * entptr;
	printf("\n");	
	printf("%15s %30s %10s %6s\n\n","Inode Number","Name","Size","UID");	
	while(1){
		entptr = readdir(mydir);
		if(entptr == NULL){
			break;
		}
		strcat(path,entptr->d_name);
		int ret_Val = lstat(path,&mystat);
		if(ret_Val == -1){
			perror("lstat failure");
			exit(1);
		}
		printf("%15ld %30s %10ld %6d\n",mystat.st_ino,entptr->d_name,mystat.st_size,mystat.st_uid);	
		memset(&mystat,0,sizeof(mystat));
		memset(path,0,strlen(path));
		strcpy(path,argv[1]);
	}
	printf("\n");	
	return 0;
}

