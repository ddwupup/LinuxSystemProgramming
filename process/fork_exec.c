#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(void){
    pid_t pid = fork();
    if(pid == 0){
        execl("/usr/bin/firefox","www.baidu.com",NULL);
        perror("execl");
    }else if(pid > 0){
        while(1){
            printf("parent process...");
            sleep(5);
        }
    }else {
        perror("fork");
    }
    return 0;
}