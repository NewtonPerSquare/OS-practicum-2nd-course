#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#define RED_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[1;32m"
#define BLUE_TEXT "\033[1;34m"
#define RESET_COLOR "\033[0m"

int pids1, pids2, pidp;
int f;
int counter = 0;
char wbyte = 0;

void sigwr1(int s){
    counter --;
    wbyte += (1 << counter);
    if (counter == 0){
        printf("%c", wbyte);
        wbyte = 0;
        counter = 8;
    }

    kill(pidp, SIGALRM);
}

void sigwr0(int s){
    counter --;
    if (counter == 0){
        printf("%c", wbyte);
        wbyte = 0;
        counter = 8;
    }

    kill(pidp, SIGALRM);
}

void sigread(int s){
    static char rbyte;
    if (counter == 0){
        if (read(f, &rbyte, sizeof(char))){
            counter = 8;
        }
        else{
            kill(pids2, SIGIO);
        }
    }
    counter--;
    char mask = 1 << counter;
    if (rbyte & mask){
        kill(pids2, SIGUSR2);
    }
    else{
        kill(pids2, SIGUSR1);
    }
}

void sigend(int s){
    close(f);
    printf("\n");
    kill(pidp, SIGIO);
}
void falarm(int s){
    kill(pids1, SIGALRM);
}
void fkiller(int s){
    kill(pids1, SIGKILL);
    kill(pids2, SIGKILL);
    exit(0);
}


int main(int argc, char ** argv){
    f = open(argv[argc-1], O_RDONLY);
    int pid1, pid2;
    if((pid2 = fork()) > 0){ // F
        pids2 = pid2;
        pidp = getpid();
        if ((pid1 = fork()) > 0){
            // F
            pids1 = pid1;        
        }
        else if (pid1 == 0){  //s1
            pidp = getppid();
            pids1 = getpid();
            signal(SIGALRM, &sigread);
            sleep(1);
            kill(pidp, SIGALRM);
            for(;;);
        }

        signal(SIGALRM, &falarm);
        signal(SIGIO, &fkiller);
        for(;;);
    }
    else if(pids2 != 0){
        abort();
    }
    else{    //s2
        pids2 = getpid();
        pidp = getppid();
        counter = 8;
        signal(SIGUSR1, &sigwr0);
        signal(SIGUSR2, &sigwr1);
        signal(SIGIO, &sigend);
        for(;;);
    }
    int status;
    waitpid(pids1, &status, WUNTRACED);
    exit(0);
    return 0;
}
