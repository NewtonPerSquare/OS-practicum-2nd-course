#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int ones_quantity(int n){
    int mask = 1;
    int i = 0;
    while (n != 0)
    {
        if ((n & mask) != 0)
        {
            i++;
        }
        n >>= 1;
    }
    return i;
}


void bin_out(int a){
    int mask = INT_MIN;
    for (int i = 0; i < 32; i++){
        if ((a & mask) != 0){
            printf("1");
        }
        else{
            printf("0");
        }
        a <<= 1;
    }
    printf("\n");
}

void bitsort(int arr[], int d1){
    int buf;
    int a, b;
    for (int j = 0; j < d1; j++){
        for (int i = 1; i < d1; i++){
            a = ones_quantity(arr[i]);
            b = ones_quantity(arr[i-1]);
            if (a < b){
                buf = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = buf;
            }
            if(a == b){
                if(arr[i] > arr[i - 1]){
                buf = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = buf;
                }
            }
        }
    }
    return;
}

void print(int a[], int len){
    for (int i = 0; i < len; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    for (int i = 0; i < len; i++){
        bin_out(a[i]);
    }
    printf("\n");
    return;
}



int main(){
    int length = 8;
    int array[length];
    for (int i = 0; i < length; i++){
        scanf("%d", &array[i]);
    }
    bitsort(array, length);

    print(array, length);
    return 0;
}