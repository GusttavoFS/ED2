#include <stdio.h>
#include "hash.h"

int main(void) {
    printf("=== 1. TABELA HASH COM ENCADEAMENTO SEPARADO ===\n");
    ChainedHashTable *CT = chained_hash_create(7);
    int keys[] = {10, 22, 31, 4, 15, 28, 17, 88, 59};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        chained_hash_insert(CT, keys[i], keys[i] * 10);
    }
    chained_hash_print(CT);

    HashNode *found = chained_hash_search(CT, 28);
    if (found) {
        printf("Removendo chave %d (valor %d)...\n", found->key, found->value);
        chained_hash_delete(CT, found);
    }
    chained_hash_destroy(CT);

    printf("\n=== 2. TABELA HASH COM DUPLO HASH (Cormen Cap. 11.4) ===\n");
    OpenHashTable *OT = open_hash_create(11); /* m primo */
    for (int i = 0; i < n; i++) {
        open_hash_insert(OT, keys[i], keys[i] * 100);
    }
    open_hash_print(OT);

    printf("Removendo chave 22 e inserindo chave 33...\n");
    open_hash_delete(OT, 22);
    open_hash_insert(OT, 33, 3300);
    open_hash_print(OT);

    open_hash_destroy(OT);
    return 0;
}