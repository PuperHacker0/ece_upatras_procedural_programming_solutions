//up1100979
#include <stdio.h>
#define N 10

int main( ) {
    int i;
    double data[N];
    double prod = 1.0;
    for (i=0; i<N; i++) {
        data[i] = ((double) i + N) / N ;
    }
    for (i=0; i<N; i++) {
        printf(" %g ", data[i]);
    }

    for (int i = 0; i < N; ++i) {
        prod *= data[i];
    }

    printf("\n%g\n", prod);
    return 0;
}
