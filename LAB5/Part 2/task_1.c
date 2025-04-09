//up1100979

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
    int value;
    struct data * next;
} Data;
typedef Data * DataList;
typedef int (*CallBack)(DataList);

typedef struct gate_t {
    char* name;
    CallBack f;
} Gate;

Data* createData(int value);
void appendData(DataList *lstptr, Data *newptr);

int myandlst(DataList);
int myorlst(DataList);
int mynandlst(DataList);
int mynorlst(DataList);
int myxorlst(DataList);

//int report(Gate);

int main() {
    //Define the gates and set the gate names
    int n = 5;
    Gate* gates = malloc(n * sizeof(Gate));

    for (int i = 0; i < n; ++i)
        gates[i].name = malloc(10 * sizeof(char));

    gates[0].f = myandlst, strcpy(gates[0].name, "myand");
    gates[1].f = myorlst, strcpy(gates[1].name, "myor");
    gates[2].f = myxorlst, strcpy(gates[2].name, "myxor");
    gates[3].f = mynandlst, strcpy(gates[3].name, "mynand");
    gates[4].f = mynorlst, strcpy(gates[4].name, "mynor");

    //Print the gate names with the corresponding table
    /*for (int i = 0; i < n; ++i) {
        report(gates[i]);
    }*/

    //Driver code gia test
    int data[5] = { 1, 1, 1, 1, 1 };
    DataList lst = NULL;
    for (int i = 0; i < 5; ++i) {
        appendData(&lst, createData(data[i]));
    }

    for (int i = 0; i < 5; ++i) {
        printf("Gate %s yields: %d\n", gates[i].name, gates[i].f(lst));
    }

    return 0;
}

/*int report(Gate g)
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
}*/

int myandlst(Data* d) { //Recursive, ginetai profanos kai iterative
    if (d == NULL)
        return 1; //Identity tou &
    
    //else
    return d->value * myandlst(d->next);
    //ginetai kai break an einai 0 alla ok for now
}

int myorlst(Data* d) {
    if (d == NULL) return 0;
    return d->value + myorlst(d->next) > 0;
}

int mynandlst(Data* d) {
    return !(myandlst(d));
}

int mynorlst(Data* d) {
    return !(myorlst(d));
}

int myxorlst(Data* d) {
    //Gia na min mplexo me to identity tou XOR
    if (d->next == NULL) return d->value;
    else return d->value ^ myxorlst(d->next);
    //enallaktika, return myor(myand(!a, b), myand(a, !b))
}

Data * createData(int value) {
    Data * dataptr = malloc(sizeof(Data));
    dataptr->value = value;
    dataptr->next = NULL;

    return dataptr;
}

void appendData(DataList *lstptr, Data *newptr) {
    if (*lstptr==NULL) {
        *lstptr = newptr;
        return;
    }
    
    appendData(&((*lstptr)->next), newptr);
    return;
}