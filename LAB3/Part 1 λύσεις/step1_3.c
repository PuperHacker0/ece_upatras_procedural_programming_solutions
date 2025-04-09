//up1100979
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define W 5

void print_array(char a[W][10], int size);
void init_words_copy(char a[W][10], char c[W][10]);
void reverse(char c[10]);

int main() {
    char words[W][9 + 1];
    char test[9 + 1]; // teleftaio to '\0'
    char endword[9 + 1] = "end";
    int i = 0;

    while (i < W) {
        scanf(" %s", test);
        if (!strcmp(test, endword)) //Stop if we encounter "end"
            break;
        strcpy(words[i++], test);
        //printf("%s\n", test);
    }

    char words_copy[W][10];
    init_words_copy(words, words_copy);

    printf("The original array is:\n");
    print_array(words, i);
    printf("The modified array is:\n");
    print_array(words_copy, i);

    return 0;
}

void print_array(char a[W][10], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d %s\n", i, a[i]);
    }
    printf("\n");
}

void init_words_copy(char a[W][10], char c[W][10]) {
    for (int i = 0; i < W; ++i)
        strcpy(c[i], a[i]);
    
    //Fist remove all unneeded characters from all words
    int rem_ptr = 0; //Index where we will overwrite
    for (int w = 0; w < W; ++w) {
        int s = strlen(c[w]);
        for (int i = 0; i < s; ++i) { //i: index that we're checking whether to write
            if (c[w][i] == 'a' || c[w][i] == 'e' || c[w][i] == 'i' || c[w][i] == 'o' || c[w][i] == 'u' || (c[w][i] == 'y' && i)) {
                //Skip these letters                
            }
            else { //If it is not to be removed, copy it
                c[w][rem_ptr] = toupper(c[w][i]);
                ++rem_ptr;
            }
        }
        c[w][rem_ptr] = '\0';
        rem_ptr = 0;
    }

    //Then reverse the words
    for (int i = 0; i < W; ++i)
        reverse(c[i]);
}

void reverse(char c[10]) {
    int size = strlen(c);
    if (size <= 1) return;

    char tmp;
    for (int i = 0; i < size / 2; ++i) {
        tmp = c[i];
        c[i] = c[size - 1 - i];
        c[size - 1 -i] = tmp;
    }
}