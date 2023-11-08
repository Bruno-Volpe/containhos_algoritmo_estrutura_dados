#include <stdio.h>
#include <stdlib.h>
#include "skiplist.h"

// Função para inicializar a skip-list
SkipList *initializeSkipList(int maxLevels)
{
    SkipList *list = (SkipList *)malloc(sizeof(SkipList));
    list->maxLevels = MAX_LEVEL;
    list->currentLevels = 1;

    // Alocando o nó cabeça
    list->head = (Node *)malloc(sizeof(Node));
    list->head->value = -1;
    list->head->next = (Node **)malloc(maxLevels * sizeof(Node *));

    // Inicializando os ponteiros next com NULL
    for (int i = 0; i < maxLevels; i++)
    {
        list->head->next[i] = NULL;
    }

    return list;
}

// Função para procurar um elemento na skip-list
Node *search(SkipList *list, int target)
{
    Node *current = list->head;

    for (int i = list->currentLevels - 1; i >= 0; i--)
    {
        while (current->next[i] != NULL && current->next[i]->value < target)
        {
            current = current->next[i];
        }
    }

    current = current->next[0];

    if (current != NULL && current->value == target)
    {
        return current;
    }
    else
    {
        return NULL;
    }
}

// Função para verificar se um elemento existe na skip-list
int contains(SkipList *list, int target)
{
    Node *result = search(list, target);
    return (result != NULL);
}

// Função para gerar um nível aleatório
int generateRandomLevel(int maxLevels)
{
    int level = 1;
    while (rand() % 2 && level < maxLevels)
    {
        level++;
    }
    return level;
}

// Função para inserir um elemento na skip-list
void insert(SkipList *list, int value)
{
    int level = generateRandomLevel(list->maxLevels);

    if (level > list->currentLevels)
    {
        for (int i = list->currentLevels; i < level; i++)
        {
            list->head->next[i] = NULL;
        }
        list->currentLevels = level;
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = (Node **)malloc(level * sizeof(Node *));

    Node *update[level];
    Node *current = list->head;

    for (int i = level - 1; i >= 0; i--)
    {
        while (current->next[i] != NULL && current->next[i]->value < value)
        {
            current = current->next[i];
        }
        update[i] = current;
    }

    for (int i = 0; i < level; i++)
    {
        newNode->next[i] = update[i]->next[i];
        update[i]->next[i] = newNode;
    }
}

// Função para dar free na skip-list
void freeSkipList(SkipList *list)
{
    Node *current = list->head;
    Node *temp;

    while (current != NULL)
    {
        temp = current;
        current = current->next[0];
        free(temp->next);
        free(temp);
    }

    free(list);
}

// Função para deletar um elemento da skip-list
void delete(SkipList *list, int target)
{
    Node *update[list->maxLevels];
    Node *current = list->head;

    for (int i = list->currentLevels - 1; i >= 0; i--)
    {
        while (current->next[i] != NULL && current->next[i]->value < target)
        {
            current = current->next[i];
        }
        update[i] = current;
    }

    current = current->next[0];

    if (current != NULL && current->value == target)
    {
        for (int i = 0; i < list->currentLevels; i++)
        {
            if (update[i]->next[i] != current)
                break;

            update[i]->next[i] = current->next[i];
        }

        free(current->next);
        free(current);
    }
}

// Função para printar a skip-list
void printSkipList(SkipList *list)
{
    Node *current = list->head->next[0];

    while (current != NULL)
    {
        printf("%d ", current->value);
        current = current->next[0];
    }

    printf("\n");
}
