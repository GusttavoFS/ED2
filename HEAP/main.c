#include <stdio.h>
#include "heap.h"

int main(void) {
    /* 1. Teste de Fila de Prioridade Maxima (Cormen Fig. 6.5) */
    MaxHeap *H = heap_create(20);
    int initial[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int n = sizeof(initial) / sizeof(initial[0]);

    build_max_heap(H, initial, n);
    printf("Max-Heap construido: ");
    heap_print(H);

    printf("Inserindo chave 15 na fila de prioridade...\n");
    max_heap_insert(H, 15);
    heap_print(H);

    printf("Extraindo maximo: %d\n", heap_extract_max(H));
    printf("Heap apos extracao: ");
    heap_print(H);

    heap_destroy(H);

    /* 2. Teste do algoritmo Heapsort in-place */
    int arr[] = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
    int m = sizeof(arr) / sizeof(arr[0]);
    heapsort(arr, m);

    printf("Vetor ordenado via Heapsort: [ ");
    for (int i = 0; i < m; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");

    return 0;
}