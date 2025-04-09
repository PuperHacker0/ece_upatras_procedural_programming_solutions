//up1100979
#include <stdio.h>
#define N 10

int load(double x[N]);
int print(double x[N]);
double computeprod(double[]);
void printprod(double prod);
double computeprodsum(double x[N], double * sum);
void printprodsum(double prod, double sum);

int main( ) {
    double data[N];
    double prod;
    load(data);
    print(data);
    prod = computeprod(data);
    printprod(prod);

    double sum = 0.0;
    prod = computeprodsum(data, &sum);
    printprodsum(prod, sum);

    return 0;
}

int print(double x[N]) {
    int i;
    for (i=0; i<N; i++) {
        printf(" %g ", x[i]) ;
    }

    return 0;
}

int load(double x[N]) {
    int i;
    for (i=0; i<N; i++) {
        x[i] = ((double) i+N) / N ;
    }

    return 0;
}

double computeprod(double x[N]) {
    double prod = 1.0;

    for (int i = 0; i < N; ++i)
        prod *= x[i];

    return prod;
}

void printprod(double prod) {
    printf("\nThe product is: %g\n", prod);
}

double computeprodsum(double x[N], double *sum) {
    double prod = 1.0;

    for (int i = 0; i < N; ++i) {
        *sum += x[i];
        prod *= x[i];
    }

    return prod;
}

void printprodsum(double prod, double sum) {
    printf("\ncomputeprodsum:\n");
    printf("The product is: %g\n", prod);
    printf("The sum is: %g\n", sum);
}