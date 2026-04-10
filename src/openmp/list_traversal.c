#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* next;
} node;

void process(node* n) {
    printf("Processed %d\n", n->value);
}

int main() {
    // create list: 0 → 1 → ... → 7
    node* head = NULL;
    for (int i = 7; i >= 0; i--) {
        node* n = malloc(sizeof(node));
        n->value = i;
        n->next = head;
        head = n;
    }

    // sequential traversal
    node* cur = head;
    while (cur) {
        process(cur);
        cur = cur->next;
    }

    return 0;
}