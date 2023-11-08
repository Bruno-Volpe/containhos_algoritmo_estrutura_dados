#ifndef SKIPLIST_H
#define SKIPLIST_H

#define MAX_LEVELS 6

// Definindo a estrutura do nó
typedef struct Node
{
    char key[11];
    char *value;
    struct Node **next;
} Node;

// Definindo a estrutura da lista
typedef struct SkipList
{
    int currentLevels; // nivel atual da lista
    int maxLevels;     // tamanho da lista em levels
    Node *head;
} SkipList;

void initializeSkipList(SkipList *list);
Node *search(SkipList *list, char *target);
int contains(SkipList *list, char *target);
int generateRandomLevel();
void insert(SkipList *list, char *key, char *value);
void freeSkipList(SkipList *list);
void delete(SkipList *list, char *target);
void printSkipList(SkipList *list);

#endif
