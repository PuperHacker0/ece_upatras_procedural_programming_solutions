//up1100979

#include <stdio.h>
#include <stdlib.h>
#define TOPG 12

typedef int (*CallBack)(int, int);
typedef struct gate {
    CallBack f;
    struct gate * in1;
    struct gate * in2;
    int result;
    //By default to result tha einai -1
    //To xreiazomaste gia na min ypologizoume polles fores piles pou sindeontai se epomenes piles
    //Eidika an einai getinput piles, auto einai provlima giati tha zitaei polles fores tis times
    //Ex'allou, to problem statement leei na tropopoiisoume ton kodika, opote auto edo epitrepetai
} Gate;

int myand(int a, int b);
int myor(int a, int b);
int mynand(int, int);
int mynor(int, int);
int myxor(int, int);

int getinput();
Gate * creategate(CallBack f);
int eval(Gate *x);

int main() {
    //Gate * a_ptr, * b_ptr, * c_ptr;
    Gate* g[TOPG];
    //Kanonika den xreiazontai tosoi pointers, mono 1 gia to root
    //kai enas gia na tou kanoume assign to creategate
    //dld ptr = creategate(), in1 = ptr, kai sinexizei etsi
    //Gia na min xreiastei omos na kano free anadromika (complex), to grafo etsi, einai ok

    //NOR
    g[0] = creategate(mynor);
    g[1] = creategate(getinput);
    g[2] = creategate(getinput);
    g[0]->in1 = g[1];
    g[0]->in2 = g[2];

    //AND
    g[3] = creategate(myand);
    g[4] = creategate(getinput); //Redundant alla ok gia tora
    g[5] = creategate(getinput);
    g[3]->in1 = g[4];
    g[3]->in2 = g[5];

    //OR
    g[6] = creategate(myor);
    g[7] = creategate(getinput);
    g[8] = creategate(getinput);
    g[6]->in1 = g[7];
    g[6]->in2 = g[8];

    //NAND
    g[9] = creategate(mynand);
    g[9]->in1 = g[0];
    g[9]->in2 = g[3];

    //XOR
    g[10] = creategate(myxor);
    g[10]->in1 = g[3];
    g[10]->in2 = g[6];

    //OR
    g[11] = creategate(myor);
    g[11]->in1 = g[9];
    g[11]->in2 = g[10];

    printf("%d", eval(g[11]));

    for (int i = 0; i < TOPG; ++i)
        free(g[i]);

    return 0;
}

int myand(int a, int b) {
    return a * b;
}

int myor(int a, int b) {
    return a + b > 0;
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

int getinput() {
    int x;
    scanf("%d", &x);

    return x;
}

Gate * creategate(CallBack f) {
    Gate * temp ;
    temp = malloc(sizeof(Gate));
    temp->f = f;
    temp->in1 = NULL;
    temp->in2 = NULL;
    temp->result = -1;

    return temp;
}

int eval(Gate *x) {
    int a, b;
    if (x->result != -1) return x->result;
    
    if (x->in1 != NULL)
        a = eval(x->in1);
    if (x->in2 != NULL)
        b = eval(x->in2);

    if (x->in1==NULL && x->in2 == NULL)
        return x->result = (x->f)(0,0); //Getinput
    return x->result = (x->f)(a, b);
}