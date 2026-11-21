#include <stdio.h>
#include "avl.h"

int main(void) {
    AVLTree *T = avl_create();

    /* Insercao sequencial que degeneraria uma BST, mas equilibra na AVL */
    int keys[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        avl_insert(T, keys[i]);
    }

    printf("Percurso Em-Ordem AVL: ");
    avl_inorder_walk(T->root);
    printf("\nRaiz atual: %d\n", T->root->key);

    avl_export_dot(T, "avl_antes.dot");

    printf("Removendo chave 40...\n");
    avl_delete(T, 40);

    printf("Percurso Em-Ordem apos remocao: ");
    avl_inorder_walk(T->root);
    printf("\n");

    avl_export_dot(T, "avl_depois.dot");
    avl_destroy(T);
    return 0;
}