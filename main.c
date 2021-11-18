// Alunos: Pedro Henrique Lima Cardoso e Mark Davis
// Estrutura de Dados II
// Hashtables
// 18.11.2021

// Os comandos de sistema estão adaptados apenas para Linux.
// Se você estiver usando Windows, utilize o WSL, gitbash ou powershell para executar o programa.

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "hashtable.h"

int main()
{
    // HashTables collection
    int tablesCount = 0;
    hashTable* tables[TABLE_MAX];
    initTablesCollection(tables);
    srand(time(NULL));

    int userOpt;
    do {
        userOpt = showMenu();
        switch (userOpt)
        {
        case 1:
            if(tablesCount < TABLE_MAX){
                opCreate(tables, tablesCount);
                tablesCount++;
            } else {
                printf("\nError: Limtie de %d tabelas atingido\n", TABLE_MAX);
                getch();
            }
            break;
        case 2:
            if(tablesCount > 0){
                opImprimirTables(tablesCount);
                getch();
            } else {
                printf("\nError: Nenhuma tabela criada\n");
                getch();
            }
            break;
        case 3:
            opInsert(tables, tablesCount);
            break;
        case 4:
            opDelete(tables, tablesCount);
            break;
        case 5:
            opSearch(tables, tablesCount);
            break;
        case 6:
            if(tablesCount < TABLE_MAX){
                if(opUnion(tables, tablesCount) == 0){
                    tablesCount++;
                }
            } else {
                printf("\nError: Limtie de %d tabelas atingido\n", TABLE_MAX);
                getch();
            }
            break;
        case 7:
            printHashTable(tables[selectHashTable(tables, tablesCount)]);
            break;
        case 8:
            opFillTeste(tables, tablesCount);
            break;
        case 0:
            break;
        default:
            printf("\nError: Invalid Option...\n");
            getch();
        }
    } while (userOpt != 0);

    deleteAllHashTables(tables, tablesCount);

    return 0;
}