// Print sorted an array of string pointers

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define WORD_MAX_LEN 10
#define SIZE_INCR 1
#define SCANF_LIMIT(x) SCANF_LIMIT2(x)
#define SCANF_LIMIT2(x) #x

char *read_word(int len);
void insert_word(char *pword, char ***words_array, int *array_size, int *num_words);
void sort_words(char **words_array, int num_words);
void print_words(char **words_array, int num_words);


int main(void) {

    char **words_array, *pword;
    int array_size = 0, num_words = 0;

    while ((pword = read_word(WORD_MAX_LEN)) != NULL)
        insert_word(pword, &words_array, &array_size, &num_words);

    sort_words(words_array, num_words);
    print_words(words_array, num_words);

    return 0;
}

char *read_word(int len) {

    int ch;
    char word[len + 1], *pword;

    printf("Enter word: ");
    while (isspace(ch = getchar()))
        if (ch == '\n')
            return NULL;

    ungetc(ch, stdin);
    scanf("%"SCANF_LIMIT(WORD_MAX_LEN)"s", word);
    if ((pword = calloc(strlen(word) + 1, sizeof(char))) == NULL)
        exit(EXIT_FAILURE);
    strcpy(pword, word);
    
    while (getchar() != '\n');

    return pword;
}

void insert_word(char *pword, char ***words_array, int *array_size, int *num_words) {

    if (*array_size == 0) {
        if ((*words_array = malloc(SIZE_INCR * sizeof(char *))) == NULL)
            exit(EXIT_FAILURE);
        *array_size += SIZE_INCR;
    } else if (*array_size == *num_words) {
        if ((*words_array = realloc(*words_array, (*array_size + SIZE_INCR) * sizeof(char *))) == NULL)
            exit(EXIT_FAILURE);
        *array_size += SIZE_INCR;
    }
    (*words_array)[*num_words] = pword;
    (*num_words)++;
}

void sort_words(char **words_array, int num_words) {

    char *temp;
    int i, new_limit;

    do {
        new_limit = 0;
        for (i = 0; i < num_words - 1; i++)
            if (strcmp(words_array[i], words_array[i + 1]) > 0) {
                temp = words_array[i];
                words_array[i] = words_array[i + 1];
                words_array[i + 1] = temp;
                new_limit = i + 1;
            }
        num_words = new_limit;
    } while (num_words > 0);
}

void print_words(char **words_array, int num_words) {

    int i;

    if (num_words == 0)
        return;
    
    printf("In sorted order:");
    for (i = 0; i < num_words; i++)
        printf(" %s", words_array[i]);
    puts("");
}