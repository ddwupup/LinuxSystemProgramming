#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

#define BUF_SIZE 20

int main(int argc,char* argv[])
{
	int fd;
	int len;
	char buf[20] = "hellow world!";
	if(argc < 2)
	{
		printf("usage:app <file_name>\n");
		exit(1);
	}
	umask(0);
	fd = open(argv[1],O_RDWR | O_CREAT,0666);
	if(fd < 0)
	{
		perror("create file failed");
		exit(1);
	}
	len = write(fd,buf,strlen(buf));
	if(len < 0)
	{
		printf("file write error!");
		exit(1);
	}else{
		printf("%d characters writed!",len);
	}
	return 0;
}
