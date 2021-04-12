#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

#define BUF_SIZE 20

void main()
{
	int fd;
	int len;
	char buf[20] = "hellow world!";
	fd = open("test_file.txt",O_WRONLY | O_APPEND);
	if(fd < 0)
	{
		perror("open file failed");
		exit(1);
	}
	len = write(fd,buf,strlen(buf));
	if(len < 0)
	{
		printf("file write error!");
		exit(1);
	}else{
		printf("%d characters appedned!",len);
	}
}
