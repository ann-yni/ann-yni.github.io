// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// counter for number of words in dictionary
int count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//set up node for loading and unloading
node *w;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int x = hash(word);
    for (node *compare = table[x]; compare != NULL; compare = compare->next)
    {
        if (strcasecmp(word, compare->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // account for words only one letter long
    if (strlen(word) < 2)
    {
        return toupper(word[0]) - 'A';
    }
    // organize hash table by first two letters of each word
    return 26 * (toupper(word[0]) - 'A') + (toupper(word[1]) - 'A');

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open dictionary file
    FILE *file = fopen(dictionary, "r");
    // if no file or cannot read, return false
    if (file == NULL)
    {
        return false;
    }
    // read strings from file one at a time
    char term[LENGTH + 1];
    while (fscanf(file, "%s", term) != EOF)
    {
        // create a new node for each word
        w = malloc(sizeof(node));
        if (w == NULL)
        {
            return false;
        }
        strcpy(w->word, term);
        count++;
        // hash word to obtain hash value
        int x = hash(w->word);
        // insert node into hash table at that location
        w->next = table[x];
        table[x] = w;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (count > 0)
    {
        return count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    if (w == NULL)
    {
        return false;
    }
    // free node after making sure next node address is kept
    while (w != NULL)
    {
        node *temp = w->next;
        free(w);
        w = temp;
    }
    return true;
}
