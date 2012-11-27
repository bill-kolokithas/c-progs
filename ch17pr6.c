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

// Declarations
typedef struct {
    char **words_array;
    int array_size;
    int num_words;
} Container;

// Prototypes
char *read_word(char *word_pointer);
void insert_word(char *word_pointer, Container *words);
void sort_words(Container *words);
void print_words(Container words);


int main(void) {

    Container words = {.array_size = 0, .num_words = 0};
    char *word_pointer;

    while ((word_pointer = read_word(word_pointer)) != NULL)
        insert_word(word_pointer, &words);

    sort_words(&words);
    print_words(words);

    return 0;
}

// Read a word of WORD_MAX_LEN length and return a pointer to a dynamically allocated string
char *read_word(char *word_pointer) {

    int ch;
    static char word[WORD_MAX_LEN + 1];

// "Eat" white-spaces before word && return NULL if line is empty
    printf("Enter word: ");
    while (isspace(ch = getchar()))
        if (ch == '\n')
            return NULL;

// Place back in buffer the first letter of the word (that we used to test for empty line)
    ungetc(ch, stdin);
    scanf("%"SCANF_LIMIT(WORD_MAX_LEN)"s", word);
    if ((word_pointer = calloc(strlen(word) + 1, sizeof(char))) == NULL)
        exit(EXIT_FAILURE);
    strcpy(word_pointer, word);

    while (getchar() != '\n'); // "Eat" trailing white-spaces

    return word_pointer;
}

// Insert the word from read_word() to array
void insert_word(char *word_pointer, Container *words) {

    if (words->array_size == 0) {
        if ((words->words_array = malloc(SIZE_INCR * sizeof(char *))) == NULL)
            exit(EXIT_FAILURE);
        words->array_size += SIZE_INCR;
    } else if (words->array_size == words->num_words) { // Increase array when we need to add more words than our current limit
        if ((words->words_array = realloc(words->words_array, (words->array_size + SIZE_INCR) * sizeof(char *))) == NULL)
            exit(EXIT_FAILURE);
        words->array_size += SIZE_INCR;
    }
    words->words_array[words->num_words] = word_pointer; // Copy the string pointer we created in read_word(), to array
    words->num_words++;
}

// Modified bubble-sort
void sort_words(Container *words) {

    char *temp;
    int i, new_limit, num_words = words->num_words;

// After every pass all elements after the last swap are sorted. 
    do {
        new_limit = 0;
        for (i = 0; i < num_words - 1; i++)
            if (strcmp(words->words_array[i], words->words_array[i + 1]) > 0) {
                temp = words->words_array[i];
                words->words_array[i] = words->words_array[i + 1];
                words->words_array[i + 1] = temp;
                new_limit = i + 1;
            }
        num_words = new_limit;
    } while (num_words > 1);
}

void print_words(Container words) {

    int i;

    if (words.num_words == 0)
        return;

    printf("In sorted order:");
    for (i = 0; i < words.num_words; i++)
        printf(" %s", words.words_array[i]);
    puts("");
}