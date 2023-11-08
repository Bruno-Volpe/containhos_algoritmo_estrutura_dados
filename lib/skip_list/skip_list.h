#ifndef SKIPLIST_H
#define SKIPLIST_H

// Definindo a estrutura do nó
typedef struct Node
{
    char key[11];
    int value;
    struct Node **next;
} Node;

// Definindo a estrutura da lista
typedef struct SkipList
{
    int maxLevels;
    int currentLevels;
    Node *head;
} SkipList;

SkipList *initializeSkipList(int maxLevels);
Node *search(SkipList *list, int target);
int contains(SkipList *list, int target);
int generateRandomLevel(int maxLevels);
void insert(SkipList *list, int value);
void freeSkipList(SkipList *list);
void delete(SkipList *list, int target);
void printSkipList(SkipList *list);

#endif
