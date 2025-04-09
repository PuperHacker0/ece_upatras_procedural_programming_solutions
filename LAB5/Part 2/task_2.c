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

int report(Gate, int);

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
    for (int i = 0; i < n; ++i) {
        report(gates[i], 4);
    }

    return 0;
}

int report(Gate g, int input_count) {
    printf("%s:\n", g.name);

    //Mporei na ginei kai recursive
    int bits = 0;
    for (; bits < (1 << input_count); bits++) { //2^(inputs) einai oloi oi pithanoi sindiasmoi
        DataList lst = NULL;

        for (int i = 32 - input_count + 1, bit; i <= 32; ++i) {
            //Pairnei to antistoixo bit
            appendData(&lst, createData(bit = ((bits & (1 << (32 - i))) >> (32 - i))));
            printf("%d ", bit);
        }
        printf("-> %d\n", g.f(lst));

        for (int i = 0; i < input_count; ++i) { //free ti lista
            Data* tmp = lst->next;            
            free(lst);
            lst = tmp;
        }
    }

    return 0;
}

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