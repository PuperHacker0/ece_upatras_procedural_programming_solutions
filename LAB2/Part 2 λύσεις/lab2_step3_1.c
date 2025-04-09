//up1100979

#include <stdio.h>
#include <string.h>
#define N 10
#define M 20

void initialize_matrix(double matrix[N][M], double, double, double, double, double);
void print_matrix(double matrix[N][M], int time);
void next_temps(double matrix[N][M]);

int main() {
    double matrix[N][M];
    initialize_matrix(matrix, 2.0, 5.0, 2.0, 4.0, 0.0);
    print_matrix(matrix, 0);

    int time_interval = 1; //seconds
    for (int i = 1; i <= time_interval; ++i) { //Step of 1 second each time
        next_temps(matrix);
        print_matrix(matrix, i);
    }

    scanf("%d", &matrix[1][1]);
    return 0;
}

void initialize_matrix(double matrix[N][M], double left, double right, double up, double down, double center) {
    //Initialize top and bottom rows
    for (int i = 1; i < M - 1; ++i) {
        matrix[0][i] = up;
        matrix[N - 1][i] = down;
    }

    //Initialize left and right columns
    for (int i = 1; i < N - 1; ++i) {
        matrix[i][0] = left;
        matrix[i][M - 1] = right;
    }

    //Initialize corner cells
    matrix[0][0] = (left + up) / 2;
    matrix[0][M - 1] = (right + up) / 2;
    matrix[N - 1][0] = (left + down) / 2;
    matrix[N - 1][M - 1] = (right + down) / 2;

    //Initialize all cells not on the boundary of the matrix (inner cells)
    for (int r = 1; r < N - 1; ++r)
        for (int c = 1; c < M - 1; ++c)
            matrix[r][c] = center;
}

void print_matrix(double matrix[N][M], int time) {
    printf("The matrix at t=%d is:\n", time);

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < M; ++c)
            printf("%.2f\t", matrix[r][c]);
        printf("\n");
    }
}

void next_temps(double matrix[N][M]) {
    /*Epivalletai na antigrapsoume ton palio pinaka se enan allo
    prin ton allaksoume, giati an den to kanoume, i metavoli tis timis
    se ena keli tha epirazei ti metavoli tis timis sta geitonika tou
    kelia, to opoio den to theloume, theloume ta kelia na allazoun
    thermokrasia mono me vasi tis proigoumenes times*/

    double prev_matrix[N][M];
    memcpy(prev_matrix, matrix, sizeof (double) * (N * M));
    //Copy N*M doubles, each one of which takes up 8 bytes

    double newTemp;
    for (int r = 1; r < N - 1; ++r)
        for (int c = 1; c < M - 1; ++c) {
            //Apply the formula
            newTemp = prev_matrix[r][c];
            for (int i = r - 1; i <= r + 1; ++i)
                for (int j = c - 1; j <= c + 1; ++j)
                    newTemp += prev_matrix[i][j];
            matrix[r][c] = newTemp * 0.1;
        }
}