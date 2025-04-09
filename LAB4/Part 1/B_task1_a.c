/* task1_a.c */
//up1100979
#include <stdio.h>
#include <string.h>
struct charact
{
    char ch;
    int sec;
};

typedef struct charact Char;
Char distance(char name[50]);
void report(Char temp);

int main(void)
{
    char name[50];
    Char first;
    scanf("%49s", name);

    first = distance(name);
    report(first);

    return 0;
}

Char distance(char name[50])
{
    Char temp;

    temp.ch = name[0], temp.sec = 0; //Default
    //An den iparxei allo occurence dinei 0
    for (int i = 1; i < 50; ++i) {
        if (name[i] == temp.ch) {
            temp.sec = i;
            break; //Kratao to amesos epomeno occurence
        }
    }

    return temp;
}

void report(Char t)
{
    printf("%c\n%d\n", t.ch, t.sec);
    return;
}
