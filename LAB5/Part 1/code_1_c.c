//up1100979
#include <stdio.h>
#include <stdlib.h>

//Dilosi sinartiseon
int myand(int a, int b);
int myor(int a, int b);

//Dilosi tou Callback os alias gia tin int (*)(int, int)
typedef int (*CallBack)(int, int);
int report(CallBack f);

int mynand(int, int);
int mynor(int, int);
int myxor(int, int);

int main()
{
    //To myfunctions einai array apo function pointers
    //Sigkekrimena, einai array apo pointers se functions pou dexontai (int, int)
    //kai epistrefoun int
    CallBack myfunctions[] = {myand, myor, myxor, mynand, mynor};
    int n = sizeof(myfunctions) / sizeof(myfunctions[0]);
    //gia na mporo na prostheso kat'eutheian to onoma tis

    for (int i = 0; i < n; ++i) {
        report(myfunctions[i]);
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

int report(CallBack f)
{
    //kalei tin synartisi tis opoias i diefthinsi einai
    //apothikevmeni stin f
    //analoga an einai i AND i i OR
    printf("PINAKAS ALITHEIAS:\n");
    for (int i = 0; i <= 1; ++i)
        for (int j = 0; j <= 1; ++j)
            printf("%d %d %d\n", i, j, f(i, j));
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