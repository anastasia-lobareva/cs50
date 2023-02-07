// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Word count in teh file
int wordCount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashIndex = hash(word);
    node *cursor = table[hashIndex];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int letterSum = 0;
    int hashIndex;

    for (int i = 0; i < strlen(word); i++)
    {

        letterSum += toupper(word[i]);
        hashIndex = letterSum % N;
    }
    return hashIndex;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dictionaryFile = fopen(dictionary, "r");
    if (dictionaryFile == NULL)
    {
        return false;
    }

    char dictionaryWord[LENGTH + 1];

    //scan each word from the file
    while (fscanf(dictionaryFile, "%s", dictionaryWord) != EOF)
    {
        node *tempNode = malloc(sizeof(node));
        if (tempNode == NULL)
        {
            return false;
        }

        strcpy(tempNode->word, dictionaryWord);

        int hashIndex = hash(dictionaryWord);

        if (table[hashIndex] == NULL)
        {
            tempNode->next = NULL;
        }
        else
        {
            tempNode->next = table[hashIndex];
        }

        table[hashIndex] = tempNode;

        wordCount++;
    }
    fclose(dictionaryFile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != 0)
        {
            free(table[i]);
        }
    }
    return true;
}