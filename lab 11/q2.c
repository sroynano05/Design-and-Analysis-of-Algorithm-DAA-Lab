#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 1e9

// Adjacency List Node
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Graph Structure
typedef struct {
    int numVertices;
    Node** head;
} Graph;

// Create Graph
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = V;
    graph->head = (Node**)malloc(V * sizeof(Node*));
    for (int i = 0; i < V; i++) {
        graph->head[i] = NULL;
    }
    return graph;
}

// Add undirected edge
void addEdge(Graph* graph, int u, int v) {
    // u -> v
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = graph->head[u];
    graph->head[u] = newNode;

    // v -> u
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = u;
    newNode->next = graph->head[v];
    graph->head[v] = newNode;
}

// Queue for BFS
typedef struct {
    int* items;
    int front;
    int rear;
    int capacity;
} Queue;

Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->capacity = capacity;
    q->items = (int*)malloc(capacity * sizeof(int));
    q->front = 0;
    q->rear = 0;
    return q;
}

bool isEmpty(Queue* q) {
    return q->front == q->rear;
}

void enqueue(Queue* q, int value) {
    q->items[q->rear++] = value;
}

int dequeue(Queue* q) {
    return q->items[q->front++];
}

// Multi-Source BFS Voronoi Partitioning Function
void computeVoronoiPartitions(Graph* graph, int* hubs, int K, int R) {
    int V = graph->numVertices;
    int* dist = (int*)malloc(V * sizeof(int));
    int* owner = (int*)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        dist[i] = -1;
        owner[i] = -1;
    }

    Queue* q = createQueue(V + 10);

    // Initialize Multi-Source BFS with all hubs
    // Hubs array is 0-indexed in code, but hub indices are 1-indexed (i + 1)
    for (int i = 0; i < K; i++) {
        int h_node = hubs[i];
        dist[h_node] = 0;
        owner[h_node] = i + 1; // 1-indexed hub identity
        enqueue(q, h_node);
    }

    while (!isEmpty(q)) {
        int u = dequeue(q);

        Node* temp = graph->head[u];
        while (temp != NULL) {
            int v = temp->vertex;

            if (dist[v] == -1) {
                // Unvisited vertex
                dist[v] = dist[u] + 1;
                owner[v] = owner[u];
                enqueue(q, v);
            } else if (dist[v] == dist[u] + 1) {
                // Alternative path of same length: Apply Deterministic Tie-Breaking
                if (owner[u] < owner[v]) {
                    owner[v] = owner[u];
                }
            }
            temp = temp->next;
        }
    }

    // Apply Radius Threshold R constraint
    printf("--- Radius-Constrained Voronoi Partitioning Results (R = %d) ---\n", R);
    for (int i = 0; i < V; i++) {
        if (dist[i] == -1 || dist[i] > R) {
            owner[i] = -1; // Unassigned or outside coverage area
            printf("Vertex %d: owner = -1 (Unreachable or > R)\n", i);
        } else {
            printf("Vertex %d: owner = %d, dist = %d\n", i, owner[i], dist[i]);
        }
    }

    // Free memory
    free(dist);
    free(owner);
    free(q->items);
    free(q);
}

// Driver Code
int main() {
    int V = 6; // Vertices: 0, 1, 2, 3, 4, 5
    Graph* graph = createGraph(V);

    // Constructing an undirected graph
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);
    addEdge(graph, 1, 4);

    // Designated hubs (0-indexed vertex values) -> Hub 1 is vertex 0, Hub 2 is vertex 5
    int hubs[] = {0, 5}; 
    int K = 2;
    int R = 2; // Radius threshold

    computeVoronoiPartitions(graph, hubs, K, R);

    return 0;
}