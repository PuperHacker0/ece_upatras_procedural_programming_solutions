//up1100979
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct charact {
    char ch;
    int occurs;
    struct charact *next;
};
typedef struct charact Char;

typedef Char * ListofChar;
typedef Char * CharNode_ptr;
//Exei ena typedef onoma gia tin arxi tis listas (to head) kai ena gia ta nodes!

void letters(char name[50], ListofChar * chars_ptr);
void report(ListofChar chars);
Char * createnode(char ch);

int next_occurrence_dist(char name[50], int idx, int n);

int main(void) {
    char name[50];
    ListofChar chars = NULL;
    scanf("%49s", name);

    letters(name, &chars);
    report(chars);
    
    return 0;
}

Char * createnode(char ch) {
    CharNode_ptr newnode_ptr ;
    newnode_ptr = malloc(sizeof (Char));
    newnode_ptr -> ch = ch;
    newnode_ptr -> occurs = 0;
    newnode_ptr -> next = NULL; //Aparaitito gia na min exei garbage values
    return newnode_ptr;
}

void letters(char name[50], ListofChar * lst_ptr) {
    int n = strlen(name);
    for (int i = 0; i < n; ++i) {
        *lst_ptr = createnode(name[i]);
        (*lst_ptr)->occurs = next_occurrence_dist(name, i, n);
        lst_ptr = &((*lst_ptr)->next);
    }

    return;
}

int next_occurrence_dist(char name[50], int idx, int n) {
    for (int j = idx + 1; j < n; ++j) {
        if (name[j] == name[idx]) return j - idx;
    }

    return 0;
}

void report(ListofChar chars) {
    while (chars != NULL) {
        printf("%c: %d\n", chars->ch, chars->occurs);
        chars = chars->next;
    }
}