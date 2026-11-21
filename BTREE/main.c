#include <stdio.h>
#include "btree.h"

int main(void) {
    BTree *T = btree_create();

    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17, 3, 1, 25, 40, 50, 60};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        btree_insert(T, keys[i]);
    }

    printf("Chaves da Arvore B (grau minimo t=%d) em ordem:\n", T_DEGREE);
    btree_traverse(T->root);
    printf("\n");

    int target = 17;
    BTreeSearchResult res = btree_search(T->root, target);
    if (res.node != NULL) {
        printf("Chave %d encontrada no indice %d da pagina %p.\n",
               target, res.index, (void*)res.node);
    } else {
        printf("Chave %d nao encontrada.\n", target);
    }

    btree_export_dot(T, "btree.dot");
    btree_destroy(T);
    return 0;
}