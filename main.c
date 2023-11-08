#include <stdio.h>
#include <string.h>
#include "./lib/skip_list/skip_list.h"

int main()
{
    char op;

    SkipList list;
    initializeSkipList(&list);

    while (1)
    {
        scanf(" %c", &op);

        // Sair do loop infinito
        if (op == '0')
        {
            break;
        }

        // Dados pelo enuciado
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

            if (exists(&list, name) == 1)
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

            if (exists(&list, name) == 0)
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

            if (exists(&list, name) == 0)
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
