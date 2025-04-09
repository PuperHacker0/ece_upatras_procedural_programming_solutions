//up1100979

/*SIMEIOSI!
Organosa etsi to programma mou, pou piga apo to vima 1 sto vima 3 kat'eutheian.
Diladi, proevlepsa oles tis voithitikes sinartiseis (printFullline, printMidline, printCenterline)
    ex arxis, kai den xreiastike na na grapso kodika pou epanalamvanetai gia to version 2.
Ean yparxei provlima me auto, parakalo epikoinoniste mazi mou gia na to diorthoso!
Euxaristo, Giorgos.
*/


#include <stdio.h>

void getShape(int *);
void getSize(int *);
void getCharacter(char *);

void printFullline(int, char);
void printMidline(int, char);
void printCenterline(int, char);

void printShape1(int, char);
void printShape2(int, char);
void printShape3(int, char);
void printShape4(int, char);

int main(void) {
    int shape, size;
    char ch;

    while (1) { //Call the respective function based on the user's choice
        getShape(&shape);

        if (shape < 1 || shape > 4) {
            printf("Program finished!\n");
            return 0;
        }
        
        getSize(&size);
        getCharacter(&ch);

        switch (shape) {
            case 1:
                printShape1(size, ch);
                break;
            case 2:
                printShape2(size, ch);
                break;
            case 3:
                printShape3(size, ch);
                break;
            case 4:
                printShape4(size, ch);
                break;
            default: //Any other shape choice (e.g. -1) terminates the program
                printf("Program finished!\n");
                return 0;
        }

        printf("\n");
    }

    return 0;
}

//Read the input from the user

void getShape(int *choice) { 
    printf("Which shape would you like? [1-4]: ");
    scanf("%d", choice);
}

void getSize(int *size) {
    printf("What should be the size of your shape? ");
    scanf("%d", size);
}

void getCharacter(char *ch) {
    printf("Finally, what should be the main character used for your shape? ");
    scanf(" %c", ch);
}

//Generic functions used for all shapes

void printFullline(int n, char ch) { //Prints a continuous line of n characters ch
    for (int i = 0; i < n; ++i) {
        printf("%c", ch);
    }
}

void printMidline(int n, char ch) { //Prints a line ch------ch of total length n
    if (n == 1) {
        printf("%c", ch);
        return;
    }

    printf("%c", ch);

    for (int i = 0; i < n - 2; ++i)
        printf("-");

    printf("%c", ch);
}

void printCenterline(int n, char ch) { //Prints a line ch--ch--ch of total length n
    printf("%c", ch);

    int innerLength = n - 2;
    for (int i = 1; i <= innerLength; ++i) {
        if (innerLength % 2 && i == innerLength / 2 + 1) {
            printf("%c", ch);
        }
        else if (innerLength % 2 == 0 && (i == innerLength / 2 || i == innerLength / 2 + 1)) {
            printf("%c", ch);
        }
        else printf("-");
    }

    printf("%c", ch);
}

//Functions specific to each shape

void printShape1(int n, char ch) {
    if (n == 1) { //Special case
        printf("%c\n", ch);
        return;
    }

    printFullline(n, ch);
    printf("\n");

    int midlines = (n - 3) / 2;
    for (int i = 0; i < midlines; ++i) { //Upper part of the shape
        printMidline(n, ch);
        printf("\n");
    }

    if (n > 2) { //Special case n = 2
        printCenterline(n, ch);
        printf("\n");

        //If even, there is an extra centerline
        if (n % 2 == 0) {
            printCenterline(n, ch);
            printf("\n");
        }
    }

    for (int i = 0; i < midlines; ++i) { //Bottom part of the shape
        printMidline(n, ch);
        printf("\n");
    }

    printFullline(n, ch);
    printf("\n");
}

void printShape2(int n, char ch) {
    if (n == 1) { //Special case
        printf("%c\n", ch);
        return;
    }
    
    int offsetOfEven = n % 2 ? 0 : 1; //To create the correct shape for even n

    int dash = n / 2 - offsetOfEven, odd = 1;
    for (; dash > 0; --dash) { //Print the upper part of the shape
        printFullline(dash, '-');
        printMidline(odd + offsetOfEven, ch);
        odd += 2;

        printf("\n");
    }

    printCenterline(n, ch);
    printf("\n");
    if (offsetOfEven) {
        printCenterline(n, ch);
        printf("\n");
    }

    for (dash = 1, odd -= 2; dash <= n / 2 - offsetOfEven; ++dash) { //Print the bottom part of the shape
        printFullline(dash, '-');
        printMidline(odd + offsetOfEven, ch);
        odd -= 2;

        printf("\n");
    }
}

void printShape3(int n, char ch) {
    printf("%c\n", ch);
    if (n == 1) //Special case
        return;

    for (int i = 2; i <= n - 1; ++i) {
        printMidline(i, ch);
        printf("\n");
    }

    printFullline(n, ch);
    printf("\n");
}

void printShape4(int n, char ch) {
    if (n == 1) { //Special case
        printf("%c\n", ch);
        return;
    }
    
    for (int i = 1, odd = 1; i < n; ++i) {
        printFullline(n - i, ' ');
        printMidline(odd, ch);
        odd += 2;

        printf("\n");
    }

    printFullline(2 * n - 1, ch);
    printf("\n");
}