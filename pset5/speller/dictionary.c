// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <ctype.h>

#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

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

//Number of entries in the dictionary
unsigned int word_count = 0;

//Initializes the hash table used for the dictionary
void initialize_table()
{
    for (int i = 0; i < N ; i++)
    {
        table[i] = NULL;
    }
}
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //New variable to store lowercase form of word
    char lower[LENGTH +1];

    //Copy contents of word to lower
    strcpy(lower,word);

    //Convert lower to lowercase
    for (int i = 0; i < strlen(lower); i++)
    {
        lower[i]=tolower(lower[i]);
    }

    //Get the hash of word
    unsigned int hash_num = hash(lower);

    //Check if this hash has any entries in the table
    if(table[hash_num]==NULL)
    {
        return false; //If this hash is NULL, no entries
    }

    //Check the linked list at the hash entry
    for(node* temp = table[hash_num]; temp != NULL; temp=temp->next)
    {
        //If a match is found, return true immediately
        if (strcmp(lower,temp->word)==0)
        {
            return true;
        }
    }

    //If the entire linked list is searched and no match is found, return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //Return index corresponding to the first character, in lowercase
    //(a is 0, b is 1... y is 24, z is 25)
    int first = tolower(word[0]) - 'a';
    return first;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //Open file
    FILE *dict = fopen(dictionary,"r");

    //Check for successful open
    if (dict==NULL)
    {
        return false;
    }

    //Initialize the hash table
    initialize_table();

    //Initialize variable for current_word
    char current_word[LENGTH + 1];

    //Add words in the dictionary
    while (fscanf(dict,"%s",current_word) != EOF) //Stop at end of file
    {
        //Update word_count
        word_count++;

        //Hash the word
        unsigned int word_hash = hash(current_word);

        //Alocate new node
        node *n = malloc(sizeof(node));

        //Insert data into note
        strcpy(n->word,current_word);

        //Make n->next point to the current first item in the linked list (will become 2nd item)
        //The first item to be inserted (which will end up as the last item in the list)
        //will point to NULL (table is initialized pointing to NULL!)
        n->next = table[word_hash];

        //Make the hash table point to n as the first item in the list
        table[word_hash]=n;



    }
    //Close file
    fclose(dict);

    //Return
    return true;



}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //Return word_count global variable
    return word_count;
}

//Unloads nodes at the i-th element of the hash table
void unload_nodes(node *n)
{
    //Base case: nothing to free if n points to NULL
    if (n == NULL)
    {
        return;
    }

    //Free elements pointed to by n
    unload_nodes(n->next);

    //Free n
    free(n);

}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //Go through hash table
    for (int i=0 ; i < N ; i++)
    {
        //Check for entry actually used
        if (table[i]!=NULL)
        {
            unload_nodes(table[i]);
        }

    }
    return true;
    // return false;
}
