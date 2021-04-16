#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

#define BUFSIZE 1024

bool do_copy(int sfd,int dfd,off_t pos,off_t len)
{
    //an shunxu du,an shunxu xie,keyi gaijin cheng wuxu duxie
    char buf[BUFSIZE];
    // 
    // lseek(sfd,len,SEEK_CUR);
    // write(fd,buf,rlen);
    lockf(sfd,F_LOCK,len);
    int rlen = read(fd,buf,len);
    lseek(sfd,rlen,SEEK_CUR);//cuole!!
    lockf(sfd,F_ULOCK,len);

    lockf(dfd,F_LOCK,rlen);
    write(dfd,buf,rlen);

    if(rlen == len)
        return true;
    else 
        return false;
}

int main(int argc ,char *argv[])
{
    int sfd;
    int dfd;
    pid_t pid;

    if(argc < 3){
        printf("usage:app <source file> <dest file>");
        exit(1);
    }

    sfd = open(argv[1],O_RDONLY);
    if(sfd < 0){
        perror("open source file");
        exit(1);
    }

    umask(0);
    //creat a file size specified as the source file
    dfd = open(argv[2],O_CREAT | O_RDWR,0777);
    if(dfd < 0){
        perror("creat dest file");
        exit(1);
    }

    int n = 4;
    while(n > 0){
        pid = fork();
        if(pid == 0){
            while(do_copy() > 0);
            return 0;
        }else if(pid < 0){
            perror("fork");
            exit(1);
        }
        n--;
    }
    while(wait(NULL) > 0);
    return 0;
}