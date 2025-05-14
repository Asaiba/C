#include <stdio.h>
#include <stdbool.h>

#define SIZE 100

typedef struct {
    int data[SIZE];
    int length;
} Array;

void insert(Array *arr, int value) {
    if (arr->length < SIZE) {
        arr->data[arr->length++] = value;
    } else {
        printf("Array is full.\n");
    }
}

void delete(Array *arr, int value) {
    int i, found = 0;
    for (i = 0; i < arr->length; i++) {
        if (arr->data[i] == value) {
            found = 1;
            break;
        }
    }
    if (found) {
        for (int j = i; j < arr->length - 1; j++) {
            arr->data[j] = arr->data[j + 1];
        }
        arr->length--;
    } else {
        printf("%d not found in array.\n", value);
    }
}

bool search(Array *arr, int value) {
    for (int i = 0; i < arr->length; i++) {
        if (arr->data[i] == value) return true;
    }
    return false;
}

void display(Array *arr) {
    printf("Array: ");
    for (int i = 0; i < arr->length; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}

// Test
int main() {
    Array arr = {.length = 0};

    insert(&arr, 10);
    insert(&arr, 20);
    insert(&arr, 30);
    insert(&arr, 50);
    insert(&arr, 60);
    display(&arr);

    delete(&arr, 20);
    display(&arr);

    printf("Search 10: %s\n", search(&arr, 10) ? "Element Found" : "Element Not Found");
    printf("Search 40: %s\n", search(&arr, 40) ? "Element Found" : "Element Not Found");

    return 0;
}
