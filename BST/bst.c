#include "bst.h"

/* Função auxiliar interna para alocar um novo nó */
static Node* create_node(int key) {
    Node *z = (Node*) malloc(sizeof(Node));
    if (!z) {
        fprintf(stderr, "Erro fatal: falha na alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    z->key = key;
    z->left = NULL;
    z->right = NULL;
    z->p = NULL;
    return z;
}

/* Função auxiliar interna para liberar nós recursivamente (pós-ordem) */
static void free_nodes(Node *x) {
    if (x != NULL) {
        free_nodes(x->left);
        free_nodes(x->right);
        free(x);
    }
}

BST* bst_create(void) {
    BST *T = (BST*) malloc(sizeof(BST));
    if (!T) {
        fprintf(stderr, "Erro fatal: falha na alocação da árvore.\n");
        exit(EXIT_FAILURE);
    }
    T->root = NULL;
    return T;
}

void bst_destroy(BST *T) {
    if (T != NULL) {
        free_nodes(T->root);
        free(T);
    }
}

/* TREE-SEARCH(x, k) - Versão Recursiva */
Node* bst_search(Node *x, int k) {
    if (x == NULL || k == x->key) {
        return x;
    }
    if (k < x->key) {
        return bst_search(x->left, k);
    } else {
        return bst_search(x->right, k);
    }
}

/* ITERATIVE-TREE-SEARCH(x, k) */
Node* bst_iterative_search(Node *x, int k) {
    while (x != NULL && k != x->key) {
        if (k < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

/* TREE-MINIMUM(x) */
Node* bst_minimum(Node *x) {
    if (x == NULL) return NULL;
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}

/* TREE-MAXIMUM(x) */
Node* bst_maximum(Node *x) {
    if (x == NULL) return NULL;
    while (x->right != NULL) {
        x = x->right;
    }
    return x;
}

/* TREE-SUCCESSOR(x) */
Node* bst_successor(Node *x) {
    if (x == NULL) return NULL;
    if (x->right != NULL) {
        return bst_minimum(x->right);
    }
    Node *y = x->p;
    while (y != NULL && x == y->right) {
        x = y;
        y = y->p;
    }
    return y;
}

/* TREE-PREDECESSOR(x) */
Node* bst_predecessor(Node *x) {
    if (x == NULL) return NULL;
    if (x->left != NULL) {
        return bst_maximum(x->left);
    }
    Node *y = x->p;
    while (y != NULL && x == y->left) {
        x = y;
        y = y->p;
    }
    return y;
}

/* TREE-INSERT(T, z) */
void bst_insert(BST *T, int key) {
    Node *z = create_node(key);
    Node *y = NULL;
    Node *x = T->root;

    while (x != NULL) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->p = y;
    if (y == NULL) {
        T->root = z; /* Árvore estava vazia */
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
}

/* TRANSPLANT(T, u, v) - Substitui a subárvore enraizada em u pela enraizada em v */
static void transplant(BST *T, Node *u, Node *v) {
    if (u->p == NULL) {
        T->root = v;
    } else if (u == u->p->left) {
        u->p->left = v;
    } else {
        u->p->right = v;
    }
    if (v != NULL) {
        v->p = u->p;
    }
}

/* TREE-DELETE(T, z) */
void bst_delete(BST *T, Node *z) {
    if (z == NULL) return;

    if (z->left == NULL) {
        transplant(T, z, z->right);
    } else if (z->right == NULL) {
        transplant(T, z, z->left);
    } else {
        Node *y = bst_minimum(z->right);
        if (y->p != z) {
            transplant(T, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        transplant(T, z, y);
        y->left = z->left;
        y->left->p = y;
    }
    free(z);
}

/* INORDER-TREE-WALK(x) */
void bst_inorder_walk(Node *x) {
    if (x != NULL) {
        bst_inorder_walk(x->left);
        printf("%d ", x->key);
        bst_inorder_walk(x->right);
    }
}

/* PREORDER-TREE-WALK(x) */
void bst_preorder_walk(Node *x) {
    if (x != NULL) {
        printf("%d ", x->key);
        bst_preorder_walk(x->left);
        bst_preorder_walk(x->right);
    }
}

/* POSTORDER-TREE-WALK(x) */
void bst_postorder_walk(Node *x) {
    if (x != NULL) {
        bst_postorder_walk(x->left);
        bst_postorder_walk(x->right);
        printf("%d ", x->key);
    }
}

/* Auxiliar para geração do arquivo Graphviz (.dot) */
static void write_dot_nodes(FILE *fp, Node *x) {
    if (x == NULL) return;

    if (x->left != NULL) {
        fprintf(fp, "    \"%p\" [label=\"%d\"];\n", (void*)x, x->key);
        fprintf(fp, "    \"%p\" [label=\"%d\"];\n", (void*)x->left, x->left->key);
        fprintf(fp, "    \"%p\" -> \"%p\" [label=\"E\"];\n", (void*)x, (void*)x->left);
        write_dot_nodes(fp, x->left);
    }
    if (x->right != NULL) {
        fprintf(fp, "    \"%p\" [label=\"%d\"];\n", (void*)x, x->key);
        fprintf(fp, "    \"%p\" [label=\"%d\"];\n", (void*)x->right, x->right->key);
        fprintf(fp, "    \"%p\" -> \"%p\" [label=\"D\"];\n", (void*)x, (void*)x->right);
        write_dot_nodes(fp, x->right);
    }
}

void bst_export_dot(BST *T, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Erro ao abrir arquivo .dot");
        return;
    }
    fprintf(fp, "digraph BST {\n");
    fprintf(fp, "    node [shape=circle, fontname=\"Arial\"];\n");
    if (T->root != NULL && T->root->left == NULL && T->root->right == NULL) {
        fprintf(fp, "    \"%p\" [label=\"%d\"];\n", (void*)T->root, T->root->key);
    } else {
        write_dot_nodes(fp, T->root);
    }
    fprintf(fp, "}\n");
    fclose(fp);
}