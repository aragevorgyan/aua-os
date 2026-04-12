#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

typedef struct node {
    int value;
    struct node* next;
} node;

void process(node* n) {
    printf("Processed %d by thread %d\n",
           n->value, omp_get_thread_num());
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

    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        {
            node* cur = head;

            while (cur) {
                node* tmp = cur;   // IMPORTANT!

                #pragma omp task
                process(tmp);

                cur = cur->next;
            }

            #pragma omp taskwait
        }
    }

    return 0;
}