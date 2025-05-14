#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

void printLeafNodes(struct Node* root) {
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->data);
        return;
    }
    printLeafNodes(root->left);
    printLeafNodes(root->right);
}

int main() {
    struct Node* root = newNode(30);
    root->left = newNode(20);
    root->right = newNode(40);
    root->left->left = newNode(5);
    root->left->right = newNode(15);

    printf("Leaf nodes: ");
    printLeafNodes(root);
    printf("\n");
    return 0;
}