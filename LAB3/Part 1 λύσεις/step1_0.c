//up1100979
#include <stdio.h>
#include <string.h>
#define W 5
int main() {
    char words[W][9 + 1];
    char test[9 + 1]; //teleftaio to '\0'
    char endword[9 + 1] = "end";
    int i = 0;

    while (i < W) {
        scanf("%s", test);
        if (!strcmp(test, endword))
            break;
        strcpy(words[i++], test);
        printf("%s\n", test);
    }

    for (i = 0; i < W; i++) {
        printf("%d %s\n", i, words[i]);
    }

    return 0;
}
