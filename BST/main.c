#include <stdio.h>
#include "bst.h"

int main(void) {
    BST *T = bst_create();

    /* Exemplo clássico de chaves (Cormen Fig. 12.2) */
    int keys[] = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        bst_insert(T, keys[i]);
    }

    printf("Percurso Em-Ordem (Inorder): ");
    bst_inorder_walk(T->root);
    printf("\n");

    Node *min = bst_minimum(T->root);
    Node *max = bst_maximum(T->root);
    printf("Mínimo: %d | Máximo: %d\n", min->key, max->key);

    Node *node13 = bst_search(T->root, 13);
    Node *succ = bst_successor(node13);
    if (succ) {
        printf("Sucessor de %d: %d\n", node13->key, succ->key);
    }

    /* Exporta imagem antes da remoção */
    bst_export_dot(T, "bst_antes.dot");

    /* Remoção de nó com dois filhos (chave 6) */
    Node *node6 = bst_iterative_search(T->root, 6);
    if (node6) {
        printf("Removendo chave %d...\n", node6->key);
        bst_delete(T, node6);
    }

    printf("Percurso Em-Ordem após remoção: ");
    bst_inorder_walk(T->root);
    printf("\n");

    bst_export_dot(T, "bst_depois.dot");

    /* Libera toda a memória (zero leaks no Valgrind) */
    bst_destroy(T);
    return 0;
}