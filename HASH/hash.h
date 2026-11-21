#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/* =========================================================================
 * 1. TABELA HASH COM ENCADEAMENTO SEPARADO (Cormen Cap. 11.2)
 * ========================================================================= */
typedef struct HashNode {
    int key;
    int value;
    struct HashNode *next;
    struct HashNode *prev;
} HashNode;

typedef struct {
    int m;              /* Numero de slots da tabela */
    HashNode **table;   /* Vetor de listas duplamente ligadas */
} ChainedHashTable;

ChainedHashTable* chained_hash_create(int m);
void chained_hash_destroy(ChainedHashTable *T);
void chained_hash_insert(ChainedHashTable *T, int key, int value);
HashNode* chained_hash_search(ChainedHashTable *T, int key);
void chained_hash_delete(ChainedHashTable *T, HashNode *x);
void chained_hash_print(const ChainedHashTable *T);

/* =========================================================================
 * 2. TABELA HASH COM ENDERECAMENTO ABERTO - DUPLO HASH (Cormen Cap. 11.4)
 * ========================================================================= */
typedef enum { SLOT_EMPTY, SLOT_OCCUPIED, SLOT_DELETED } SlotState;

typedef struct {
    int key;
    int value;
    SlotState state;
} OpenSlot;

typedef struct {
    int m;              /* Tamanho da tabela (idealmente numero primo) */
    OpenSlot *table;
} OpenHashTable;

OpenHashTable* open_hash_create(int m);
void open_hash_destroy(OpenHashTable *T);
int open_hash_insert(OpenHashTable *T, int key, int value);
int open_hash_search(const OpenHashTable *T, int key);
bool open_hash_delete(OpenHashTable *T, int key);
void open_hash_print(const OpenHashTable *T);

#endif /* HASH_H */