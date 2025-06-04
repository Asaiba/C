#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Manhattan Distance
int manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Diagonal Distance
int diagonal(int x1, int y1, int x2, int y2) {
    return (abs(x1 - x2) > abs(y1 - y2)) ? abs(x1 - x2) : abs(y1 - y2);
}

// Euclidean Distance
double euclidean(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main() {
    // Sample coordinates
    int x1 = 0, y1 = 0;
    int x2 = 3, y2 = 4;

    // Calculate distances
    int m_dist = manhattan(x1, y1, x2, y2);
    int d_dist = diagonal(x1, y1, x2, y2);
    double e_dist = euclidean(x1, y1, x2, y2);

    // Print results
    printf("Manhattan Distance: %d\n", m_dist);
    printf("Diagonal Distance: %d\n", d_dist);
    printf("Euclidean Distance: %.2f\n", e_dist);

    return 0;
}
