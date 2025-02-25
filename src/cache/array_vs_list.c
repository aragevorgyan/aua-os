#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000000  // 10 million elements

// Node structure for linked list
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// Function to create a linked list with N elements
Node* create_linked_list(int n) {
    Node* head = malloc(sizeof(Node));
    Node* current = head;
    for (int i = 0; i < n - 1; i++) {
        current->next = malloc(sizeof(Node));
        current = current->next;
    }
    current->next = NULL;
    return head;
}

// Function to traverse the linked list
void traverse_linked_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        current->value += 1;  // Dummy operation
        current = current->next;
    }
}

// Function to free the linked list
void free_linked_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

// Function to traverse an array
void traverse_array(int* arr, int n) {
    volatile int dummy = 0;  // Prevent compiler optimizations
    for (int i = 0; i < n; i++) {
        dummy += arr[i];
    }
}

int main() {
    clock_t start, end;
    double time_array, time_list;

    // Allocate memory for array
    int* array = malloc(N * sizeof(int));

    // Allocate memory for linked list
    Node* list = create_linked_list(N);

    // Measure time for array traversal
    start = clock();
    traverse_array(array, N);
    end = clock();
    time_array = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Array traversal time: %f seconds\n", time_array);

    // Measure time for linked list traversal
    start = clock();
    traverse_linked_list(list);
    end = clock();
    time_list = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Linked list traversal time: %f seconds\n", time_list);

    // Free allocated memory
    free(array);
    free_linked_list(list);

    return 0;
}
