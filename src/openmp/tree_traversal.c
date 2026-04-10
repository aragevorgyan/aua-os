#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
    sleep(1);  // simulate work
    printf("Processed node %d\n", n->value);
}

void traverse_preorder(Node* root) {
    if (root == NULL) return;

    process(root);                // Root
    traverse_preorder(root->left);   // Left
    traverse_preorder(root->right);  // Right
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

    traverse_preorder(root);

    return 0;
}