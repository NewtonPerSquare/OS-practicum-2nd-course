#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>	
#define RED_TEXT "\033[1;31m"
#define RESET_COLOR "\033[0m"


void reason_end(int status)
{
    if(WIFEXITED(status)){
        printf("Process terminated successfully.\n");
    }
    else{
        printf("Stop signal: %d\n", WTERMSIG(status));
    }
    return;
}


int main(int argc, char *argv[]){
    pid_t s_pid1;
    pid_t s_pid2;
    int exfl;
    int err;
    if(argc < 6){
        fprintf(stderr, RED_TEXT"Not enough info\n"RESET_COLOR);
        return -1;
    }
    if(argv[5][0] == 'p'){       //parallel
        if((s_pid1 = fork()) > 0){ //dad
            if((s_pid2 = fork()) > 0){ //dad
                pid_t pidb;
                pidb = wait(&err);      //wait untill someone ends
                if (pidb == s_pid1){
                    printf("Process 1 ended up with code %d. ", err);
                }
                else{
                    printf("Process 2 ended up with code %d. ", err);
                }
                reason_end(err);
                pidb = wait(&err);
                if (pidb == s_pid1){
                    printf("Process 1 ended up with code %d. ", err);
                }
                else{
                    printf("Process 2 ended up with code %d. ", err);
                }
                reason_end(err);
            }
            else if(s_pid2 == 0){ // son2
                exfl = execl(argv[3], argv[3], argv[4], NULL);
                if(exfl == -1){
                    printf("process fail2\n");
                    abort();
                }
            }
            else{
                exit(-1); 
            }
        }
        else if(s_pid1 == 0){ // son1
            exfl = execl(argv[1], argv[1], argv[2], NULL);
            if(exfl == -1){
                printf("process fail1\n");
                abort();
            }
        }
        else{
            exit(-1);
        }
    }




    else{       //One by one
        if((s_pid1 = fork()) == 0){ // son
            exfl = execl(argv[1], argv[1], argv[2], NULL);
            if(exfl == -1){
                printf("process fail1\n");
                abort();
            }
        }
        else if (s_pid1 > 0){//dad
            wait(&err);
            printf("Process 1 ended up with code %d. ", err);
            reason_end(err);
            if ((s_pid2 = fork()) == 0){ // son 2
                exfl = execl(argv[3], argv[3], argv[4], NULL);
                if(exfl == -1){
                    printf("process fail2\n");
                    abort();
                }
            }
            else if (s_pid2 > 0){
                wait(&err);
                printf("Process 2 ended up with code %d. ", err);
                reason_end(err);
            }
            else{
                exit(-1);
            }         
        }
        else{
            exit(-1);
        }
    }
    return 0;
}