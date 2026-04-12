#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(int value) {
    Node* n = malloc(sizeof(Node));
    n->value = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void process(Node* n) {
    sleep(1);  // simulate heavy work
    printf("Processed node %d by thread %d\n",
           n->value, omp_get_thread_num());
}

void traverse_task(Node* root) {
    if (root == NULL) return;
    //#pragma omp task
    process(root);

    #pragma omp task
    traverse_task(root->left);

    #pragma omp task
    traverse_task(root->right);

    #pragma omp taskwait
}

int main() {
    /*
            1
           / \
          2   3
         / \ / \
        4  5 6  7
    */

    Node* root = create_node(1);
    root->left = create_node(2);
    root->right = create_node(3);
    root->left->left = create_node(4);
    root->left->right = create_node(5);
    root->right->left = create_node(6);
    root->right->right = create_node(7);

    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        {
            traverse_task(root);
        }
    }

    return 0;
}