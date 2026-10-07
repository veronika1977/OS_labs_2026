#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
int main(){
    pid_t p1=fork();
    if(p1==0){
        clock_t t=clock();
        for(volatile int i=0;i<90000000;i++);
        printf("Process ID: %d, Parent ID: %d, Time: %.2f ms\n",getpid(),getppid(),(double)(clock()-t)*1000/CLOCKS_PER_SEC);
        exit(0);
    }else{
        pid_t p2=fork();
        if(p2==0){
            clock_t t=clock();
            for(volatile int i=0;i<90000000;i++);
            printf("Process ID: %d, Parent ID: %d, Time: %.2f ms\n",getpid(),getppid(),(double)(clock()-t)*1000/CLOCKS_PER_SEC);
            exit(0);
        }
        clock_t t=clock();
        for(volatile int i=0;i<90000000;i++);
        printf("Process ID: %d, Parent ID: %d, Time: %.2f ms\n",getpid(),getppid(),(double)(clock()-t)*1000/CLOCKS_PER_SEC);
        wait(NULL);
        wait(NULL);
    }
    return 0;
}

