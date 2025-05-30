#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#define MAXLEN 100
////
void delete_n(const char* Name, int N){
    FILE* F = fopen(Name, "r");
    if (F == NULL){
        perror("fopen");
    } 
    FILE* Ftmp = tmpfile();
    char S[MAXLEN];
    while (fgets(S, MAXLEN, F)){
        if (strlen(S) <= N + 1){
            fputs(S, Ftmp);
        }
    }
    fclose(F);
    F = fopen(Name, "w");
    fseek(Ftmp, 0, SEEK_SET);
    while (fgets(S, MAXLEN, Ftmp)){
        fputs(S, F);
    }
    fclose(F);
    fclose(Ftmp);
    return;
}

void mix1(const char* Name, int N){
    FILE* F = fopen(Name, "r");
    if (F == NULL){
        perror("fopen");
    } 
    FILE* Ftmp = tmpfile();
    char S[MAXLEN];
    int i = 0;
    while (fgets(S, MAXLEN, F)){
        i++;
    }
    if (i <= N){
        return;         
    }
    fseek(F, 0, SEEK_SET);
    i = 0;
    while (fgets(S, MAXLEN, F) && (i < N)){
        i++;
    }
    fputs(S, Ftmp);
    while (fgets(S, MAXLEN, F)){
        fputs(S, Ftmp);
    }
    fseek(F, 0, SEEK_SET);
    i = 0;
    while (fgets(S, MAXLEN, F) && (i < N)){
        fputs(S, Ftmp);
        i++;
    }
    fclose(F);
    F = fopen(Name, "w");
    fseek(Ftmp, 0, SEEK_SET);
    while (fgets(S, MAXLEN, Ftmp)){
        fputs(S, F);
    }
    fclose(F);
    fclose(Ftmp);
    return;
}
////
void mix2(const char* Name, int N){
    FILE* F = fopen(Name, "r");
    if (F == NULL){
        perror("fopen");
    } 
    FILE* Ftmp = tmpfile();
    char S[MAXLEN];
    int q = 0;
    while (fgets(S, MAXLEN, F)){
        q++;
    }
    if (q <= N){
        return;         
    }
    fseek(F, 0, SEEK_SET);
    int i = 0;
    while (fgets(S, MAXLEN, F) && (i < q - N)){
        i++;
    }
    fputs(S, Ftmp);
    while (fgets(S, MAXLEN, F)){
        fputs(S, Ftmp);
    }
    fseek(F, 0, SEEK_SET);
    i = 0;
    while (fgets(S, MAXLEN, F) && (i < q - N)){
        fputs(S, Ftmp);
        i++;
    }
    fclose(F);
    F = fopen(Name, "w");
    fseek(Ftmp, 0, SEEK_SET);
    while (fgets(S, MAXLEN, Ftmp)){
        fputs(S, F);
    }
    fclose(F);
    fclose(Ftmp);
    return;
}

int main(int argc, char** argv){
    if (argc == 1){
        return -2;
    }
    void (*fp[3])(const char*, int);
    fp[0] = &delete_n;
    fp[1] = &mix1;
    fp[2] = &mix2;
    int number, n;
    printf("Input procedure number: \n");
    while (scanf("%d", &number) != -1){
        if ((number >= -1) && (number <=3)){
            printf("Input n: \n");
            scanf("%d", &n);
            fp[number-1](argv[1], n);
        }
    }
    return 0;
}