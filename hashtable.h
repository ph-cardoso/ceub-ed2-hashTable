#ifndef HASHTABLE_LIB
#define HASHTABLE_LIB

// Definitions
#define HASHTABLE_SIZE 50
#define TABLE_MAX 10

// Structs
typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct hashTable hashTable;

// Functions prototypes
// Util functions
int showMenu(); // Mostra o menu de opções e pega a opção do usuário
void initTablesCollection(hashTable**); // Inicializa as tabelas com NULL
void deleteAllHashTables(hashTable**, int); // Deleta todas as tabelas
int selectHashTable(hashTable**, int); // Pega o index da tabela Hash que vai sofrer a operação

// Operações
void opCreate(hashTable**, int); // Operação de criação
void opImprimirTables(int); // Operação de impressão das Hash Tables criadas
void opInsert(hashTable**, int); // Operação de inserção de elementos
void opDelete(hashTable**, int); // Operação de deleção de elementos
void opSearch(hashTable**, int); // Operação de busca de elementos
int opUnion(hashTable**, int); // Operação de união de Hash Tables
void opFillTeste(hashTable**, int); // Preenche uma Hash Table com 1024 valores aleatórios

// Hash table functions
hashTable* createHashTable(); // Cria uma tabela hash
void deleteHashTable(hashTable*); // Deleta uma tabela hash
int hash(int); // Recebe um valor e retorna o hash dele
int insertHashTable(hashTable*, int); // Insere um elemento na tabela hash
void printHashTable(hashTable*); // Imprime a tabela hash
int deleteElement(hashTable*, int value); // Deleta um elemento da tabela hash
int findElement(hashTable*, int value); // Procura um elemento na tabela hash
void unionHashTable(hashTable*, hashTable*); // Une duas tabelas hash

#endif