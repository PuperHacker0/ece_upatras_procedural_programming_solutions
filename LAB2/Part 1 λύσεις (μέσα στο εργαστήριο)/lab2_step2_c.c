//up1100979
#include <stdio.h>
#define N 10
#define M 5

int load(double x[N][M]);
int print(double *x, int r, int c);
//Me pointer gia na min xriasti na grapso dio sinartisis
//pou kanoun to idio apla gia diaforetikou megethous pinakes

double computeprod(double x[N][M]);
void printprod(double prod);
void transpose(double[N][M], double[M][N]);

int main( ) {
    double data[N][M];
    double prod;
    load(data);
    prod = computeprod(data);
    printprod(prod);

    printf("The original matrix is:\n");
    print(data[0], N, M);

    printf("\n\nThe transpose matrix is:\n");
    double dataT[M][N];
    transpose(data, dataT);
    print(dataT[0], M, N);

    return 0;
}

int print(double *x, int r, int c) {
    int i;
    for (i=0; i<r; i++) {
        for (int j = 0; j < c; ++j)
            printf(" %g\t", *(x + i*c + j));
        printf("\n");
    }

    return 0;
}

int load(double x[N][M]) {
    int i;
    for (i=0; i<N; i++) {
        for (int j = 0; j < M; ++j)
            x[i][j] = ((double) i+j+N) / N ;
    }

    return 0;
}

double computeprod(double x[N][M]) {
    double prod = 1.0;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            prod *= x[i][j];

    return prod;
}

void printprod(double prod) {
    printf("\nThe product is: %g\n", prod);
}

void transpose(double data[N][M], double dataT[M][N]) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            dataT[j][i] = data[i][j];
}