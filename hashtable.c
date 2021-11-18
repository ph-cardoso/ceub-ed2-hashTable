#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "hashtable.h"

struct hashTable
{
    struct Node* arr[HASHTABLE_SIZE];
};

int showMenu(){
    int userOpt = 0;

    system("clear");
    printf("\n---------------------------- MENU ----------------------------\n\n");
    printf("1) Criar HashTable\n");
    printf("2) Imprimir HashTables\n");
    printf("3) Inserir dado na HashTable\n");
    printf("4) Remover dado na HashTable\n");
    printf("5) Buscar dado na HashTable\n");
    printf("6) Unir HashTables\n");
    printf("7) Imprimir HashTable\n");
    printf("8) Popular tabela com valores de teste\n");
    printf("0) Sair\n\n\n");
    printf("Option: ");
    scanf("%d", &userOpt);

    return userOpt;
}

hashTable* createHashTable(){
    hashTable* ht = (hashTable*) malloc(sizeof(hashTable));

    if (ht == NULL)
    {
        printf("\nError: Failed to create hashTable\n");
        getch();
        exit(1);
    }

    int i;
    for(i = 0; i < HASHTABLE_SIZE; i++){
        ht->arr[i] = NULL;
    }

    return ht;
}

void deleteHashTable(hashTable* ht){
    int i;
    for(i = 0; i < HASHTABLE_SIZE; i++){
        Node* current = ht->arr[i];
        Node* next;

        while(current != NULL){
            next = current->next;
            free(current);
            current = next;
        }
    }
    ht = NULL;
}

int hash(int value){
    return value % HASHTABLE_SIZE;
}

int insertHashTable(hashTable* ht, int value){
    int index = hash(value);

    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    if (ht->arr[index] == NULL)
    {
        ht->arr[index] = newNode;
    } else {
        Node* current = ht->arr[index];

        while(current->next != NULL){
            if(current->value == value){
                return 1;
            }

            current = current->next;
        }

        if(current->value != value){
            current->next = newNode;
        } else {
            return 1;
        }
    }

    return 0;
}

void printHashTable(hashTable* ht){
    int i;
    printf("\n\n");
    for(i = 0; i < HASHTABLE_SIZE; i++){
        Node* current = ht->arr[i];

        if (ht->arr[i] == NULL)
        {
            printf("\t%d\t\t---\n", i);
        } else {
            printf("\t%d\t\t", i);
            while(current != NULL){
                printf("%d -> ", current->value);
                current = current->next;
            }
            printf("---\n");
        }
    }
    getch();
}

void deleteAllHashTables(hashTable** tables, int tablesCount){
    int i;
    for(i = 0; i < tablesCount; i++){
        deleteHashTable(tables[i]);
    }
}

void initTablesCollection(hashTable** tables){
    int i;
    for(i = 0; i < TABLE_MAX; i++){
        tables[i] = NULL;
    }
}

void opImprimirTables(int tablesCount){
    printf("\n---------------------------- HASHTABLES ----------------------------\n\n");
    printf("Tabelas Disponiveis: \n");

    int i;
    for(i = 0; i < tablesCount; i++){
        printf("%d) Hash Table %d\n", i+1, i+1);
    }
    printf("\n");
}

int selectHashTable(hashTable** tables, int tablesCount){
    int userOpt = 0;

    do {
        system("clear");
        opImprimirTables(tablesCount);
        printf("Table: ");
        scanf("%d", &userOpt);

        if(userOpt <= 0 || userOpt > tablesCount){
            printf("\nError: Invalid table...");
            getch();
        }
    } while (userOpt <= 0 || userOpt > tablesCount);

    return userOpt - 1;
}

void opCreate(hashTable** tables, int tablesCount){
    tables[tablesCount] = createHashTable();

    if (tables[tablesCount] == NULL){
        printf("\nError: Failed to create hashTable\n");
        getch();
    } else {
        printf("\nHashTable %d criada com sucesso\n", tablesCount+1);
        getch();
    }
}

void opInsert(hashTable** tables, int tablesCount){
    int tableIndex = selectHashTable(tables, tablesCount);
    int value = 0;

    printf("\nDigite o valor a ser inserido: ");
    scanf("%d", &value);

    if(insertHashTable(tables[tableIndex], value) == 0){
        printf("\nValor inserido com sucesso!\n");
        getch();
    } else {
        printf("\nError: Valor ja existe na tabela!\n");
        getch();
    }
}

int deleteElement(hashTable* ht, int value){
    int index = hash(value);

    Node* current = ht->arr[index];
    Node* previous = NULL;

    while(current != NULL){
        if(current->value == value){
            if(previous == NULL){
                ht->arr[index] = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return 0;
        }
        previous = current;
        current = current->next;
    }

    printf("\nError: Valor nao existe na tabela!\n");
    getch();
    return 1;
}

void opDelete(hashTable** tables, int tablesCount){
    int tableIndex = selectHashTable(tables, tablesCount);
    int value = 0;

    printf("\nDigite o valor a ser removido: ");
    scanf("%d", &value);

    if(deleteElement(tables[tableIndex], value) == 0){
        printf("\nValor removido com sucesso!\n");
        getch();
    } else {
        printf("\nError: Valor nao existe na tabela!\n");
        getch();
    }
}

int findElement(hashTable* ht, int value){
    int index = hash(value);

    Node* current = ht->arr[index];

    while(current != NULL){
        if(current->value == value){
            return 0;
        }
        current = current->next;
    }

    return 1;
}

void opSearch(hashTable** tables, int tablesCount){
    int tableIndex = selectHashTable(tables, tablesCount);
    int value = 0;

    printf("\nDigite o valor a ser buscado: ");
    scanf("%d", &value);

    if (findElement(tables[tableIndex], value) == 0){
        printf("\nValor encontrado!\n");
        getch();
    } else {
        printf("\nError: Valor nao existe na tabela!\n");
        getch();
    }
}

void unionHashTable(hashTable* ht, hashTable* htUnion){
    // Insert ht1
    int j;
    for (j = 0; j < HASHTABLE_SIZE; j++){
        Node* current = ht->arr[j];

        while(current != NULL){
            insertHashTable(htUnion, current->value);
            current = current->next;
        }
    }
}

int opUnion(hashTable** tables, int tablesCount){
    int tableIndex1;
    int tableIndex2;

    system("clear");
    printf("\n---------------------------- UNION OPERATION ----------------------------\n\n");
    printf("Selecione as tabelas a serem juntadas: \n");
    opImprimirTables(tablesCount);

    printf("\nTabela 01: \n");
    scanf("%d", &tableIndex1);

    printf("\nTabela 02: \n");
    scanf("%d", &tableIndex2);

    if(tableIndex1 == tableIndex2){
        printf("\nError: Tabelas devem ser diferentes!\n");
        getch();
        return 1;
    } else {
        tables[tablesCount] = createHashTable();
        unionHashTable(tables[tableIndex1-1], tables[tablesCount]);
        unionHashTable(tables[tableIndex2-1], tables[tablesCount]);

        if (tables[tablesCount] == NULL)
        {
            printf("\nError: Failed to unify hashTables\n");
            getch();
            return 1;
        } else {
            printf("\nTabela unida com sucesso!\n");
            getch();
            return 0;
        }
    }
}

void opFillTeste(hashTable** tables, int tablesCount){
    int tableIndex = selectHashTable(tables, tablesCount);

    // Insere 100 valores na hashtable
    int i;
    int r;
    for(i = 0; i < 100; i++){
        r = rand() % 1024;
        insertHashTable(tables[tableIndex], r);
    }
}