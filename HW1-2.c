#include <stdio.h>
#include <limits.h>

void bin_out(int n){
    int mask = INT_MIN;
    int buf;
    for (int i = 0; i < 32; i++){
        if (n & mask){
            printf("1");
        }
        else{
            printf("0");
        }
        n <<= 1;
    }
    printf("\n");
}

int cycle_shift(unsigned int n, int dig, int dir){
    dig = dig % 32;
    int check;
    int correction;
    if (dir == 1){
        int mask = 1;
        for (int i = 0; i < dig; i++){
            correction = n & mask;
            n >>= 1;
            if (correction){
                n = n | INT_MIN;
            }
        }
    }
    else{
        int mask = INT_MIN;
        for (int i = 0; i < dig; i++){
            correction = ((n & mask) != 0);
            n <<= 1;
            if (correction){
                n = n | 1;
            }
        }
    }
    return n;
}

int main(){
    int n;
    printf("\nInput the number: ");
    scanf("%d", &n);
    bin_out(n);
    int digits;
    printf("\nInput the amount of positions: ");
    scanf("%d", &digits);
    int dir_flag;
    printf("Direction (1-right, 2-left): ");
    scanf("%d", &dir_flag);
    n = cycle_shift(n, digits, dir_flag);
    bin_out(n);
    return 0;
}