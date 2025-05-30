#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define delta 4

struct list2
{
    char* c;
    struct list2* next;
    struct list2* prev;
};
                    
char* input_word(char* fl){ //modified function from prev homework, only for words, not for the all text                  
    int c;
    char *p_str = NULL;
    int i = 0;
    while (((c = fgetc(stdin)) != '\n') && (c != EOF) && (c != ' ')){
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
        if (c != ' '){
            *fl = 1;
        }
        else{
            *fl = 0;
        }
    }
    return p_str;
}

void del(struct list2* L){
    if(L->next != NULL){
        del(L->next);
    }
    free(L->c);
    free(L);
    return;
}

void sort(struct list2* L){
    struct list2* L_p = L;
    int check = 0;     //sorted flag
    char* buf = NULL;
    if(L == NULL){
        return;
    }
    while(check == 0){      //modified bubble sort =)
        L_p = L;
        check = 1;
        while(L_p->next != NULL){
            if(strcmp(L_p->c, L_p->next->c) > 0){ //exchange or not
                buf = L_p->c; 
                L_p->c = L_p->next->c;
                L_p->next->c = buf;
                check = 0;
            }
            L_p = L_p->next;
        }
    }
    return;
}

int main(){
    struct list2* L1 = NULL; 
    struct list2* L_last = NULL;
    char fl = 0; //1 == \n || EOF, 0 == ' '
    char* buf = NULL;
    printf("Write several words:\n");
    while (fl != 1){
        buf = input_word(&fl);
        if(buf == NULL){            //fool check
            break;
        }
        if(L1 == NULL){             //first iteration
            L1 = calloc(1, sizeof(struct list2));
            L1->c = buf;
            L1->next = NULL;
            L1->prev = NULL;
            L_last = L1;
        }
        else{                       //common case
            L_last->next = calloc(1, sizeof(struct list2));
            L_last->next->prev = L_last;
            L_last = L_last->next;
            L_last->c = buf;
            L_last->next = NULL;
        }
    }
    if(L1 != NULL){
        struct list2* L2 = L1;          //for list outputs
        printf("\n");
        printf("Your list:\n");
        while(L2 -> next != NULL){   //first output
            printf("%s ", L2->c);
            L2 = L2->next;
        }
        printf("%s ", L2->c);       //prints last elem
        printf("\n\n");
        printf("Reversed list:\n");
        while(L2 != NULL){          //second output
            printf("%s ", L2->c);
            L2 = L2->prev;
        }
        printf("\n\nIn alphabetical order:\n");
        sort(L1);
        L2 = L1;
        while(L2 != NULL){ //third output
            printf("%s ", L2->c);
            L2 = L2->next;
        }
        del(L1); 
        printf("\n");
    }
    return 0;
}