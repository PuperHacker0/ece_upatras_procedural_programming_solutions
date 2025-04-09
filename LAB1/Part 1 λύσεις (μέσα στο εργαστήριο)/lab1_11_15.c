//up1100979
#include <stdio.h>

void printfivechars(void);
void printnchars(int n, char ch);
void squarefive(void);
void squaren(int n);

int main(void) {
    //1.1
    printfivechars();

    //1.2
    printnchars(8, '=');
    printnchars(22, '!');

    //1.3
    int cnt;
    printf("How many chars to print? ");
    scanf("%d", &cnt);
    
    printnchars(cnt, 'x'); //Random character

    //1.4
    squarefive();

    //1.5
    squaren(3);

    return 0;
}

void printfivechars(void) {
    for (int i = 0; i < 5; ++i)
        printf("=");
    printf("\n");
}

void printnchars(int n, char ch) {
    for (int i = 0; i < n; ++i)
        printf("%c", ch);
    printf("\n");
}

void squarefive(void) {
    for (int i = 0; i < 5; ++i)
        printfivechars();
}

void squaren(int n) {
    for (int j = 0; j < n; ++j)
        printnchars(n, '!');
}