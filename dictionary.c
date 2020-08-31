// Implements a dictionary's functionality

#include <string.h>
#include <strings.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node //we create a struct called node
{
    char word[LENGTH + 1]; //in this structure is a word with space for length +1
    struct node *next; //and a pointer to the next node
}
node;  //assigned name

int counter = 0; //integer for word counter starts at 0

// Number of buckets in hash table
const unsigned int N = 26; //26 buckets for 26 letters

// Hash table
node *table[N]; //node which we point to table of buckets

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int key = hash(word); //we need to add a key

    node* nodePtr = table[key]; //next node (pointer) we will call the arrow between nodePtr and equal its value to the key

    while(nodePtr != NULL) //so while the arrow isnt equal to NULL.. line43..
    {
        if(strcasecmp(nodePtr -> word, word) == 0) //however! (use strcascmp to compare two strings) if word is a word, called word.. has a value..
        {
            return true; //return true
        }
        nodePtr = nodePtr -> next; //declare nodeptr to equal next
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) //Source: cp algorithms with my own change
{
        unsigned int value = 0; //we need an int to count each letter
        for (int i = 0, n = strlen(word); i < n; i++) //for counting characters, make use of strlen to cound each character
        {
             value += isalpha(word[i]); //use isalpha to detect character case of letters[i]..
        }
        return value % N; //N = hashtable
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE* filePtr = fopen(dictionary, "r"); //create file and pointer to open dictionary to read.
    if(filePtr == NULL) //if arrow reaches null..
    {
        return false;
    }

    for(int i = 0; i < N; i++) //i less than table number
    {
        table[i] = NULL; //index of table null
    }

    char tmpWrd[LENGTH +1]; //create a temp word so we can hold onto and continue to link

    while(fscanf(filePtr, "%s\n", tmpWrd) != EOF) //scan along the arrow. while temp word is not the end of file..
    {
        node* tmpNode = malloc(sizeof(node)); //allocate a temp node malloced to the size of previous node..

        strcpy(tmpNode -> word, tmpWrd); //copy into tmpnode, the tmpwrd copied from word..

        int key = hash(tmpWrd); //add a key number. hash that into tmpwrd..

        if(table[key] == NULL) //check to see if table is null
        {
            tmpNode -> next = NULL; //follow arrow to next to see if that is null
            table[key] = tmpNode;
        }

        else
        {
            tmpNode -> next = table[key]; //follow arrow.. if it equals the key
            table[key] = tmpNode; //store node in key
        }

        counter++; //use word counter to continue counting as we add new words
    }

    fclose(filePtr); //close ptr
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter; //keep couting
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++) //go along number of words
    {
        node* nodePtr = table[i]; //node pointer and table

        while(nodePtr != NULL) //while has a value
        {
            node* todelete = nodePtr; //store value of node pointer into a delete box.
            nodePtr = nodePtr -> next; //continue along
            free(todelete); //free up everything stored in box
        }
        table[i] = NULL; //if table value is now NULL
    }
    return true; //delete worked.
}
