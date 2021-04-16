/*duojincheng kaobei wenjian
*/
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

#define BUFSIZE 1024

void do_copy(int sfd,int dfd)
{
    //an shunxu du,an shunxu xie,keyi gaijin cheng wuxu duxie
    char buf[BUFSIZE];
    struct flock fl;
    off_t len = BUFSIZE;
    off_t rlen;
    int errno;

    lockf(sfd,F_LOCK,len);//jiasuo,huchi xiugai pos 
    while((rlen = read(sfd,buf,len)) > 0){
        off_t pos = lseek(sfd,0,SEEK_CUR);//huoqu dangqian duqu zhizhen weizhi
        lockf(sfd,F_ULOCK,len);

        fl.l_type = F_WRLCK;
        fl.l_whence = SEEK_SET;
        fl.l_start = pos;
        fl.l_len = rlen;

        fcntl(dfd,F_SETLK,fl);
        write(dfd,buf,rlen);
        fcntl(dfd,F_SETLKW,fl);

        lockf(sfd,F_LOCK,len);
    }
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

    int n = 4;//zhiding gei 4 ge jincheng
    while(n > 0){
        pid = fork();
        if(pid == 0){
            do_copy(sfd,dfd);
            return 0;
        }else if(pid < 0){
            perror("fork");
            exit(1);
        }
        n--;
    }
    while(wait(NULL) > 0);
    close(sfd);
    close(dfd);
    return 0;
}