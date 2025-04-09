//up1100979
#include <stdio.h>
#include <stdlib.h>

//Dilosi sinartiseon
int myand(int a, int b);
int myor(int a, int b);

//Dilosi tou Callback os alias gia tin int (*)(int, int)
typedef int (*CallBack)(int, int);
int report(CallBack f);

int main()
{
    CallBack f;
    //i metavliti f einai typou int(*)(int, int)
    //diladi pointer se function pou dexetai
    //dyo int arguments
    //gia times, pairnei tis dieuthinseis ton sinartiseon
    //pou exoun (int, int) arguments kai epistrfoun int

    f = myand; //i f pairnei os timi tin diefthinsi tis myand
    report(f);
    f = myor;
    report(f); //i f pairnei os timi tin diefthinsi tis myor

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
