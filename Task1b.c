#include <stdio.h>
#include <limits.h>

int main(){
    int imax = INT_MAX;
    int a = 0;
    char c;
    c = getchar();
    while ((c != '/n' && c != EOF)) {
        if (c >= '0' && c <= '9'){
            if (a > (imax-c)/10){
                printf("%d", a);
                printf("%c",' ');
                a = c -'0';
            }
            else{
                a *= 10;
                a -= '0';
                a += c;
            }
        }
        c = getchar();
    }
    if (a != 0){
        printf("%c",' ');
        printf("%d",a);
    }
}