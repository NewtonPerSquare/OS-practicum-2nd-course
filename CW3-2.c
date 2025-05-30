#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exchange(char str[], int len)
{
    if (str == NULL)
    {
        return;
    }
    char *a1;
    char *a2;
    char *str1 = malloc(100);
    int i = 0;
    int count = 0;

    while (str[i] != '\0'){
        if (i > 0){
            if (str[i - 1] == ' ' && str[i] == ' '){
                for (int j = i; j <= len; j++){
                    str[j-1] = str[j];
                }
                len--;
                i--;
            }
        }
        i++;
    }

    i = 0;
    count = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ' ')
        {
            count++;
            if (count == 1)
            {
                a1 = &str[i];
            }
            a2 = &str[i];
        }
        i++;
    }
    if (count == 0)
    {
        free(str1);
        return;
    }
    char *str2 = malloc(100);
    
    memcpy(str1, str, a1 - str + 1);
    str1[a1 - str] = '\0';
    strcpy(str2, a1);
    memcpy(str, a2+1, &str[len - 1] - a2);
    strcpy(&str[(&str[len] - a2 - 1)], str2); 
    strcpy(a2 + ((&str[len - 1] - a2) - (a1 - str - 1)), str1);
    free(str1);
    free(str2);
    return;
}

int main(void)
{
    int len;
    char str[100];
    int i = 0;
    int c;
    while ((i < 100) && ((c = fgetc(stdin)) != '\n') && (c != EOF))
    {
        str[i] = c;
        i++;
    }
    len = i;
    exchange(str, len);
    if (len != 0) 
    {
    i = 0;
    while (str[i] != '\0')
    {
        fputc(str[i], stdout);
        i++;
    }
    printf("\n");
    }
    return 0;
}




