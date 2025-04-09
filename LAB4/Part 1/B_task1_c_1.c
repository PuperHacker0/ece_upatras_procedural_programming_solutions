/* task1_c.c */
//up1100979
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHARS 10

typedef struct text_t { char** mytext; int words;} Text_t;

Text_t readText(void);

int main(void)
{
    //char **mytext;
    int i;//, words;

    Text_t txt = readText();

    for (i = 0; i < txt.words; i++)
        printf("%s\n", txt.mytext[i]);

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