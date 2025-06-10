#include <stdio.h>
#include <stdlib.h>

#define MAX_CHILDREN 10
#define MAX_QUEUE_SIZE 100

// Tree node structure
typedef struct Node {
    int val;
    int child_count;
    struct Node* children[MAX_CHILDREN];
} Node;

// Create a new node
Node* createNode(int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;
    node->child_count = 0;
    return node;
}

// Simple queue for BFS
typedef struct {
    Node* items[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = 0;
}

int isEmpty(Queue* q) {
    return q->front == q->rear;
}

void enqueue(Queue* q, Node* node) {
    q->items[q->rear++] = node;
}

Node* dequeue(Queue* q) {
    return q->items[q->front++];
}

// BFS function
void bfs(Node* root) {
    if (!root) return;

    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        Node* current = dequeue(&q);
        printf("%d ", current->val);

        for (int i = 0; i < current->child_count; i++) {
            enqueue(&q, current->children[i]);
        }
    }
}

int main() {
    // Create nodes 1 to 11
    Node* nodes[12];
    for (int i = 1; i <= 11; i++) {
        nodes[i] = createNode(i);
    }

    // Build the tree (based on your diagram)
    nodes[1]->children[nodes[1]->child_count++] = nodes[2];
    nodes[1]->children[nodes[1]->child_count++] = nodes[3];
    nodes[1]->children[nodes[1]->child_count++] = nodes[4];
    nodes[2]->children[nodes[2]->child_count++] = nodes[5];
    nodes[2]->children[nodes[2]->child_count++] = nodes[6];
    nodes[6]->children[nodes[6]->child_count++] = nodes[7];
    nodes[4]->children[nodes[4]->child_count++] = nodes[8];
    nodes[4]->children[nodes[4]->child_count++] = nodes[11];
    nodes[8]->children[nodes[8]->child_count++] = nodes[9];
    nodes[8]->children[nodes[8]->child_count++] = nodes[10];

    // Run BFS
    printf("BFS traversal: ");
    bfs(nodes[1]);
    printf("\n");

    return 0;
}
