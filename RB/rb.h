#ifndef RB_H
#define RB_H

#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    int key;
    Color color;
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *p;
} RBNode;

/* Estrutura com no sentinela T->nil conforme Cormen Cap. 13.1 */
typedef struct {
    RBNode *root;
    RBNode *nil;
} RBTree;

/* Inicializacao e destruicao */
RBTree* rb_create(void);
void rb_destroy(RBTree *T);

/* Operacoes fundamentais (Cormen Cap. 13) */
RBNode* rb_search(RBTree *T, RBNode *x, int k);
RBNode* rb_minimum(RBTree *T, RBNode *x);
void rb_insert(RBTree *T, int key);
void rb_delete(RBTree *T, RBNode *z);

/* Percursos e visualizacao */
void rb_inorder_walk(RBTree *T, RBNode *x);
void rb_export_dot(RBTree *T, const char *filename);

#endif /* RB_H */