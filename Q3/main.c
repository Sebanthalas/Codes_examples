/*
 * Author: Sebastian Moraga Scheuermann
 * Date: July 6, 2024
 * Description: This program reads a text file containing Shakespearean literature,
 * computes the frequency of each word, and identifies the top N most frequent words.
 * It utilizes a hash table for efficient word counting and sorting algorithms to find
 * the most frequent words.
 * Inut  : n
 * Output: n most frquent words; computational time nedded to run the code.
 */
#include <stdio.h>   // Standard input-output functions.
#include <stdlib.h>  // Standard library functions, including dynamic memory management.
#include <string.h>  // String manipulation functions.
#include <ctype.h>   // Character type functions (e.g., tolower).
#include <stdint.h>  // Standard integer types.
#include <time.h>    // Include the time.h library for clock functions

#define TABLE_SIZE 10000

// Define a struct for hash table entries:
typedef struct Entry {
    char *word;
    int count;
    struct Entry *next; // Pointer to the next entry in the case of a collision (linked list).
} Entry;

// Computes a hash value for a given word using bitwise left shift and addition.
unsigned int hash(const char *word) {
    unsigned int hash = 0;
    while (*word) hash = (hash << 5) + *word++;
    return hash % TABLE_SIZE;
}

Entry *hash_table[TABLE_SIZE] = {NULL};
// Creates a new hash table entry:
Entry *create_entry(const char *word) {
    Entry *entry = malloc(sizeof(Entry)); // Allocates memory for a new Entry
    entry->word  = strdup(word);
    entry->count = 1; //Duplicates the word and sets the initial count to 1
    entry->next  = NULL;
    return entry;
}

//Inserts a word into the hash table
void insert_word(const char *word) {
    unsigned int index = hash(word); //Computes the hash index for the word
    Entry *entry = hash_table[index];
    //Checks if the word already exists in the linked list at that index
    while (entry) {
        if (strcmp(entry->word, word) == 0) {
            entry->count++;  //If found, increments the count and returns
            return;
        }
        entry = entry->next; // Move to the next entry in the linked list.
    }
    // If the word is not found, create a new entry and insert it at the beginning.
    entry = create_entry(word);
    entry->next = hash_table[index];
    hash_table[index] = entry;
}
// Reads the file and inserts words into the hash table.
void read_file(const char *path) {
    FILE *file = fopen(path, "r"); // Opens the file for reading.
    if (!file) {  // Checks if the file was successfully opened.
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char buffer[1024]; // Buffer to store each line from the file.
    while (fgets(buffer, sizeof(buffer), file)) { // Reads each line from the file.
        char *word = strtok(buffer, " \t\n\r.,;:!?()[]{}\"'"); // Tokenizes the line into words.
        // Processes each word in the line.
        while (word) {
            for (char *p = word; *p; ++p) *p = tolower(*p); // Converts the word to lowercase.
            insert_word(word); // Inserts the word into the hash table.
            word = strtok(NULL, " \t\n\r.,;:!?()[]{}\"'"); // Gets the next word in the line.
        }
    }
    fclose(file);
}

// Define a struct for storing word counts.
typedef struct {
    char *word;  // Pointer to the word string.
    int count;   // Count of occurrences of the word.
} WordCount;

// Comparison function for qsort to sort words by count in descending order.
int compare(const void *a, const void *b) {
    return ((WordCount *)b)->count - ((WordCount *)a)->count;
}

// Finds the n most frequent words in the file.
char **find_frequent_words(const char *path, int32_t n) {
    read_file(path);

    // Allocate an initial size for the words array
    int allocated_size = TABLE_SIZE;
    WordCount *words = malloc(allocated_size * sizeof(WordCount));
    int word_count = 0;

    // Iterate through the hash table and collect all words.
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry *entry = hash_table[i];
        while (entry) {
            if (word_count >= allocated_size) {
                // Resize the words array if it's too small
                allocated_size *= 2;
                words = realloc(words, allocated_size * sizeof(WordCount));
            }
            words[word_count].word = strdup(entry->word); // Copy the word.
            words[word_count].count = entry->count;       // Copy the count.
            word_count++;
            entry = entry->next;   // Move to the next entry in the linked list.
        }
    }
    // Sort the words array by count in descending order.
    qsort(words, word_count, sizeof(WordCount), compare);

    // Allocate an array to hold the top n frequent words.
    char **result = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) result[i] = strdup(words[i].word); // Copy the top n words.
    
    // Free the words array.
    for (int i = 0; i < word_count; i++) {
        free(words[i].word); // Free the copied word.
    }
    free(words);
    return result;
}

int main() {
    const char *path = "shakespeare.txt";
    int32_t n; // Number of top frequent words to find.

    // Prompt user for the number of top frequent words.
    printf("Enter the number of top frequent words to find: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    clock_t start = clock(); // Start the clock

    char **frequent_words = find_frequent_words(path, n);

    clock_t end = clock(); // End the clock
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculate the time taken

    printf("The %d most frequent words are:\n", n);
    for (int i = 0; i < n; i++) {
        printf("%s\n", frequent_words[i]);
        free(frequent_words[i]);
    }
    free(frequent_words);
    printf("Time taken to find the most frequent words: %.6f seconds\n", time_taken);
    return 0;
}
