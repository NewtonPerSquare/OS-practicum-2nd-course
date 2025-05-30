#include <stdio.h>

int cycshift(int a[],int len,int n){
    int x;
    for (int j = 0; j<n; j++){
        x = a[len-1];
        for (int i = len; i>=0; i--){
        a[i+1] = a[i];
        }
    a[0] = x;
    }
}

int main(){
    int i, len, n;
    scanf("%d", &len);
    int a[len];
    for (i=0; i<len; i++){
        scanf("%d", &a[i]);
    }
    scanf("%d", &n);
    n = n%len;
    cycshift(a,len,n);
    for (i=0; i<len; i++){
        printf("%d ", a[i]);
    }
    return 0;
}

