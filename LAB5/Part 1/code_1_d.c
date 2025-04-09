//up1100979
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Dilosi tou Callback os alias gia tin int (*)(int, int)
typedef int (*CallBack)(int, int);

typedef struct gate_t {
    char* name;
    CallBack f;
} Gate;

//Dilosi sinartiseon
int myand(int a, int b);
int myor(int a, int b);

int report(Gate);

int mynand(int, int);
int mynor(int, int);
int myxor(int, int);

int main()
{
    //Define the gates and set the gate names
    int n = 5;
    Gate* gates = malloc(n * sizeof(Gate));

    for (int i = 0; i < n; ++i)
        gates[i].name = malloc(10 * sizeof(char));

    gates[0].f = myand, strcpy(gates[0].name, "myand");
    gates[1].f = myor,strcpy(gates[1].name, "myor");
    gates[2].f = myxor,strcpy(gates[2].name, "myxor");
    gates[3].f = mynand,strcpy(gates[3].name, "mynand");
    gates[4].f = mynor,strcpy(gates[4].name, "mynor");

    //Print the gate names with the corresponding table
    for (int i = 0; i < n; ++i) {
        report(gates[i]);
    }

    return 0;
}

//Ylopoiei tin pyli AND
int myand(int a, int b)
{
    return a * b;
}

//ylopoiei tin pyli OR
int myor(int a, int b)
{
    return a + b > 0;
}

int report(Gate g)
{
    //kalei tin synartisi tis opoias i diefthinsi einai
    //apothikevmeni stin f
    //analoga an einai i AND i i OR
    printf("PINAKAS ALITHEIAS TIS SINARTISIS %s:\n", g.name);
    for (int i = 0; i <= 1; ++i)
        for (int j = 0; j <= 1; ++j)
            printf("%d %d %d\n", i, j, g.f(i, j));
    printf("\n");
    return 0;
}

int mynand(int a, int b) {
    return !(myand(a, b));
}

int mynor(int a, int b) {
    return !(myor(a, b));
}

int myxor(int a, int b) {
    return a ^ b;
    //enallaktika, return myor(myand(!a, b), myand(a, !b))
}