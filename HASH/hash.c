#include "hash.h"

/* Constante aurea sugerida no Cormen Cap. 11.3.2: (sqrt(5) - 1) / 2 */
#define KNUTH_A 0.6180339887498949

/* Metodo da Multiplicacao: h(k) = floor(m * ((k * A) mod 1)) */
static int hash_mult(int k, int m) {
    double key_abs = fabs((double)k);
    double frac = (key_abs * KNUTH_A) - floor(key_abs * KNUTH_A);
    return (int)floor(m * frac);
}

/* =========================================================================
 * ENCADEAMENTO SEPARADO
 * ========================================================================= */

ChainedHashTable* chained_hash_create(int m) {
    ChainedHashTable *T = (ChainedHashTable*) malloc(sizeof(ChainedHashTable));
    if (!T) exit(EXIT_FAILURE);
    T->m = m;
    T->table = (HashNode**) calloc(m, sizeof(HashNode*));
    if (!T->table) {
        free(T);
        exit(EXIT_FAILURE);
    }
    return T;
}

void chained_hash_destroy(ChainedHashTable *T) {
    if (!T) return;
    for (int i = 0; i < T->m; i++) {
        HashNode *curr = T->table[i];
        while (curr != NULL) {
            HashNode *next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(T->table);
    free(T);
}

/* CHAINED-HASH-INSERT(T, x) */
void chained_hash_insert(ChainedHashTable *T, int key, int value) {
    /* Atualiza valor se chave ja existir */
    HashNode *existing = chained_hash_search(T, key);
    if (existing != NULL) {
        existing->value = value;
        return;
    }

    int idx = hash_mult(key, T->m);
    HashNode *x = (HashNode*) malloc(sizeof(HashNode));
    if (!x) exit(EXIT_FAILURE);

    x->key = key;
    x->value = value;
    x->prev = NULL;
    x->next = T->table[idx];

    if (T->table[idx] != NULL) {
        T->table[idx]->prev = x;
    }
    T->table[idx] = x;
}

/* CHAINED-HASH-SEARCH(T, k) */
HashNode* chained_hash_search(ChainedHashTable *T, int key) {
    int idx = hash_mult(key, T->m);
    HashNode *curr = T->table[idx];
    while (curr != NULL && curr->key != key) {
        curr = curr->next;
    }
    return curr;
}

/* CHAINED-HASH-DELETE(T, x) */
void chained_hash_delete(ChainedHashTable *T, HashNode *x) {
    if (x == NULL) return;
    int idx = hash_mult(x->key, T->m);

    if (x->prev != NULL) {
        x->prev->next = x->next;
    } else {
        T->table[idx] = x->next;
    }
    if (x->next != NULL) {
        x->next->prev = x->prev;
    }
    free(x);
}

void chained_hash_print(const ChainedHashTable *T) {
    for (int i = 0; i < T->m; i++) {
        printf("Slot [%02d]: ", i);
        HashNode *curr = T->table[i];
        while (curr != NULL) {
            printf("(%d -> %d) <-> ", curr->key, curr->value);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

/* =========================================================================
 * ENDERECAMENTO ABERTO (DUPLO HASH - Cormen Cap. 11.4)
 * h(k, i) = (h1(k) + i * h2(k)) mod m
 * ========================================================================= */

static int h1(int k, int m) {
    int r = k % m;
    return (r < 0) ? r + m : r;
}

static int h2(int k, int m) {
    int r = k % (m - 1);
    if (r < 0) r += (m - 1);
    return 1 + r;
}

OpenHashTable* open_hash_create(int m) {
    OpenHashTable *T = (OpenHashTable*) malloc(sizeof(OpenHashTable));
    if (!T) exit(EXIT_FAILURE);
    T->m = m;
    T->table = (OpenSlot*) malloc(sizeof(OpenSlot) * m);
    if (!T->table) {
        free(T);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < m; i++) {
        T->table[i].state = SLOT_EMPTY;
    }
    return T;
}

void open_hash_destroy(OpenHashTable *T) {
    if (!T) return;
    free(T->table);
    free(T);
}

/* HASH-INSERT(T, k) */
int open_hash_insert(OpenHashTable *T, int key, int value) {
    int i = 0;
    int first_deleted = -1;

    while (i < T->m) {
        int j = (h1(key, T->m) + i * h2(key, T->m)) % T->m;
        if (T->table[j].state == SLOT_OCCUPIED && T->table[j].key == key) {
            T->table[j].value = value;
            return j;
        }
        if (T->table[j].state == SLOT_DELETED && first_deleted == -1) {
            first_deleted = j;
        }
        if (T->table[j].state == SLOT_EMPTY) {
            int target = (first_deleted != -1) ? first_deleted : j;
            T->table[target].key = key;
            T->table[target].value = value;
            T->table[target].state = SLOT_OCCUPIED;
            return target;
        }
        i++;
    }

    if (first_deleted != -1) {
        T->table[first_deleted].key = key;
        T->table[first_deleted].value = value;
        T->table[first_deleted].state = SLOT_OCCUPIED;
        return first_deleted;
    }

    fprintf(stderr, "Erro: hash table overflow.\n");
    return -1;
}

/* HASH-SEARCH(T, k) */
int open_hash_search(const OpenHashTable *T, int key) {
    int i = 0;
    while (i < T->m) {
        int j = (h1(key, T->m) + i * h2(key, T->m)) % T->m;
        if (T->table[j].state == SLOT_EMPTY) {
            return -1;
        }
        if (T->table[j].state == SLOT_OCCUPIED && T->table[j].key == key) {
            return j;
        }
        i++;
    }
    return -1;
}

/* HASH-DELETE(T, k) com marcador DELETED (Cormen Ex. 11.4-2) */
bool open_hash_delete(OpenHashTable *T, int key) {
    int idx = open_hash_search(T, key);
    if (idx == -1) return false;
    T->table[idx].state = SLOT_DELETED;
    return true;
}

void open_hash_print(const OpenHashTable *T) {
    for (int i = 0; i < T->m; i++) {
        printf("Slot [%02d]: ", i);
        if (T->table[i].state == SLOT_EMPTY) {
            printf("EMPTY\n");
        } else if (T->table[i].state == SLOT_DELETED) {
            printf("DELETED\n");
        } else {
            printf("Key=%d, Val=%d\n", T->table[i].key, T->table[i].value);
        }
    }
}