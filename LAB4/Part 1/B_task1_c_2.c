/* task1_c.c */
//up1100979
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHARS 10

struct charact
{
    char ch;
    int sec;
};
typedef struct charact Char;

typedef struct text_t { char** mytext; int words;} Text_t;

Text_t readText(void);
void findDist(Char*, int, char*);
void report(Char*, int);

int main(void)
{
    //char **mytext;
    int i;//, words;

    Text_t txt = readText();
    for (i = 0; i < txt.words; i++) {
        int len = strlen(txt.mytext[i]);
        Char* letters = malloc(sizeof(Char) * len);
        findDist(letters, len, txt.mytext[i]);
        report(letters, len);
        //printf("%s\n", txt.mytext[i]);

        free(letters);
    }

    return 0;
}

Text_t readText(void)
{
    Text_t txt;
    txt.mytext = NULL;
    char *word;
    int i;

    txt.words = 0;
    while (scanf("%s", word = malloc(CHARS * sizeof(char))),
           strcmp(word, "TELOS"))
    {
        txt.words++;
        txt.mytext = realloc(txt.mytext, (txt.words) * sizeof(char *));
        txt.mytext[txt.words - 1] = word;
    }
    free(word);

    return txt;
}

//Ta dedomena einai ola sto heap, ara moirazontai sti main

void findDist(Char* letters, int n, char* word)
{
    //Ola by reference opote OK
    size_t i, j;
    //memset(chars, 0, 50 * sizeof(Char));
    for (i = 0; i < n; ++i) {
        letters[i].ch = word[i];
        letters[i].sec = 0; //Default
        for (j = i + 1; j < n; ++j) {
            if (word[i] == word[j]) {
                letters[i].sec = j - i;
                break;
            }
        }
    }

    return;
}

void report(Char* letters, int n)
{
    for (int i = 0; i < n; ++i) {
        if (letters[i].ch == 0) break; //Stop at the end of the word
        printf("%c: %d\n", letters[i].ch, letters[i].sec);
    }
    printf("\n");

    return;
}
