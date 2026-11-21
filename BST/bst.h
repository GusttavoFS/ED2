#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>

/* Estrutura do nó conforme Cormen (Cap. 12):
 * key: chave armazenada
 * left, right: filhos esquerdo e direito
 * p: ponteiro para o nó pai (parent)
 */
typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    struct Node *p;
} Node;

/* Estrutura da Árvore Binária de Busca */
typedef struct {
    Node *root;
} BST;

/* Inicialização e destruição */
BST* bst_create(void);
void bst_destroy(BST *T);

/* Operações fundamentais (Cormen Cap. 12) */
Node* bst_search(Node *x, int k);
Node* bst_iterative_search(Node *x, int k);
Node* bst_minimum(Node *x);
Node* bst_maximum(Node *x);
Node* bst_successor(Node *x);
Node* bst_predecessor(Node *x);

void bst_insert(BST *T, int key);
void bst_delete(BST *T, Node *z);

/* Percursos */
void bst_inorder_walk(Node *x);
void bst_preorder_walk(Node *x);
void bst_postorder_walk(Node *x);

/* Exportação visual (Graphviz) */
void bst_export_dot(BST *T, const char *filename);

#endif /* BST_H */