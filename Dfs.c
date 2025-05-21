#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Graph structure
typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
} Graph;

// Stack structure
typedef struct Stack {
    int* items;
    int top;
    int capacity;
} Stack;

// Function to create a new node
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

//  Function to create a graph
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (bool*)calloc(vertices, sizeof(bool));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// Function to add edge
void addEdge(Graph* graph, int src, int dest) {
    // Add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Since this is an undirected graph, add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function to print the graph
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjLists[v];
        printf("Vertex %d:", v);
        while (temp) {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Stack functions
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->items = (int*)malloc(capacity * sizeof(int));
    stack->capacity = capacity;
    stack->top = -1;
    return stack;
}

void push(Stack* stack, int value) {
    if (stack->top < stack->capacity - 1) {
        stack->items[++stack->top] = value;
    }
}

int pop(Stack* stack) {
    if (stack->top >= 0) {
        return stack->items[stack->top--];
    }
    return -1;
}

bool isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

// DFS Iterative function
void DFS_Iterative(Graph* graph, int startVertex) {
    Stack* stack = createStack(graph->numVertices);
    push(stack, startVertex);

    while (!isStackEmpty(stack)) {
        int currentVertex = pop(stack);

        if (!graph->visited[currentVertex]) {
            printf("Visited %d\n", currentVertex);
            graph->visited[currentVertex] = true;
        }

        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            if (!graph->visited[temp->vertex]) {
                push(stack, temp->vertex);
            }
            temp = temp->next;
        }
    }

    free(stack->items);
    free(stack);
}

// Main function
int main() {
    int vertices = 6;
    Graph* graph = createGraph(vertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);

    printf("\nGraph Adjacency List:\n");
    printGraph(graph);

    printf("\nIterative Depth-First Search starting from vertex 0:\n");
    DFS_Iterative(graph, 0);

    // Free memory
    for (int i = 0; i < vertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->adjLists);
    free(graph->visited);
    free(graph);

    return 0;
}
