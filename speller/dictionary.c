// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int i = hash(word);

    node *cursor = table[i1];

    // Iterate through the linked list
    while (cursor != NULL)
    {
        // Compare the word with the one in the current node
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true; // Word found in dictionary
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word 1to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if (word[0] == '\0')
    {
        return 0;
    }

    char firstChar = toupper(word[0]);
    if (isalpha(firstChar))
    {
        return firstChar - 'A';
    }

    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Initialize table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Buffer for storing word
    char word[LENGTH + 1];

    // Read words from file and add to hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory for new node
        node *Node = malloc(sizeof(node));
        if (Node == NULL)
        {
            fclose(file);
            return false;
        }

        // Copy word into node
        strcpy(Node->word, word);

        // Hash word to get index
        int i = hash(word);

        // Insert node into hash table
        Node->next = table[i];
        table[i] = Node;
    }

    // Close dictionary file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int count = 0;

    // Iterate through all buckets
    for (int i = 0; i < N; i++)
    {
        // Traverse the linked list at the current index
        node *cursor = table[i];

        // Count words in the linked list
        while (cursor != NULL)
        {
            count++;
            cursor = cursor->next;
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        // Pointer to the current node in the bucket
        node *cursor = table[i];

        // Iterate through each node in the bucket
        while (cursor != NULL)
        {
            // Keep track of the next node before freeing the current node
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
