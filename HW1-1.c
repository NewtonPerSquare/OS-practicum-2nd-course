#include <stdio.h>
#include <limits.h>

int main(){
    double eps;
    scanf("%lf", &eps);
    double x;
    while (scanf("%lf", &x) != EOF){
        printf("%g", x);
        double x_prev = 1;
        double x_next = (x_prev + x/x_prev) / 2;
        while  ((x_prev - x_next) * (x_prev - x_next) >= eps*eps){
            x_prev = x_next;
            x_next = (x_prev + x/x_prev) / 2;
        }
        printf("\n%f", x_next);
        printf("\n%g", x_next);
        printf("\n%e", x_next);
        printf("\n%.10g\n", x_next);
    }
}