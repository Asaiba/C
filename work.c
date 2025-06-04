#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 5
#define MAX_OPEN 100

typedef struct {
    int x, y;
    int g, h, f;
    int walkable;
    int parent_x, parent_y;
    int closed;
    int in_open;
} Node;

typedef enum { MANHATTAN = 1, EUCLIDEAN, DIAGONAL } HeuristicType;
HeuristicType heuristicType;

Node grid[SIZE][SIZE];
Node* openList[MAX_OPEN];
int openCount = 0;
int visitedNodes = 0;

// Directions: up, down, left, right
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

void initializeGrid() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = (Node){i, j, 0, 0, 0, 1, -1, -1, 0, 0};
        }
    }

    // Set blocked cells
    grid[1][1].walkable = 0;
    grid[2][2].walkable = 0;
    grid[3][3].walkable = 0;
}

int heuristic(int x1, int y1, int x2, int y2) {
    int dx = abs(x1 - x2), dy = abs(y1 - y2);
    switch (heuristicType) {
        case MANHATTAN:
            return (dx + dy) * 10;
        case EUCLIDEAN:
            return (int)(sqrt(dx * dx + dy * dy) * 10);
        case DIAGONAL:
            return 10 * (dx + dy) + (14 - 2 * 10) * (dx < dy ? dx : dy);
        default:
            return 0;
    }
}

int isValid(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE && grid[x][y].walkable;
}

Node* getLowestFNode() {
    int minIndex = 0;
    for (int i = 1; i < openCount; i++) {
        if (openList[i]->f < openList[minIndex]->f)
            minIndex = i;
    }
    Node* lowest = openList[minIndex];
    for (int i = minIndex; i < openCount - 1; i++)
        openList[i] = openList[i + 1];
    openCount--;
    return lowest;
}

void reconstructPath(int endX, int endY) {
    int path[SIZE * SIZE][2];
    int length = 0;
    int x = endX, y = endY;

    while (x != -1 && y != -1) {
        path[length][0] = x;
        path[length][1] = y;
        int px = grid[x][y].parent_x;
        int py = grid[x][y].parent_y;
        x = px;
        y = py;
        length++;
    }

    printf("\nPath:\n");
    for (int i = length - 1; i >= 0; i--) {
        printf("(%d,%d)", path[i][0], path[i][1]);
        if (i > 0) printf(" -> ");
    }

    printf("\n\nTotal Cost: %d\n", length - 1);
    printf("Nodes Visited: %d\n", visitedNodes);
}

void aStar(int startX, int startY, int endX, int endY) {
    Node* start = &grid[startX][startY];
    start->g = 0;
    start->h = heuristic(startX, startY, endX, endY);
    start->f = start->g + start->h;
    start->in_open = 1;

    openList[openCount++] = start;

    while (openCount > 0) {
        Node* current = getLowestFNode();
        current->closed = 1;
        visitedNodes++;

        if (current->x == endX && current->y == endY) {
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = current->x + dir[i][0];
            int ny = current->y + dir[i][1];

            if (!isValid(nx, ny))
                continue;

            Node* neighbor = &grid[nx][ny];

            if (neighbor->closed)
                continue;

            int tentative_g = current->g + 10;

            if (!neighbor->in_open || tentative_g < neighbor->g) {
                neighbor->g = tentative_g;
                neighbor->h = heuristic(nx, ny, endX, endY);
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent_x = current->x;
                neighbor->parent_y = current->y;

                if (!neighbor->in_open) {
                    openList[openCount++] = neighbor;
                    neighbor->in_open = 1;
                }
            }
        }
    }

    printf("No path found.\n");
}

void promptHeuristicSelection() {
    int choice;
    printf("Select a heuristic:\n");
    printf("1. Manhattan\n");
    printf("2. Euclidean\n");
    printf("3. Diagonal\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: heuristicType = MANHATTAN; break;
        case 2: heuristicType = EUCLIDEAN; break;
        case 3: heuristicType = DIAGONAL; break;
        default:
            printf("Invalid input. Defaulting to Manhattan.\n");
            heuristicType = MANHATTAN;
    }
}

int main() {
    initializeGrid();
    promptHeuristicSelection();

    printf("\nStart: (0,0)\nGoal: (4,4)\nBlocked: (1,1), (2,2), (3,3)\n");

    printf("Using Heuristic: ");
    switch (heuristicType) {
        case MANHATTAN: printf("Manhattan\n"); break;
        case EUCLIDEAN: printf("Euclidean\n"); break;
        case DIAGONAL:  printf("Diagonal\n");  break;
        default:        printf("Unknown\n");
    }

    aStar(0, 0, 4, 4);
    reconstructPath(4, 4);

    return 0;
}
