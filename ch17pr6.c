// Print sorted an array of string pointers

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define WORD_MAX_LEN 10
#define SIZE_INCR 1

void read_word(char word[], int len);
void insert_word(const char word[], char ***words_array, int *array_size, int num_words, int word_len);
void sort_words(char **words_array, int num_words);
void print_words(char **words_array, int num_words);


int main(void) {

    char **words_array, temp_word[WORD_MAX_LEN + 1];
    int array_size, num_words, word_len;
    array_size = num_words = 0;

    do {
        read_word(temp_word, WORD_MAX_LEN);
        word_len = strlen(temp_word);
        if (word_len > 0) {
            insert_word(temp_word, &words_array, &array_size, num_words, word_len);
            num_words++;
        }
    } while (word_len > 0);
    
    sort_words(words_array, num_words);
    print_words(words_array, num_words);

    return 0;
}

void read_word(char word[], int len) {

    int ch, i = 0;

    printf("Enter word: ");
    while (isspace(ch = getchar()))
        if (ch == '\n')
            break;

    while (ch != '\n' && ch != EOF) {
        if (isalpha(ch) && i < len) {
            word[i++] = ch;
            ch = getchar();
        } else
            break;
    }
    word[i] = '\0';
    while (ch != '\n')
        ch = getchar();
}

void insert_word(const char word[], char ***words_array, int *array_size, int num_words, int word_len) {

    char **allocate_test;

    if (*array_size == 0) {
        *words_array = malloc(SIZE_INCR * sizeof(char *));
        if (*words_array == NULL)
            exit(EXIT_FAILURE);
        *array_size += SIZE_INCR;
    } else if (*array_size == num_words) {
        allocate_test = realloc(*words_array, (*array_size + SIZE_INCR) * sizeof(char *));
        if (allocate_test == NULL)
            exit(EXIT_FAILURE);
        *words_array = allocate_test;
        *array_size += SIZE_INCR;
    }
    (*words_array)[num_words] = calloc(word_len + 1, sizeof(char));
    if ((*words_array)[num_words] == NULL)
        exit(EXIT_FAILURE);
    strcpy((*words_array)[num_words], word);
}

void sort_words(char **words_array, int num_words) {

    char *temp;
    int i, j;

    for (i = 0; i < num_words - 1; i++)
        for (j = i + 1; j < num_words; j++)
            if (strcmp(words_array[i], words_array[j]) > 0) {
                temp = words_array[i];
                words_array[i] = words_array[j];
                words_array[j] = temp;
            }
}

void print_words(char **words_array, int num_words) {

    int i;

    printf("In sorted order:");
    for (i = 0; i < num_words; i++)
        printf(" %s", words_array[i]);
    puts("");
}