/* task1_b.c */
//up1100979
#include <stdio.h>
#include <string.h>
struct charact
{
    char ch;
    int sec;
};
typedef struct charact Char;
void letters(char name[50], Char chars[50]);
void report(Char chars[50]);

int main(void)
{
    char name[50];
    Char chars[50];

    scanf("%49s", name);

    letters(name, chars);
    report(chars);

    return 0;
}

void letters(char name[50], Char chars[50])
{
    //Ola by reference opote OK
    size_t i, j;
    memset(chars, 0, 50 * sizeof(Char));
    
    for (i = 0; i < 50; ++i) {
        chars[i].ch = name[i];
        chars[i].sec = 0; //Default
        for (j = i + 1; j < 50; ++j) {
            if (name[i] == name[j]) {
                chars[i].sec = j - i;
                break;
            }
        }
    }

    return;
}

void report(Char t[50])
{
    for (int i = 0; i < 50; ++i) {
        if (t[i].ch == 0) break; //Stop at the end of the word
        printf("%c: %d\n", t[i].ch, t[i].sec);
    }

    return;
}
