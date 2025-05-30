#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>	
#include <string.h>

int main(int argc, char ** argv){
    if(argc != 2){
        fprintf(stderr, "No number provided\n");
        return -1;
    }
    int n = atoi(argv[1]);
    for(int i = 0; i<n; i++){
        printf("Pid is %d\n", (int) getpid());
    }
    abort(); //exit(0); // exit(1);
}