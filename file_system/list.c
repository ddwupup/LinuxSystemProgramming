/*ls -l <dir_name>
 * mode links Uid Gid Size mtime filename
 * */
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>

int main(void)
{
	DIR *dir;
	struct dirent *dirp;
	char path[1024];
	char *rootpath = ".";
	struct stat *file_stat;
	
	if((dir = opendir(rootpath)) == NULL){
		perror("opendir");
	}

	//read the dirent one by one
	while((dirp = readdir(dir)) != NULL){
		if((dirp->d_name == ".") || (dirp->d_name == ".."))
			continue;
		//print the type of the file
		switch(dirp->d_type){
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

		sprintf(path,"%s/%s",rootpath,dirp->d_name);
		if(stat(path,file_stat) == -1){
			perror("stat");
			exit(-1);
		}
		//print the mode
		printf("");
		//print the Gid
	
		//print the Uid
			

		//print the mtime
		

		//print the file_name	
	}




	closedir(dir);

	return 0;
}
