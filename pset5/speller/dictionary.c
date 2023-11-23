// Implements a dictionary's functionality
#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char *alpha[26];
    char word[LENGTH + 1];
    struct node *next;
    struct node *safe;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *cursor = malloc(sizeof(node));
    for (int i = 0, j = strlen(word); i < j; i++)
    {
        int index = isalpha(word[i]) - 'a';
        if (cursor->alpha[index] == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hash = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hash += tolower(word[i]);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    int counter = 0;
    char word[LENGTH + 1];
    // open dictionary
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("ERROR 1\n");
        return false;
    }
    // loop through every word till EOF is reached
    while (fscanf(dic, "%s", word) != EOF)
    {
        // create space to save the words inside
        node *safe = malloc(sizeof(node));
        if (safe == NULL)
        {
            printf("ERROR 2\n");
            return false;
        }
        strcpy(safe->word, word);
        safe->next = NULL;
        // find what index of the array the word should go in
        int index = hash(word);
        // if hashtable is empty at index, insert
        if (table[index] == NULL)
        {
            table[index] = safe;
        }
        else
        {
            // if hashtable is not empty at index, append
            safe->next = table[index];
            table[index] = safe;
        }
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODo
    int size = 0;
    char word[LENGTH + 1];
    for (int i = 0, n = strlen(word); i > n; i++)
    {
        size++;
    }
    return size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // don't forget to close the file
    return false;
}
