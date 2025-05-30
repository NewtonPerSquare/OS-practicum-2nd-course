#include <stdio.h>
#include <limits.h>
#define size 256

void spyral(int dim1, int dim2, int arr[size][size]){
    int i = 0;
    int j = 0;
    int bound = 0;
    int k = 1;
    while (k <= dim1 * dim2){
        arr[i][j] = k;
        if (i == bound && j < dim2-bound-1){
            j++;
        }
        else if (j == dim2-bound-1 && i < dim1-bound-1){
            i++;
        }
        else if (i == dim1-bound-1 && j > bound){
            j--;
        }
        else{
            i--;
        }
        if ((i == bound + 1) && (j == bound) && (bound != dim2 - bound - 1)){
            bound++;
        }
        k++;
    }
}

int main(){
    int M, N;
    scanf("%d %d", &M, &N);
    int arr[size][size] = {0};
    spyral(M, N, arr);
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    } 
}