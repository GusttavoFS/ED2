#include "avl.h"

static int max_int(int a, int b) {
    return (a > b) ? a : b;
}

static int node_height(AVLNode *x) {
    return (x == NULL) ? -1 : x->height;
}

static int get_balance(AVLNode *x) {
    if (x == NULL) return 0;
    return node_height(x->left) - node_height(x->right);
}

static void update_height(AVLNode *x) {
    if (x != NULL) {
        x->height = 1 + max_int(node_height(x->left), node_height(x->right));
    }
}

static AVLNode* create_node(int key) {
    AVLNode *z = (AVLNode*) malloc(sizeof(AVLNode));
    if (!z) {
        fprintf(stderr, "Erro fatal: falha na alocacao de memoria.\n");
        exit(EXIT_FAILURE);
    }
    z->key = key;
    z->height = 0;
    z->left = NULL;
    z->right = NULL;
    z->p = NULL;
    return z;
}

static void free_nodes(AVLNode *x) {
    if (x != NULL) {
        free_nodes(x->left);
        free_nodes(x->right);
        free(x);
    }
}

AVLTree* avl_create(void) {
    AVLTree *T = (AVLTree*) malloc(sizeof(AVLTree));
    if (!T) {
        fprintf(stderr, "Erro fatal: falha na alocacao da arvore AVL.\n");
        exit(EXIT_FAILURE);
    }
    T->root = NULL;
    return T;
}

void avl_destroy(AVLTree *T) {
    if (T != NULL) {
        free_nodes(T->root);
        free(T);
    }
}

/* LEFT-ROTATE(T, x) conforme Cormen Cap. 13.2 */
static AVLNode* left_rotate(AVLTree *T, AVLNode *x) {
    AVLNode *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == NULL) {
        T->root = y;
    } else if (x == x->p->left) {
        x->p->left = y;
    } else {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;

    update_height(x);
    update_height(y);
    return y;
}

/* RIGHT-ROTATE(T, y) conforme Cormen Cap. 13.2 */
static AVLNode* right_rotate(AVLTree *T, AVLNode *y) {
    AVLNode *x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->p = y;
    }
    x->p = y->p;
    if (y->p == NULL) {
        T->root = x;
    } else if (y == y->p->right) {
        y->p->right = x;
    } else {
        y->p->left = x;
    }
    x->right = y;
    y->p = x;

    update_height(y);
    update_height(x);
    return x;
}

/* Rebalanceia subindo a partir do no z */
static void avl_rebalance(AVLTree *T, AVLNode *z) {
    while (z != NULL) {
        update_height(z);
        int balance = get_balance(z);

        /* Caso Esquerda-Esquerda (LL) */
        if (balance > 1 && get_balance(z->left) >= 0) {
            z = right_rotate(T, z);
        }
        /* Caso Esquerda-Direita (LR) */
        else if (balance > 1 && get_balance(z->left) < 0) {
            left_rotate(T, z->left);
            z = right_rotate(T, z);
        }
        /* Caso Direita-Direita (RR) */
        else if (balance < -1 && get_balance(z->right) <= 0) {
            z = left_rotate(T, z);
        }
        /* Caso Direita-Esquerda (RL) */
        else if (balance < -1 && get_balance(z->right) > 0) {
            right_rotate(T, z->right);
            z = left_rotate(T, z);
        }

        z = z->p;
    }
}

AVLNode* avl_search(AVLNode *x, int k) {
    while (x != NULL && k != x->key) {
        x = (k < x->key) ? x->left : x->right;
    }
    return x;
}

AVLNode* avl_minimum(AVLNode *x) {
    if (x == NULL) return NULL;
    while (x->left != NULL) x = x->left;
    return x;
}

AVLNode* avl_maximum(AVLNode *x) {
    if (x == NULL) return NULL;
    while (x->right != NULL) x = x->right;
    return x;
}

void avl_insert(AVLTree *T, int key) {
    AVLNode *z = create_node(key);
    AVLNode *y = NULL;
    AVLNode *x = T->root;

    while (x != NULL) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else if (z->key > x->key) {
            x = x->right;
        } else {
            free(z); /* Evita chaves duplicadas */
            return;
        }
    }

    z->p = y;
    if (y == NULL) {
        T->root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    avl_rebalance(T, z->p);
}

static void transplant(AVLTree *T, AVLNode *u, AVLNode *v) {
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

void avl_delete(AVLTree *T, int key) {
    AVLNode *z = avl_search(T->root, key);
    if (z == NULL) return;

    AVLNode *rebalance_start = z->p;

    if (z->left == NULL) {
        transplant(T, z, z->right);
    } else if (z->right == NULL) {
        transplant(T, z, z->left);
    } else {
        AVLNode *y = avl_minimum(z->right);
        rebalance_start = (y->p == z) ? y : y->p;
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
    avl_rebalance(T, rebalance_start);
}

void avl_inorder_walk(AVLNode *x) {
    if (x != NULL) {
        avl_inorder_walk(x->left);
        printf("%d(h=%d) ", x->key, x->height);
        avl_inorder_walk(x->right);
    }
}

static void write_dot_nodes(FILE *fp, AVLNode *x) {
    if (x == NULL) return;
    fprintf(fp, "    \"%p\" [label=\"%d\\n(fb=%d)\"];\n", (void*)x, x->key, get_balance(x));
    if (x->left != NULL) {
        fprintf(fp, "    \"%p\" -> \"%p\" [label=\"E\"];\n", (void*)x, (void*)x->left);
        write_dot_nodes(fp, x->left);
    }
    if (x->right != NULL) {
        fprintf(fp, "    \"%p\" -> \"%p\" [label=\"D\"];\n", (void*)x, (void*)x->right);
        write_dot_nodes(fp, x->right);
    }
}

void avl_export_dot(AVLTree *T, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return;
    fprintf(fp, "digraph AVL {\n    node [shape=circle, fontname=\"Arial\"];\n");
    write_dot_nodes(fp, T->root);
    fprintf(fp, "}\n");
    fclose(fp);
}