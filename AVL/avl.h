#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int key;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
    struct AVLNode *p;
} AVLNode;

typedef struct {
    AVLNode *root;
} AVLTree;

/* Inicializacao e destruicao */
AVLTree* avl_create(void);
void avl_destroy(AVLTree *T);

/* Operacoes fundamentais */
AVLNode* avl_search(AVLNode *x, int k);
AVLNode* avl_minimum(AVLNode *x);
AVLNode* avl_maximum(AVLNode *x);

void avl_insert(AVLTree *T, int key);
void avl_delete(AVLTree *T, int key);

/* Percursos e visualizacao */
void avl_inorder_walk(AVLNode *x);
void avl_export_dot(AVLTree *T, const char *filename);

#endif /* AVL_H */