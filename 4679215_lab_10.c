// Gabriel Saborido Lab 10 CS1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRIE_SIZE 26

typedef struct trie
{
    // array of children nodes
    struct trie *childNode[TRIE_SIZE];
    // keep count of occurences
    int count;
} trie;

// makes a node
trie *createNode()
{
    trie *node = malloc(sizeof(trie));
    node->count = 0;
    // initialize to null
    for (int i = 0; i < TRIE_SIZE; i++)
    {
        node->childNode[i] = NULL;
    }
    return node;
}

// maps a-z to 0-25
int map(char s)
{
    return s - 'a';
}

void insert(trie **ppTrie, char *word)
{

    // get size of word
    int sizeOfWord = strlen(word);

    // create a node the go down the tree
    trie *node = *ppTrie;

    // loop through the word
    for (int i = 0; i < sizeOfWord; i++)
    {
        int index = map(word[i]);
        // if current node doesn't exist make one
        if (node == NULL)
        {
            node = createNode();
        }

        // if the child node doesn't exist, make one
        if (node->childNode[index] == NULL)
        {
            node->childNode[index] = createNode();
        }

        // push down the tree
        node = node->childNode[index];
    }

    // we reached the end so track count
    node->count++;
}

int numberOfOccurances(trie *pTrie, char *word)
{
    int sizeofWord = strlen(word);
    trie *node = pTrie;
    for (int i = 0; i < sizeofWord; i++)
    {
        int index = map(word[i]);
        if (node->childNode[index] == NULL)
        {
            return 0;
        }
        // push node down the child
        node = node->childNode[index];
    }
    return node->count;
}

trie *deallocateTrie(trie *pTrie)
{
    if (pTrie == NULL)
    {
        return NULL;
    }

    // recursively frees all existing nodes
    for (int i = 0; i < TRIE_SIZE; i++)
    {
        if (pTrie->childNode[i] != NULL)
        {
            deallocateTrie(pTrie->childNode[i]);
        }
    }
    // free the current node
    free(pTrie);
    return NULL;
}

int main(void)
{
    // read the number of the words in the dictionary
    //  parse line  by line, and insert each word to the trie data structure
    trie *head = createNode();

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    for (int i = 0; i < 5; i++)
        insert(&head, pWords[i]);

    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(head, pWords[i]));
    }

    head = deallocateTrie(head);

    if (head != NULL)
        printf("There is an error in this program\n");
    return 0;
}