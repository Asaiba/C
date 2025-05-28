#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// ---------------------- MIN HEAP ----------------------
typedef struct {
    int data[MAX_SIZE];
    int size;
} MinHeap;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapifyUp(MinHeap *heap, int index) {
    int parent = (index - 1) / 2;
    if (index && heap->data[parent] > heap->data[index]) {
        swap(&heap->data[parent], &heap->data[index]);
        minHeapifyUp(heap, parent);
    }
}

void minHeapifyDown(MinHeap *heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;
    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;

    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        minHeapifyDown(heap, smallest);
    }
}

void insertMinHeap(MinHeap *heap, int value) {
    if (heap->size == MAX_SIZE) {
        printf("MinHeap is full!\n");
        return;
    }
    heap->data[heap->size] = value;
    minHeapifyUp(heap, heap->size);
    heap->size++;
}

int deleteMin(MinHeap *heap) {
    if (heap->size == 0) {
        printf("MinHeap is empty!\n");
        return -1;
    }
    int root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    minHeapifyDown(heap, 0);
    return root;
}

void printMinHeap(MinHeap *heap) {
    printf("MinHeap: ");
    for (int i = 0; i < heap->size; i++)
        printf("%d ", heap->data[i]);
    printf("\n");
}

// ---------------------- MAX HEAP ----------------------
typedef struct {
    int data[MAX_SIZE];
    int size;
} MaxHeap;

void maxHeapifyUp(MaxHeap *heap, int index) {
    int parent = (index - 1) / 2;
    if (index && heap->data[parent] < heap->data[index]) {
        swap(&heap->data[parent], &heap->data[index]);
        maxHeapifyUp(heap, parent);
    }
}

void maxHeapifyDown(MaxHeap *heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;

    if (left < heap->size && heap->data[left] > heap->data[largest])
        largest = left;
    if (right < heap->size && heap->data[right] > heap->data[largest])
        largest = right;

    if (largest != index) {
        swap(&heap->data[index], &heap->data[largest]);
        maxHeapifyDown(heap, largest);
    }
}

void insertMaxHeap(MaxHeap *heap, int value) {
    if (heap->size == MAX_SIZE) {
        printf("MaxHeap is full!\n");
        return;
    }
    heap->data[heap->size] = value;
    maxHeapifyUp(heap, heap->size);
    heap->size++;
}

int deleteMax(MaxHeap *heap) {
    if (heap->size == 0) {
        printf("MaxHeap is empty!\n");
        return -1;
    }
    int root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    maxHeapifyDown(heap, 0);
    return root;
}

void printMaxHeap(MaxHeap *heap) {
    printf("MaxHeap: ");
    for (int i = 0; i < heap->size; i++)
        printf("%d ", heap->data[i]);
    printf("\n");
}

// ---------------------- MAIN ----------------------
int main() {
    MinHeap minHeap;
    minHeap.size = 0;

    MaxHeap maxHeap;
    maxHeap.size = 0;

    // Inserting into MinHeap
    insertMinHeap(&minHeap, 15);
    insertMinHeap(&minHeap, 10);
    insertMinHeap(&minHeap, 20);
    insertMinHeap(&minHeap, 8);
    insertMinHeap(&minHeap, 25);

    printMinHeap(&minHeap);
    printf("Deleted Min: %d\n", deleteMin(&minHeap));
    printMinHeap(&minHeap);

    // Inserting into MaxHeap
    insertMaxHeap(&maxHeap, 15);
    insertMaxHeap(&maxHeap, 10);
    insertMaxHeap(&maxHeap, 20);
    insertMaxHeap(&maxHeap, 8);
    insertMaxHeap(&maxHeap, 25);

    printMaxHeap(&maxHeap);
    printf("Deleted Max: %d\n", deleteMax(&maxHeap));
    printMaxHeap(&maxHeap);

    MaxHeap pq;
    pq.size = 0;

    insertMaxHeap(&pq, 15);
    insertMaxHeap(&pq, 10);
    insertMaxHeap(&pq, 20);
    insertMaxHeap(&pq, 8);
    insertMaxHeap(&pq, 25);

    //printMaxHeap(&pq);
    int maxVal = deleteMax(&pq);  // Extract max
    printf("Extracted max (priority): %d\n", maxVal);
    //printMaxHeap(&pq);


    return 0;
}
