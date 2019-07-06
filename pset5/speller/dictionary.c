// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
//#define N 26 for default hash function
#define N 60000

//Initialize word count
    int word_count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];


//--------------------------------------------------------HASH FUNCTIONS--------------------------------------------
// Hashes word to a number between 0 and 25, inclusive, based on its first letter
/*
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}
*/
unsigned int hash(const char* word)
 {
     unsigned long hash = 5381;

     for (const char* ptr = word; *ptr != '\0'; ptr++)
     {
         hash = ((hash << 5) + hash) + tolower(*ptr);
     }

     return hash % 60000;
}
//--------------------------------------------------------END OF HASH FUNCTIONS--------------------------------------------

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{


    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table (Part of TODO)
    while (fscanf(file, "%s", word) != EOF)
    {

        node*new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }

        strcpy(new_node -> word, word);

        new_node -> next = hashtable[hash(word)];
        hashtable[hash(word)] = new_node;
        //add to the word count
        word_count += 1;

    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    bool is_true = false;
    node *cursor = hashtable[hash(word)];
    while (cursor != NULL)
    {
        //Dosomething
        if (strcasecmp(word, cursor -> word) == 0 )
        {
            is_true = true;
        }
        cursor = cursor -> next;
    }
    return is_true;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = hashtable[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor -> next;
            free(temp);
        }
    }
    return true;
    //ACTUALY return TRUE
}

