#include <stdio.h>
#include <limits.h>

#define n1 3    //matrix sizes, you can change them
#define m1 3

#define n2 2
#define m2 1


void *saturation_problem(int arr1[n1][m1], int arr2[n2][m2], int y, int x) 
{
    static int arr[n1][m1];
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            arr[i][j] = arr1[i][j];
        }
    }
    for (int i = 0; i < n2; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            if (((x + i) < n1) && ((y + j) < m1))
            {
                if ((arr[x + i][y + j] > 0) && (arr2[i][j] > 0) && (INT_MAX - arr2[i][j] < arr[x + i][y + j]))
                {
                    arr[x + i][y + j]=INT_MAX;
                } 
                else if((arr[x + i][y + j] < 0) && (arr2[i][j] < 0) && (INT_MIN - arr2[i][j] > arr[x + i][y + j]))
                {
                    arr[x + i][y + j]=INT_MIN;
                }
                else
                {
                    arr[x + i][y + j]+=arr2[i][j];
                }
            }
        }
    }
    return (int *) arr;
}

void arr_input(int *arr, int n, int m)
{
    int dd;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &dd);
            arr[i*m +  j] = dd;
        }
    }
}
void arr_output(int const *arr, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", arr[i*m + j]);
        }
        printf("\n");
    }
}

int main(void)
{
    int a1[n1][m1];
    int a2[n2][m2];
    arr_input(a1, n1, m1);
    printf("\n");
    arr_input(a2, n2, m2);
    printf("\n Input point cooridinates: \n");
    int x, y;
    scanf("%d", &x);
    scanf("%d", &y);
    int *arr = saturation_problem(a1, a2, x, y);
    arr_output(arr, n1, m1);
    return 0;
}