//up1100979

#include <stdio.h>
#include <stdlib.h>

struct gate;

/*Xreiazomaste auto to struct oste i linked list tou kathe komvou
na einai linked list apo pointers se gates, ara xreiazomaste ena struct
pou na exei next pointer kai gate pointer*/
typedef struct linked_list_node {
    struct gate* gate;
    struct linked_list_node* next;
} Node;
typedef Node* NodeList;
typedef int(*CallBack)(NodeList);

typedef struct gate {
    CallBack f;
    Node* inputs;
    int result;
} Gate;
typedef Gate * GateList;


void appendData(Node** lstptr, Node *newptr);

int myandlst(NodeList);
int myorlst(NodeList);
int mynandlst(NodeList);
int mynorlst(NodeList);
int myxorlst(NodeList);

int getinput();
Gate * createGate(CallBack f);
Node * createNode(Gate *gate);
int eval(Gate *x);

int main() {
    Gate *NOR, *AND, *OR1st, *OR2nd, *NAND, *XOR, *ORTOP;

    //NOR
    NOR = createGate(mynorlst);
    appendData(&(NOR->inputs), createNode(createGate(getinput)));
    appendData(&(NOR->inputs), createNode(createGate(getinput)));

    //AND
    AND = createGate(myandlst);
    appendData(&(AND->inputs), createNode(createGate(getinput)));
    appendData(&(AND->inputs), createNode(createGate(getinput)));

    //OR
    OR1st = createGate(myorlst);
    appendData(&(OR1st->inputs), createNode(createGate(getinput)));
    appendData(&(OR1st->inputs), createNode(createGate(getinput)));

    //OR
    OR2nd = createGate(myorlst);
    appendData(&(OR2nd->inputs), createNode(createGate(getinput)));
    appendData(&(OR2nd->inputs), createNode(createGate(getinput)));
    
    //NAND
    NAND = createGate(mynandlst);
    appendData(&(NAND->inputs), createNode(NOR));
    appendData(&(NAND->inputs), createNode(AND));
    appendData(&(NAND->inputs), createNode(OR1st));

    //XOR
    XOR = createGate(myxorlst);
    appendData(&(XOR->inputs), createNode(NOR));
    appendData(&(XOR->inputs), createNode(AND));
    appendData(&(XOR->inputs), createNode(OR2nd));

    //Final OR
    ORTOP = createGate(myorlst);
    appendData(&(ORTOP->inputs), createNode(NAND));
    appendData(&(ORTOP->inputs), createNode(XOR));

    printf("%d", eval(ORTOP));

    //Kanonika prepei na ginei free recursively alla einai pera apo to zitoumeno autis tis askisis

    return 0;
}

int myandlst(Node* d) { //Recursive, ginetai profanos kai iterative
    if (d == NULL)
        return 1; //Identity tou &
    
    //else
    return d->gate->result * myandlst(d->next);
    //ginetai kai break an einai 0 alla ok for now
}

int myorlst(Node* d) {
    if (d == NULL) return 0;
    return d->gate->result + myorlst(d->next) > 0;
}

int mynandlst(Node* d) {
    return !(myandlst(d));
}

int mynorlst(Node* d) {
    return !(myorlst(d));
}

int myxorlst(Node* d) {
    //Gia na min mplexo me to identity tou XOR
    if (d->next == NULL) return d->gate->result;
    else return d->gate->result ^ myxorlst(d->next);
    //enallaktika, return myor(myand(!a, b), myand(a, !b))
}

int getinput() {
    int x;
    scanf("%d", &x);

    return x;
}

Gate * createGate(CallBack f) {
    Gate * temp;
    temp = malloc(sizeof(Gate));
    temp->f = f;
    temp->inputs = NULL;
    temp->result = -1;

    return temp;
}

Node * createNode(Gate *g) {
    Node * temp;
    temp = malloc(sizeof(Node));
    temp->next = NULL;
    temp->gate = g;

    return temp;
}

int eval(Gate *x) {
    if (x->result != -1) return x->result;
    
    if (x->inputs == NULL) { //Getinput
        return x->result = (x->f)(NULL); //Getinput
    }

    //Else this gate has not been computed yet
    //So check all its inputs and make sure they have been computed
    Node* lst = x->inputs; //Head of list
    while (lst != NULL) {
        eval(lst->gate);
        lst = lst->next;
    }

    return x->result = (x->f)(x->inputs);
}

void appendData(Node** lstptr, Node* newptr) {
    if (*lstptr == NULL) { //The linked list has not been initialized yet
        *lstptr = newptr; //Put the pointer to the root to the actual root
        return;
    }
    
    //We do have a head, find the tail
    Node* node = *lstptr;
    while (node->next != NULL) { //Tail, append here
        node = node->next;
    }
    node->next = newptr;
}