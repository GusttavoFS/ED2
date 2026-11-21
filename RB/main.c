#include <stdio.h>
#include "rb.h"

int main(void) {
    RBTree *T = rb_create();

    /* Exemplo classico do Cormen (Fig. 13.4): 11, 2, 14, 1, 7, 15, 5, 8, 4 */
    int keys[] = {11, 2, 14, 1, 7, 15, 5, 8, 4};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        rb_insert(T, keys[i]);
    }

    printf("Percurso Em-Ordem Rubro-Negra: ");
    rb_inorder_walk(T, T->root);
    printf("\nRaiz: %d (%s)\n", T->root->key, (T->root->color == BLACK) ? "BLACK" : "RED");

    rb_export_dot(T, "rb_antes.dot");

    RBNode *node2 = rb_search(T, T->root, 2);
    if (node2 != T->nil) {
        printf("Removendo chave 2...\n");
        rb_delete(T, node2);
    }

    printf("Percurso Em-Ordem apos remocao: ");
    rb_inorder_walk(T, T->root);
    printf("\n");

    rb_export_dot(T, "rb_depois.dot");
    rb_destroy(T);
    return 0;
}