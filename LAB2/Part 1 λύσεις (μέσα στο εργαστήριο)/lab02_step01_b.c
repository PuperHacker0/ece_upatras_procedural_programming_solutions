//up1100979
#include <stdio.h>
#define N 10
#define M 5

int load(double x[N][M]);
int print(double x[N][M]);
double computeprod(double[N][M]);
void printprod(double prod);

int main()
{
    double data[N][M];
    double prod = 1.0;

    load(data);
    print(data);
    prod = computeprod(data);
    printprod(prod);

    return 0;
}

int print(double x[N][M])
{
    int i;
    for (i = 0; i < N; i++)
    {
        for (int j = 0; j < M; ++j)
            printf(" %g\t ", x[i][j]);

            printf("\n");
    }

    return 0;
}

int load(double x[N][M])
{
    int i;
    for (i = 0; i < N; i++)
    {
        for (int j = 0; j < M; ++j)
            x[i][j] = ((double)i+j+N) / N;
    }

    return 0;
}

double computeprod(double x[N][M]) {
    double prod = 1.0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            prod *= x[i][j];
        }
    }

    return prod;
}

void printprod(double prod) {
    printf("The product is: %g\n", prod);
}