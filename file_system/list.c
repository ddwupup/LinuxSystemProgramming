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

int main(int argc,char *argv[])
{
	char *path;
	DIR *dir;
	struct dirent *item;

	if(argc < 2){
		*path = "./";
	}else{
		*path = argv[1];
	}

	dir = opendir(path);
	if(dir == NULL){
		perror("opendir");
		exit(-1);
	}

	//read the dirent one by one
	while((item = readdir(dir) != NULL)){
		//print the type of the file
		switch(item->d_type){
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

		//print the mode
		
		//print the Gid
	
		//print the Uid
			

		//print the mtime
		

		//print the file_name	
	}






	return 0;
}
