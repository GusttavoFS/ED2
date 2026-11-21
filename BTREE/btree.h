#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Grau minimo t conforme Cormen Cap. 18.1:
 * Cada no (exceto raiz) tem no minimo t-1 chaves e no maximo 2t-1 chaves.
 * Com t = 3: minimo 2 chaves, maximo 5 chaves e 6 filhos.
 */
#define T_DEGREE 3

typedef struct BTreeNode {
    int n;                              /* Numero atual de chaves armazenadas */
    int keys[2 * T_DEGREE - 1];         /* Vetor de chaves ordenadas */
    struct BTreeNode *c[2 * T_DEGREE];  /* Ponteiros para os filhos */
    bool leaf;                          /* true se for folha, false caso contrario */
} BTreeNode;

typedef struct {
    BTreeNode *root;
} BTree;

typedef struct {
    BTreeNode *node;
    int index;
} BTreeSearchResult;

/* Inicializacao e destruicao */
BTree* btree_create(void);
void btree_destroy(BTree *T);

/* Operacoes fundamentais (Cormen Cap. 18.2) */
BTreeSearchResult btree_search(BTreeNode *x, int k);
void btree_insert(BTree *T, int k);

/* Percurso e visualizacao */
void btree_traverse(BTreeNode *x);
void btree_export_dot(BTree *T, const char *filename);

#endif /* BTREE_H */