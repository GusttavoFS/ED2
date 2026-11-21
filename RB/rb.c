#include "rb.h"

RBTree* rb_create(void) {
    RBTree *T = (RBTree*) malloc(sizeof(RBTree));
    RBNode *nil = (RBNode*) malloc(sizeof(RBNode));
    if (!T || !nil) {
        fprintf(stderr, "Erro fatal: falha na alocacao da Arvore Rubro-Negra.\n");
        exit(EXIT_FAILURE);
    }
    nil->color = BLACK;
    nil->left = nil;
    nil->right = nil;
    nil->p = nil;
    nil->key = 0;

    T->nil = nil;
    T->root = nil;
    return T;
}

static void free_nodes(RBTree *T, RBNode *x) {
    if (x != T->nil) {
        free_nodes(T, x->left);
        free_nodes(T, x->right);
        free(x);
    }
}

void rb_destroy(RBTree *T) {
    if (T != NULL) {
        free_nodes(T, T->root);
        free(T->nil);
        free(T);
    }
}

/* LEFT-ROTATE(T, x) */
static void left_rotate(RBTree *T, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left != T->nil) {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == T->nil) {
        T->root = y;
    } else if (x == x->p->left) {
        x->p->left = y;
    } else {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
}

/* RIGHT-ROTATE(T, y) */
static void right_rotate(RBTree *T, RBNode *y) {
    RBNode *x = y->left;
    y->left = x->right;
    if (x->right != T->nil) {
        x->right->p = y;
    }
    x->p = y->p;
    if (y->p == T->nil) {
        T->root = x;
    } else if (y == y->p->right) {
        y->p->right = x;
    } else {
        y->p->left = x;
    }
    x->right = y;
    y->p = x;
}

/* RB-INSERT-FIXUP(T, z) - Cormen Cap. 13.3 */
static void rb_insert_fixup(RBTree *T, RBNode *z) {
    while (z->p->color == RED) {
        if (z->p == z->p->p->left) {
            RBNode *y = z->p->p->right; /* Tio de z */
            if (y->color == RED) {
                /* Caso 1: tio vermelho */
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->right) {
                    /* Caso 2: tio preto e z e filho a direita */
                    z = z->p;
                    left_rotate(T, z);
                }
                /* Caso 3: tio preto e z e filho a esquerda */
                z->p->color = BLACK;
                z->p->p->color = RED;
                right_rotate(T, z->p->p);
            }
        } else {
            RBNode *y = z->p->p->left;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->left) {
                    z = z->p;
                    right_rotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                left_rotate(T, z->p->p);
            }
        }
    }
    T->root->color = BLACK;
}

/* RB-INSERT(T, z) */
void rb_insert(RBTree *T, int key) {
    RBNode *z = (RBNode*) malloc(sizeof(RBNode));
    if (!z) exit(EXIT_FAILURE);
    z->key = key;

    RBNode *y = T->nil;
    RBNode *x = T->root;

    while (x != T->nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->p = y;
    if (y == T->nil) {
        T->root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = T->nil;
    z->right = T->nil;
    z->color = RED;
    rb_insert_fixup(T, z);
}

/* RB-TRANSPLANT(T, u, v) */
static void rb_transplant(RBTree *T, RBNode *u, RBNode *v) {
    if (u->p == T->nil) {
        T->root = v;
    } else if (u == u->p->left) {
        u->p->left = v;
    } else {
        u->p->right = v;
    }
    v->p = u->p;
}

RBNode* rb_minimum(RBTree *T, RBNode *x) {
    while (x->left != T->nil) {
        x = x->left;
    }
    return x;
}

RBNode* rb_search(RBTree *T, RBNode *x, int k) {
    while (x != T->nil && k != x->key) {
        x = (k < x->key) ? x->left : x->right;
    }
    return x;
}

/* RB-DELETE-FIXUP(T, x) - Cormen Cap. 13.4 */
static void rb_delete_fixup(RBTree *T, RBNode *x) {
    while (x != T->root && x->color == BLACK) {
        if (x == x->p->left) {
            RBNode *w = x->p->right; /* Irmao de x */
            if (w->color == RED) {
                /* Caso 1 */
                w->color = BLACK;
                x->p->color = RED;
                left_rotate(T, x->p);
                w = x->p->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                /* Caso 2 */
                w->color = RED;
                x = x->p;
            } else {
                if (w->right->color == BLACK) {
                    /* Caso 3 */
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(T, w);
                    w = x->p->right;
                }
                /* Caso 4 */
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                left_rotate(T, x->p);
                x = T->root;
            }
        } else {
            RBNode *w = x->p->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                right_rotate(T, x->p);
                w = x->p->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->p;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(T, w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                right_rotate(T, x->p);
                x = T->root;
            }
        }
    }
    x->color = BLACK;
}

/* RB-DELETE(T, z) */
void rb_delete(RBTree *T, RBNode *z) {
    if (z == T->nil) return;

    RBNode *y = z;
    RBNode *x;
    Color y_original_color = y->color;

    if (z->left == T->nil) {
        x = z->right;
        rb_transplant(T, z, z->right);
    } else if (z->right == T->nil) {
        x = z->left;
        rb_transplant(T, z, z->left);
    } else {
        y = rb_minimum(T, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->p == z) {
            x->p = y;
        } else {
            rb_transplant(T, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        rb_transplant(T, z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }

    free(z);
    if (y_original_color == BLACK) {
        rb_delete_fixup(T, x);
    }
}

void rb_inorder_walk(RBTree *T, RBNode *x) {
    if (x != T->nil) {
        rb_inorder_walk(T, x->left);
        printf("%d(%c) ", x->key, (x->color == RED) ? 'R' : 'B');
        rb_inorder_walk(T, x->right);
    }
}

static void write_dot_nodes(FILE *fp, RBTree *T, RBNode *x) {
    if (x == T->nil) return;
    const char *fill = (x->color == RED) ? "#e74c3c" : "#2c3e50";
    fprintf(fp, "    \"%p\" [label=\"%d\", style=filled, fillcolor=\"%s\", fontcolor=white];\n",
            (void*)x, x->key, fill);
    if (x->left != T->nil) {
        fprintf(fp, "    \"%p\" -> \"%p\";\n", (void*)x, (void*)x->left);
        write_dot_nodes(fp, T, x->left);
    }
    if (x->right != T->nil) {
        fprintf(fp, "    \"%p\" -> \"%p\";\n", (void*)x, (void*)x->right);
        write_dot_nodes(fp, T, x->right);
    }
}

void rb_export_dot(RBTree *T, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return;
    fprintf(fp, "digraph RBTree {\n    node [shape=circle, fontname=\"Arial\"];\n");
    write_dot_nodes(fp, T, T->root);
    fprintf(fp, "}\n");
    fclose(fp);
}