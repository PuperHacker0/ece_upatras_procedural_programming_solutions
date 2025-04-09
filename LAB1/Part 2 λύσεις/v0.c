//up1100979
#include <stdio.h>

void getShape(int *);
void getSize(int *);
void getCharacter(char *);

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
    printf("Which shape would you like? [1-4]:\n");
    *choice = 1;
    //Gia na do an doulevei sosta, theto *choice = -1 gia na do an tha kanei terminate to programma
}

void getSize(int *size) {
    printf("What should be the size of your shape?\n");
    *size = 5;
}

void getCharacter(char *ch) {
    printf("Finally, what should be the main character used for your shape?\n");
    *ch = ';';
}

//Functions to print each shape

void printShape1(int n, char ch) {
    printf("shape1\n");
}

void printShape2(int n, char ch) {
    printf("shape2\n");
}

void printShape3(int n, char ch) {
    printf("shape3\n");
}

void printShape4(int n, char ch) {
    printf("shape4\n");
}