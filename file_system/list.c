/*
*ls -l <dir_path>
 * mode links Uid Gid Size mtime filename
 * */
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<string.h>

void printf_type(unsigned char type)
{
	switch(type){
		case DT_BLK:
			printf("b");
			break;
		case DT_CHR:
            printf("c");
			break;
		case DT_DIR:
            printf("d");
            break;
		case DT_FIFO:
            printf("f");
            break;
		case DT_LNK:
            printf("l");
            break;
        case DT_REG:
            printf("-");
            break;
        case DT_SOCK:
            printf("s");
            break;
        default:
			printf(" ");
            break;
		}
}
void print_mode(unsigned int mode)
{
	switch(mode){
		case 0:
			printf("---");
			break;
		case 1: 
			printf("--x");
			break;
		case 2:
            printf("-w-");
            break;
        case 3:
            printf("-wx");
            break;
		case 4:
            printf("r--");
            break;
        case 5:
            printf("r-x");
            break;
		case 6:
            printf("rw-");
            break;
        case 7:
            printf("rwx");
            break;
	}
}

void list_file(char *rootpath)
{
	DIR *dir;
	struct dirent *dirp;
	char path[1024];
	struct stat file_stat;
	struct passwd *pwd;
	struct group *gr;
	struct tm lt;//local time
	char mtime[80];
	const char *c_path = ".";//current path
	const char *f_path = "..";

	if((dir = opendir(rootpath)) == NULL){
		perror("opendir");
		exit(-1);
	}

	//read the dirent one by one
	while((dirp = readdir(dir)) != NULL){
		//ignore . and ..
		if((strncmp(dirp->d_name,c_path,sizeof(c_path)) == 0) || (strncmp(dirp->d_name,f_path,sizeof(f_path)) == 0))
			continue;
		//print the type of the file
		printf_type(dirp->d_type);

		sprintf(path,"%s/%s",rootpath,dirp->d_name);

		if(stat(path,&file_stat) == -1){
			perror("stat");
			exit(-1);
		}
		//print the mode
		print_mode(file_stat.st_mode & 0700/(8*8));
		print_mode(file_stat.st_mode & 0070/8);
		print_mode(file_stat.st_mode & 0007);

		//print links,Gid,Uid , can find the user name by file passwd 
		pwd = getpwuid(file_stat.st_uid);
		gr = getgrgid(file_stat.st_gid);
		printf(" %3lu %s %s ",file_stat.st_nlink,pwd->pw_name,gr->gr_name);

		//print size
		printf("%8ld ",file_stat.st_size);
		//print the mtime
		localtime_r(&(file_stat.st_mtime),&lt);
		strftime(mtime,sizeof(mtime),"%c",&lt);
		printf("%s ",mtime);

		//print the file_name
		printf("%s \n",dirp->d_name);	
	}
	closedir(dir);
}

int main(int argc,char *argv[])
{
	if(argc < 2){
		list_file(".");
	}else{
		for(int i = 1;i < argc;i++){
			printf("%s :\n",argv[i]);
			list_file(argv[i]);
		}
	}
	return 0;
}
