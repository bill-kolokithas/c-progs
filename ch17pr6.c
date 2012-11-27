// Print sorted an array of string pointers

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define WORD_MAX_LEN 10
#define SIZE_INCR 1

// Stringize the WORD_MAX_LEN constant value, for use in scanf
#define SCANF_LIMIT(x) SCANF_LIMIT2(x)
#define SCANF_LIMIT2(x) #x

// Prototypes
char *read_word();
void insert_word(char *pword, char ***words_array, int *array_size, int *num_words);
void sort_words(char **words_array, int num_words);
void print_words(char **words_array, int num_words);


int main(void) {

    char **words_array, *pword;
    int array_size = 0, num_words = 0;

    while ((pword = read_word()) != NULL)
        insert_word(pword, &words_array, &array_size, &num_words);

    sort_words(words_array, num_words);
    print_words(words_array, num_words);

    return 0;
}

// Read a word of WORD_MAX_LEN length
char *read_word() {

    int ch;
    static char word[WORD_MAX_LEN + 1];
    char *pword;

// "Eat" white-spaces before word && return NULL if line is empty
    printf("Enter word: ");
    while (isspace(ch = getchar()))
        if (ch == '\n')
            return NULL;

// Place back in buffer the first letter of the word (that we used to test for empty line)
    ungetc(ch, stdin);
    scanf("%"SCANF_LIMIT(WORD_MAX_LEN)"s", word);
    if ((pword = calloc(strlen(word) + 1, sizeof(char))) == NULL)
        exit(EXIT_FAILURE);
    strcpy(pword, word);
    
    while (getchar() != '\n'); // "Eat" trailing white-spaces

    return pword;
}

void insert_word(char *pword, char ***words_array, int *array_size, int *num_words) {

    if (*array_size == 0) {
        if ((*words_array = malloc(SIZE_INCR * sizeof(char *))) == NULL)
            exit(EXIT_FAILURE);
        *array_size += SIZE_INCR;
    } else if (*array_size == *num_words) { // Increase array when we need to add more words than our current limit
        if ((*words_array = realloc(*words_array, (*array_size + SIZE_INCR) * sizeof(char *))) == NULL)
            exit(EXIT_FAILURE);
        *array_size += SIZE_INCR;
    }
    (*words_array)[*num_words] = pword; // Copy the string pointer we created in read_word(), to array
    (*num_words)++;
}

void sort_words(char **words_array, int num_words) {

    char *temp;
    int i, new_limit;

// After every pass all elements after the last swap are sorted. 
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
    } while (num_words > 1);
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