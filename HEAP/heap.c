#include "heap.h"

/* Macros de navegacao (indexacao base 0 adaptada do Cormen) */
#define PARENT(i) (((i) - 1) / 2)
#define LEFT(i)   (2 * (i) + 1)
#define RIGHT(i)  (2 * (i) + 2)

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

MaxHeap* heap_create(int capacity) {
    MaxHeap *H = (MaxHeap*) malloc(sizeof(MaxHeap));
    if (!H) {
        fprintf(stderr, "Erro fatal: falha na alocacao do Heap.\n");
        exit(EXIT_FAILURE);
    }
    H->A = (int*) malloc(sizeof(int) * capacity);
    if (!H->A) {
        free(H);
        fprintf(stderr, "Erro fatal: falha na alocacao do vetor do Heap.\n");
        exit(EXIT_FAILURE);
    }
    H->length = capacity;
    H->heap_size = 0;
    return H;
}

void heap_destroy(MaxHeap *H) {
    if (H != NULL) {
        free(H->A);
        free(H);
    }
}

/* MAX-HEAPIFY(A, i) - Cormen Cap. 6.2 */
void max_heapify(MaxHeap *H, int i) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int largest = i;

    if (l < H->heap_size && H->A[l] > H->A[largest]) {
        largest = l;
    }
    if (r < H->heap_size && H->A[r] > H->A[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap(&H->A[i], &H->A[largest]);
        max_heapify(H, largest);
    }
}

/* BUILD-MAX-HEAP(A) - Cormen Cap. 6.3 */
void build_max_heap(MaxHeap *H, const int *arr, int n) {
    if (n > H->length) {
        fprintf(stderr, "Erro: tamanho excede a capacidade do Heap.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        H->A[i] = arr[i];
    }
    H->heap_size = n;

    for (int i = (n / 2) - 1; i >= 0; i--) {
        max_heapify(H, i);
    }
}

/* HEAPSORT(A) - Cormen Cap. 6.4 */
void heapsort(int *arr, int n) {
    MaxHeap H;
    H.A = arr;
    H.length = n;
    H.heap_size = n;

    for (int i = (n / 2) - 1; i >= 0; i--) {
        max_heapify(&H, i);
    }

    for (int i = n - 1; i >= 1; i--) {
        swap(&H.A[0], &H.A[i]);
        H.heap_size--;
        max_heapify(&H, 0);
    }
}

/* HEAP-MAXIMUM(A) */
int heap_maximum(const MaxHeap *H) {
    if (H->heap_size < 1) {
        fprintf(stderr, "Erro: heap underflow.\n");
        return INT_MIN;
    }
    return H->A[0];
}

/* HEAP-EXTRACT-MAX(A) */
int heap_extract_max(MaxHeap *H) {
    if (H->heap_size < 1) {
        fprintf(stderr, "Erro: heap underflow.\n");
        return INT_MIN;
    }
    int max = H->A[0];
    H->A[0] = H->A[H->heap_size - 1];
    H->heap_size--;
    max_heapify(H, 0);
    return max;
}

/* HEAP-INCREASE-KEY(A, i, key) */
void heap_increase_key(MaxHeap *H, int i, int key) {
    if (key < H->A[i]) {
        fprintf(stderr, "Erro: nova chave e menor que a chave atual.\n");
        return;
    }
    H->A[i] = key;
    while (i > 0 && H->A[PARENT(i)] < H->A[i]) {
        swap(&H->A[i], &H->A[PARENT(i)]);
        i = PARENT(i);
    }
}

/* MAX-HEAP-INSERT(A, key) */
void max_heap_insert(MaxHeap *H, int key) {
    if (H->heap_size == H->length) {
        fprintf(stderr, "Erro: heap overflow.\n");
        return;
    }
    H->heap_size++;
    H->A[H->heap_size - 1] = INT_MIN;
    heap_increase_key(H, H->heap_size - 1, key);
}

void heap_print(const MaxHeap *H) {
    printf("[ ");
    for (int i = 0; i < H->heap_size; i++) {
        printf("%d ", H->A[i]);
    }
    printf("]\n");
}