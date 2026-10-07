#include <stdio.h>
#include <limits.h>

#define V 5
#define INF INT_MAX

// Find the vertex with the minimum distance
// that has not been visited yet.
int minDistance(int dist[], int visited[])
{
    int min = INF;
    int minIndex = -1;

    for (int i = 0; i < V; i++)
    {
        if (!visited[i] && dist[i] < min)
        {
            min = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}

// Print the shortest path recursively
void printPath(int parent[], int vertex)
{
    if (parent[vertex] == -1)
    {
        printf("%c", 'A' + vertex);
        return;
    }

    printPath(parent, parent[vertex]);
    printf(" -> %c", 'A' + vertex);
}

// Dijkstra's algorithm
void dijkstra(int graph[V][V], int start, int end)
{
    int dist[V];
    int visited[V];
    int parent[V];

    // Initialize arrays
    for (int i = 0; i < V; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    // Distance from start to itself is 0
    dist[start] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, visited);

        // No more reachable vertices
        if (u == -1)
            break;

        visited[u] = 1;

        // Update distances of neighboring vertices
        for (int v = 0; v < V; v++)
        {
            if (!visited[v] &&
                graph[u][v] != 0 &&
                dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    // No path exists
    if (dist[end] == INF)
    {
        printf("No path exists.\n");
        return;
    }

    printf("Shortest distance: %d\n", dist[end]);

    printf("Shortest path: ");
    printPath(parent, end);
    printf("\n");
}

int main()
{
    /*
        Graph:

             4
        A -------- B
        |          | \
       2|         1|  \5
        |          |   \
        C ---------     D
         \ 8            | \
          \              | 2
           \10           |  \
            E <-----------
    */

    int graph[V][V] =
    {
        // A  B  C  D  E
        { 0, 4, 2, 0, 0 }, // A
        { 4, 0, 1, 5, 0 }, // B
        { 2, 1, 0, 8, 10}, // C
        { 0, 5, 8, 0, 2 }, // D
        { 0, 0, 10, 2, 0 }  // E
    };

    // Find shortest path from A to E
    dijkstra(graph, 0, 4);

    return 0;
}

