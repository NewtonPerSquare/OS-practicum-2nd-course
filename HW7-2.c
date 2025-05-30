#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define RED_TEXT "\033[1;31m"
#define MAGENTA_TEXT "\033[1;35m"
#define RESET_COLOR "\033[0m"

#define delta 4

struct List
{
    char* str;
    int count;
    struct List* next;
};

                    
char* ReadFileStr(char* fl, FILE* F){ //modified function from prev homeworks, fl == 1 <=> EOF                
    int c;
    char *p_str = NULL;
    int i = 0;
    while (((c = fgetc(F)) != '\n') && (c != EOF) && (c != ' ')){
        if (i % delta == 0){
            p_str = realloc(p_str, delta + i);
        }
        if (p_str != NULL){
            p_str[i] = (char) (c % 256);
        }
        else{
            printf("memory error");
            break;
        }
        i++;
    }
    if (i % delta == 0 && p_str != NULL){
        p_str = realloc(p_str, delta + i);
        if (p_str != NULL){
            p_str[i] = '\0';
        }
        else{
            printf("memory error");
            return NULL;
        }
    }
    else{
        if (p_str != NULL){
            p_str[i] = '\0';
        }
        else{
            p_str = malloc(1);
            *p_str = '\0';
        }
    }
    if (fl != NULL){     //the word is read, changing the flag
        if (c == EOF){
            *fl = 1;
        }
        else{
            *fl = 0;
        }
    }
    return p_str;
}


struct List* append(struct List* L, char* new, int shift){       //add or correct the counter (in list)
    char newlenOk = (strlen(new) > shift);
    if(L == NULL) 
    {
        L = calloc(1, sizeof(struct List));
        L->next = NULL;
        L->count = 1;
        L->str = new;
        return L;
    }
    struct List* L1 = L;
    struct List* L2 = L; 
    while(L1 != NULL)
    {
        L2 = L1;
        if(newlenOk && (strlen(L1->str) > shift)) 
        {
            if((strcmp(&L1->str[shift], &new[shift]) == 0)) 
            {
                free(new); 
                L1->count++;
                return L;
            }
        }
        L1 = L1->next;
    }
    L1 = L2;
    L1->next = calloc(1, sizeof(struct List)); //new elem
    L1 = L1->next;
    L1->next = NULL;
    L1->count = 1;
    L1->str = new;
    return L;
}

void deleteL(struct List* L){
    if (L != NULL){
        deleteL(L->next);
        free(L->str);
        free(L);
    }
    return;
}

int main(int argc, char ** argv)
{
    char c_fl = 0;    //to show the amount
    char d_fl = 0;    //don't show unique strings
    char u_fl = 0;    //to show only unique
    int s_cnt = 0;    //to ignore first _ symbols during comparison
    if (argc == 1){
        fprintf(stderr, RED_TEXT "No_file_mentioned\n" RESET_COLOR);
        return -1;
    }
    if (argc > 2){
        for(int i = 2; i<argc; i++){
            if (strcmp(argv[i], "-s") == 0){
                s_cnt = atoi(argv[i+1]);
                i++;  
            }
            else if ((argv[i])[0] == '-'){
                if((argv[i])[1] == 'c'){
                    c_fl = 1;
                }
                else if ((argv[i])[1] == 'd')
                {
                    d_fl = 1;
                }
                else if ((argv[i])[1] == 'u')
                {
                    u_fl = 1;
                }
            }
        }
    }                //got all info from command line
    if ((d_fl + u_fl) == 2){ //d and u flags are contradiction
        printf(MAGENTA_TEXT "-d + -u = no strings\n" RESET_COLOR);
        return 0;
    }
    FILE * F = fopen(argv[1], "r");
    if (F == NULL){
        fprintf(stderr, RED_TEXT "Fopen_error\n" RESET_COLOR);
        return -2;
    }
    char fl = 0;
    char* str = NULL;
    struct List* LL = NULL;
    for (;;){   
        str = ReadFileStr(&fl, F); 
        if(fl == 1)
        {
            LL = append(LL, str, s_cnt);    //final element
            break;
        }
        LL = append(LL, str, s_cnt); //add to list (or correct list)
    }
    struct List* L1 = LL;
    
    while(L1 != NULL){
        if (((d_fl + u_fl) == 0) || (d_fl && (L1->count != 1)) || (u_fl && (L1->count == 1))){   //conditions, when you output
            if (c_fl){
                printf("#%d# ", L1->count);
            }
            printf("%s\n", L1->str);
        }
        L1 = L1->next;
    }
    deleteL(LL); //clear memory ^-^ (thank you, valgrind)
    fclose(F);
    return 0;
}