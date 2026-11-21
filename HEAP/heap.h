#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *A;         /* Vetor de elementos */
    int length;     /* Capacidade total alocada */
    int heap_size;  /* Quantidade atual de elementos validos no heap */
} MaxHeap;

/* Inicializacao e destruicao */
MaxHeap* heap_create(int capacity);
void heap_destroy(MaxHeap *H);

/* Procedimentos fundamentais (Cormen Cap. 6.2 - 6.4) */
void max_heapify(MaxHeap *H, int i);
void build_max_heap(MaxHeap *H, const int *arr, int n);
void heapsort(int *arr, int n);

/* Fila de Prioridade Maxima (Cormen Cap. 6.5) */
int heap_maximum(const MaxHeap *H);
int heap_extract_max(MaxHeap *H);
void heap_increase_key(MaxHeap *H, int i, int key);
void max_heap_insert(MaxHeap *H, int key);

/* Utilitario */
void heap_print(const MaxHeap *H);

#endif /* HEAP_H */