#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define delta 4
//////
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
/////////
 
void print(struct list2* L){
    printf("Your list: \n");
    while (L != NULL){
        printf("%s ", L->c);
        L = L->next;
    }
    printf("\n\n");
}

struct list2* insert(struct list2* L, char* x, int p){
    if (L == NULL){
        return L;
    }
    struct list2* elem = calloc(1, sizeof(struct list2));
    elem->c = x;
    if(p <= 1){             //for first elem
        elem->next = L;
        elem->prev = NULL;
        L->prev = elem;
        L = elem;
        return L;
    }
    else{
        struct list2* buf = L;              //moving until end of list or place is achieved
        if(buf->next != NULL){
            while(buf->next->next != NULL){
                if(p == 2){
                    break;
                }
                p--;
                buf = buf->next;
            }
            if (p == 2){                    //if place is achieved
                elem->prev = buf;
                elem->next = buf->next;
                buf->next->prev = elem;
                buf->next = elem;
            }
            else{                           //if end is achieved
                buf = buf->next;
                elem->next = NULL;
                elem->prev = buf;
                buf->next = elem;
            }
        }
        else{                               //also for end
            elem->prev = buf;
            elem->next = buf->next;
            buf->next = elem;
        }
    }
    return L;
}


struct list2* erase(struct list2* L, int p){
    if (L == NULL){
        return L;
    }
    if(p == 1){                     //for 1st element
        struct list2* elem = L;
        L = L->next;
        elem->next = NULL;
        del(elem);
    }
    else{
        struct list2* buf1 = L;
        struct list2* buf2 = NULL;
        if(buf1->next != NULL){
            while(buf1->next->next != NULL){        //moving until end or place is achieved
                if(p == 2){
                    break;
                }
                buf1 = buf1->next;
                p--;
            }
            buf2 = buf1->next;                      //deleting
            if (buf1->next->next != NULL){
                buf1->next->next->prev = buf1;
            }
            buf1->next = buf1->next->next;
            buf2->next = NULL;
            del(buf2);
        }
        else{                                       //also for end
            L = L->next;
            buf1->next = NULL;
            del(buf1);
        }
    }
    return L;
}

int main(){
    //////
    struct list2* L1 = NULL; 
    struct list2* L_last = NULL;
    char fl = 0; //1 == \n || EOF, 0 == ' '
    char var;
    char* buf = NULL;
    char p;
    printf("Write a list:\n");
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
    //////
    if(L1 != NULL){
        while (1){
            printf("What do you want to do? \nTo insert-1, to erase-2, to show list-3, to exit-0: ");
            scanf("%c", &var);
            scanf("%c");
            if (var == '0')
                break;
            else if (var == '1'){
                printf("\nInput p: ");
                scanf("%c", &p);
                scanf("%c");
                printf("\nPrint a word to insert: ");
                buf = input_word(&fl);
                L1 = insert(L1, buf, p-'0');
            }
            else if (var == '2'){
                printf("\nInput p: ");
                scanf("%c", &p);
                scanf("%c");
                L1 = erase(L1, p-'0');
            }
            else if (var == '3'){
                print(L1);
            }
            else
                printf("\nSorry, incorrect input, try again. ");
        }
    }
    return 0;
}