#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *substr_finder(char *str, char *search)
{
    char *ptr = NULL;
    int str_len = strlen(str);
    int search_len = strlen(search);
    if (str_len == 0 || search_len == 0)
    {
        return ptr;
    }
    int i = 0;
    while((i < str_len) && (str_len >= search_len + i))
    {
        if(str[i] == search[0])
        {
            ptr = &str[i];
            int j = 1;
            while((j<str_len) && (str[i+j] == search[j]))
            {
                j++;
            }
            if(j == search_len)
            {
                break;
            }
        }
        i++;
    }
    return ptr;
}

#define delta 4

char * input()
{
    int c;
    char *p_str = NULL;
    int i = 0;
    while (((c = fgetc(stdin)) != '\n') && (c != EOF)){
        if (i % delta == 0){
            p_str = realloc(p_str, delta + i);
        }
        if (p_str != NULL){
            p_str[i] = (char) (c % 256);
        }
        else{
            printf("memory_error");
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
            printf("memory_error");
            return NULL;
        }
    }
    else{
        if (p_str != NULL){
            p_str[i] = '\0';
        }
    }
    if (p_str == NULL){
        p_str = realloc(p_str, delta);
        p_str[0] = '\0';
    }
    return p_str;
}


int main(void)
{
    char* str1 = input();
    char* str2 = input();
    int len_str1 = strlen(str1);
    int len_str2 = strlen(str2);
    char* res = substr_finder(str1, str2);
    char* buf = malloc(len_str1);
    while(res != NULL){
        strcpy(buf, (&res[len_str2]));
        strcpy(res, buf);
        res = substr_finder(str1, str2);
    }
    free(buf);
    printf("%s\n", str1);
    free(str1);
    free(str2);
    return 0;
}