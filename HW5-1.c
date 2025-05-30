#include <stdio.h>

#define BINPRINT(a){\
    for(int i = 0; i < sizeof(typeof(a))*8; i++) {\
        /*check, if digit to check is 0 or 1*/\
        if (((((typeof(a)) 1) << (sizeof(typeof(a))*8 - i - 1)) & a) > 0)\  
            putc('1', stdout);\
        else\
            putc('0', stdout);\
    }\
    printf("\n");\
} 


int main(){
    //////
    char c = -3;
    if(c)
        BINPRINT(c)
    else
        printf("Zero!\n");
    BINPRINT((short)7);
    long x = 15;
    if(x)
        BINPRINT(x)
    else
        printf("Zero!\n");
    BINPRINT((long long)x);
    //////
    return 0;
}