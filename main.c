#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LEVELS 5

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


// SKIP_LIST.C SKIP_LIST.C SKIP_LIST.C SKIP_LIST.C SKIP_LIST.C SKIP_LIST.C SKIP_LIST.C SKIP_LIST.C 

void freeNode(Node* current) {
    if (current) {
        free(current->next);
        free(current);
    }
}


// Função para gerar um nível aleatório
int generateRandomLevel()
{
    int level = 1;
    while (rand() < RAND_MAX / 2 && level < MAX_LEVELS)
    {
        level++;
    }

    return level;
}

// Função para inicializar a skip-list
void initializeSkipList(SkipList *list)
{
    // Aloca memória para o nó cabeça da Skip List
    Node *head = (Node *)malloc(sizeof(Node));

    // Atribui o nó cabeça à lista
    list->head = head;

    // Define a chave do nó cabeça como uma string vazia
    strcpy(head->key, "");

    // Aloca espaço para os ponteiros para os próximos nós em cada nível
    head->next = (Node **)malloc((MAX_LEVELS + 1) * sizeof(Node *));

    // Inicializa os ponteiros para os próximos nós como o próprio nó cabeça
    for (int i = 0; i <= MAX_LEVELS; i++)
    {
        head->next[i] = list->head;
    }

    // Inicializa o número máximo de níveis e o nível atual
    list->maxLevels = 1;
    list->currentLevels = 0;
}

// Função para procurar um elemento na skip-list
Node *search(SkipList *list, char *target)
{
    // Inicializa o ponteiro 'current' como o nó da cabeça da lista.
    Node *current = list->head;

    // Itera através dos níveis da Skip List (começando pelo nível mais alto).
    for (int i = list->currentLevels - 1; i >= 0; i--)
    {
        // Enquanto o próximo nó no nível atual não for o nó da cabeça
        // e a chave do próximo nó for menor que o alvo, avança para o próximo nó.
        while (current->next[i] != list->head && current->next[i]->key < target)
        {
            current = current->next[i];
        }
    }

    // Após percorrer todos os níveis, verifica se o próximo nó no nível 0
    // não é o nó da cabeça e se a chave do próximo nó é igual ao alvo.
    if (current->next[0] != list->head && current->next[0]->key == target)
    {
        // Se a condição for verdadeira, retorna o próximo nó no nível 0.
        return current->next[0];
    }
    else
    {
        // Caso contrário, retorna NULL indicando que o alvo não foi encontrado.
        return NULL;
    }
}

// Função para verificar se um elemento existe na skip-list
int contains(SkipList *list, char *target)
{
    Node *result = search(list, target);
    return (result != NULL);
}

// Função para inserir um elemento na skip-list
void insert(SkipList *list, char *key, char *value)
{
    Node *update[MAX_LEVELS + 1];
    Node *target = list->head;
    int level;

    for (int i = list->currentLevels; i >= 1; i--)
    {
        while (target->next[i] != list->head && strcmp(target->next[i]->key, key) < 0)
        {
            target = target->next[i];
        }

        update[i] = target;
    }

    if (target->next[1] != list->head)
    {
        target = target->next[1];
    }

    if (target != list->head && strcmp(key, target->key) == 0)
    {
        free(target->value);
        target->value = strdup(value);
        return;
    }
    else
    {
        level = generateRandomLevel();

        if (level > list->currentLevels)
        {
            for (int i = list->currentLevels + 1; i <= level; i++)
            {
                update[i] = list->head;
            }

            list->currentLevels = level;
        }

        target = (Node *)malloc(sizeof(Node));
        strcpy(target->key, key);
        target->value = strdup(value);
        target->next = (Node **)malloc(sizeof(Node *) * (level + 1));

        for (int i = 1; i <= level; i++)
        {
            target->next[i] = update[i]->next[i];
            update[i]->next[i] = target;
        }

        list->maxLevels = list->maxLevels + 1;
    }
}

// Função para deletar um elemento da skip-list
void delete(SkipList *list, char *target)
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

        free(current->value);
        freeNode(current);
    }
}

// Função para printar a skip-list
void printSkipList(SkipList *list)
{
    Node *current = list->head;

    while (current && current->next[1] != list->head)
    {
        printf("%s[%s]->", current->next[1]->key, current->next[1]->value);
        current = current->next[1];  
    }

    printf("\n");
}


//MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN


int main()
{
    char op;
    SkipList list;
    initializeSkipList(&list);

    while (1)
    {
        scanf("%c", &op);

        // Sair do loop infinito
        if (op == '0')
        {
            break;
        }

        // Dados pelo enunciado
        char name[11];
        char number[10];

        if (op == 'P')
        {
            scanf("%s", name);

            Node *node = search(&list, name);
            if (node == NULL)
            {
                printf("Contatinho nao encontrado\n");
            }
            else
            {
                printf("Contatinho encontrado: telefone %s\n", node->value);
            }
        }
        else if (op == 'I')
        {
            scanf("%s %s", name, number);

            if (contains(&list, name) == 1)
            {
                printf("Contatinho ja inserido\n");
            }
            else
            {
                insert(&list, name, number);
            }
        }
        else if (op == 'A')
        {
            scanf("%s %s", name, number);

            if (contains(&list, name) == 0)
            {
                printf("Operacao invalida: contatinho nao encontrado\n");
            }
            else
            {
                insert(&list, name, number);
            }
        }
        else if (op == 'R')
        {
            scanf("%s", name);

            if (contains(&list, name) == 0)
            {
                printf("Operacao invalida: contatinho nao encontrado\n");
            }
            else
            {
                delete (&list, name);
            }
        }
    }


    return 0;
}
