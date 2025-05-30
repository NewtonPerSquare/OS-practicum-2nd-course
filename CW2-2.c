#include <stdio.h> 
 
 
int ones_counter(char *ar, int length, int n, int *maxlen_pointer) 
{ 
    char mask = 128; 
    char buffer; 
    int max_len = 0; 
    char bit = 0; 
    int current = 0; 
    int counter = 0; 
    for (int i = 0; i < length; i++) 
    { 
        buffer = *(ar + i); 
        for (int j = 0; j < 8; j++) 
        { 
            bit = mask & buffer; 
            if (bit == 0) 
            { 
                if (max_len < current) 
                { 
                    max_len = current; 
                } 
                if (current >= n) 
                { 
                    counter++; 
                } 
                current = 0; 
            } 
            else 
            { 
                current++; 
            } 
            buffer <<= 1; 
        } 
    } 
    if (max_len < current) 
    { 
        max_len = current; 
    } 
    if (current >= n) 
    { 
        counter++; 
    } 
    (*maxlen_pointer) = max_len; 
    return counter;  
} 
 
void base_2_out(char n) 
{ 
    for (int i = 0; i < 8; i++) 
    { 
        if (n & 128) 
        { 
            printf("1"); 
        } 
        else 
        { 
            printf("0"); 
        } 
        n <<= 1; 
    } 
    printf("\n"); 
} 
 
int main(void) 
{ 
    char arr[500]; 
    int len; 
    int n; 
    scanf("%d", &len); 
    scanf("%d", &n); 
    scanf("%s%n", arr, &len); 
    len--; //correction after scanf
    for (int i = 0; i < len; i++) 
    { 
        base_2_out(arr[i]); 
    } 
    int max_len; 
    int *address = &max_len;  
    int count_ones = ones_counter(arr, len, n, address); 
    printf("\n Amount = %d, length of longest = %d", count_ones, max_len); 
    return 0; 
}
