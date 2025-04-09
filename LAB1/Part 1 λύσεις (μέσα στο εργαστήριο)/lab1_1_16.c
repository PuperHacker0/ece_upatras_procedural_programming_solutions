//up1100979
#include <stdio.h>

//1.6

void printTopBottomLine(int n);
void printMidline(int n);
void printCenterline(int n);
void printSQ(int n);

int main(void) {
    int n;
    printf("Side length of square: ");
    scanf("%d", &n);

    printSQ(n);

    return 0;
}

void printTopBottomLine(int n) {
    for (int i = 0; i < n; ++i) {
        printf("q");
    }

    printf("\n");
}

void printMidline(int n) {
    printf("a");

    for (int i = 0; i < n - 2; ++i)
        printf("-");

    printf("a\n");
}

void printCenterline(int n) {
    printf("a");

    int innerLength = n - 2;
    for (int i = 1; i <= innerLength; ++i) {
        if (innerLength % 2 && i == innerLength / 2 + 1) {
            printf("*");
        }
        else if (innerLength % 2 == 0 && (i == innerLength / 2 || i == innerLength / 2 + 1)) {
            printf("*");
        }
        else printf("-");
    }

    printf("a\n");
}

void printSQ(int n) {
    if (n == 1) { //Special case
        printf("q\n");
        return;
    }

    printTopBottomLine(n);

    int midlines = (n - 3) / 2;
    for (int i = 0; i < midlines; ++i)
        printMidline(n);

    if (n > 2) { //Special case
        printCenterline(n);
        //If even, there is an extra centerline
        if (n % 2 == 0) printCenterline(n);
    }

    for (int i = 0; i < midlines; ++i)
        printMidline(n);

    printTopBottomLine(n);
}