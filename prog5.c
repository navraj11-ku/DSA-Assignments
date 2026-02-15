#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int adj[MAX][MAX];
int visited[MAX];
int n;

void addEdge(int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1;
}

void bfs(int start) {
    int queue[MAX], front = 0, rear = 0;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        for (int i = 0; i < n; i++) {
            if (adj[current][i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
}

void dfs(int start) {
    printf("%d ", start);
    visited[start] = 1;

    for (int i = 0; i < n; i++) {
        if (adj[start][i] == 1 && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    n = 5;

    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            adj[i][j] = 0;

    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(1, 4);

    printf("BFS Traversal starting from vertex 0:\n");
    bfs(0);

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    printf("\n\nDFS Traversal starting from vertex 0:\n");
    dfs(0);

    return 0;
}