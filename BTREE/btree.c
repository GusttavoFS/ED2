#include "btree.h"

/* ALLOCATE-NODE() */
static BTreeNode* allocate_node(bool leaf) {
    BTreeNode *x = (BTreeNode*) malloc(sizeof(BTreeNode));
    if (!x) {
        fprintf(stderr, "Erro fatal: falha na alocacao do no da Arvore B.\n");
        exit(EXIT_FAILURE);
    }
    x->leaf = leaf;
    x->n = 0;
    for (int i = 0; i < 2 * T_DEGREE; i++) {
        x->c[i] = NULL;
    }
    return x;
}

static void free_nodes(BTreeNode *x) {
    if (x == NULL) return;
    if (!x->leaf) {
        for (int i = 0; i <= x->n; i++) {
            free_nodes(x->c[i]);
        }
    }
    free(x);
}

/* B-TREE-CREATE(T) */
BTree* btree_create(void) {
    BTree *T = (BTree*) malloc(sizeof(BTree));
    if (!T) {
        fprintf(stderr, "Erro fatal: falha na alocacao da Arvore B.\n");
        exit(EXIT_FAILURE);
    }
    BTreeNode *x = allocate_node(true);
    T->root = x;
    return T;
}

void btree_destroy(BTree *T) {
    if (T != NULL) {
        free_nodes(T->root);
        free(T);
    }
}

/* B-TREE-SEARCH(x, k) - Cormen Cap. 18.2 */
BTreeSearchResult btree_search(BTreeNode *x, int k) {
    int i = 0;
    while (i < x->n && k > x->keys[i]) {
        i++;
    }
    if (i < x->n && k == x->keys[i]) {
        BTreeSearchResult res = {x, i};
        return res;
    } else if (x->leaf) {
        BTreeSearchResult res = {NULL, -1};
        return res;
    } else {
        return btree_search(x->c[i], k);
    }
}

/* B-TREE-SPLIT-CHILD(x, i) - Divide o filho cheio y = x->c[i] */
static void btree_split_child(BTreeNode *x, int i) {
    BTreeNode *y = x->c[i];
    BTreeNode *z = allocate_node(y->leaf);
    z->n = T_DEGREE - 1;

    /* Copia as ultimas t-1 chaves de y para z */
    for (int j = 0; j < T_DEGREE - 1; j++) {
        z->keys[j] = y->keys[j + T_DEGREE];
    }

    /* Se y nao for folha, copia os ultimos t filhos de y para z */
    if (!y->leaf) {
        for (int j = 0; j < T_DEGREE; j++) {
            z->c[j] = y->c[j + T_DEGREE];
        }
    }

    y->n = T_DEGREE - 1;

    /* Abre espaco nos ponteiros de filhos de x */
    for (int j = x->n; j >= i + 1; j--) {
        x->c[j + 1] = x->c[j];
    }
    x->c[i + 1] = z;

    /* Abre espaco nas chaves de x */
    for (int j = x->n - 1; j >= i; j--) {
        x->keys[j + 1] = x->keys[j];
    }

    /* Sobe a chave mediana de y para x */
    x->keys[i] = y->keys[T_DEGREE - 1];
    x->n = x->n + 1;
}

/* B-TREE-INSERT-NONFULL(x, k) */
static void btree_insert_nonfull(BTreeNode *x, int k) {
    int i = x->n - 1;

    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n = x->n + 1;
    } else {
        while (i >= 0 && k < x->keys[i]) {
            i--;
        }
        i++;
        if (x->c[i]->n == 2 * T_DEGREE - 1) {
            btree_split_child(x, i);
            if (k > x->keys[i]) {
                i++;
            }
        }
        btree_insert_nonfull(x->c[i], k);
    }
}

/* B-TREE-INSERT(T, k) */
void btree_insert(BTree *T, int k) {
    BTreeNode *r = T->root;
    if (r->n == 2 * T_DEGREE - 1) {
        BTreeNode *s = allocate_node(false);
        T->root = s;
        s->c[0] = r;
        btree_split_child(s, 0);
        btree_insert_nonfull(s, k);
    } else {
        btree_insert_nonfull(r, k);
    }
}

/* Percurso em ordem (imprime todas as chaves ordenadas) */
void btree_traverse(BTreeNode *x) {
    if (x == NULL) return;
    int i;
    for (i = 0; i < x->n; i++) {
        if (!x->leaf) {
            btree_traverse(x->c[i]);
        }
        printf("%d ", x->keys[i]);
    }
    if (!x->leaf) {
        btree_traverse(x->c[i]);
    }
}

/* Exporta a estrutura de paginas da Arvore B para Graphviz (.dot) */
static void write_dot_nodes(FILE *fp, BTreeNode *x) {
    if (x == NULL) return;

    fprintf(fp, "    \"%p\" [label=\"", (void*)x);
    for (int i = 0; i < x->n; i++) {
        fprintf(fp, "<f%d> |%d|", i, x->keys[i]);
    }
    fprintf(fp, "<f%d>\"];\n", x->n);

    if (!x->leaf) {
        for (int i = 0; i <= x->n; i++) {
            if (x->c[i] != NULL) {
                fprintf(fp, "    \"%p\":f%d -> \"%p\";\n", (void*)x, i, (void*)x->c[i]);
                write_dot_nodes(fp, x->c[i]);
            }
        }
    }
}

void btree_export_dot(BTree *T, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return;
    fprintf(fp, "digraph BTree {\n    node [shape=record, fontname=\"Arial\"];\n");
    write_dot_nodes(fp, T->root);
    fprintf(fp, "}\n");
    fclose(fp);
}