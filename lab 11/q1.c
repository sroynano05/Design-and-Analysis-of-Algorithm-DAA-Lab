#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 1e9

// Adjacency List Node
typedef struct EdgeNode {
    int to;
    int weight; // 0 or 1
    struct EdgeNode* next;
} EdgeNode;

// Graph Structure
typedef struct {
    int numVertices;
    EdgeNode** head;
} Graph;

// Create a new graph
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = V;
    graph->head = (EdgeNode**)malloc(V * sizeof(EdgeNode*));
    for (int i = 0; i < V; i++) {
        graph->head[i] = NULL;
    }
    return graph;
}

// Add directed edge (u -> v) with weight w
void addEdge(Graph* graph, int u, int v, int w) {
    EdgeNode* newNode = (EdgeNode*)malloc(sizeof(EdgeNode));
    newNode->to = v;
    newNode->weight = w;
    newNode->next = graph->head[u];
    graph->head[u] = newNode;
}

// State representation in Expanded Graph G'
typedef struct {
    int u;      // Original vertex
    int parity; // 0 for even, 1 for odd
} State;

// Double-Ended Queue (Deque) for 0-1 BFS
typedef struct {
    State* data;
    int front;
    int rear;
    int capacity;
} Deque;

Deque* createDeque(int capacity) {
    Deque* dq = (Deque*)malloc(sizeof(Deque));
    dq->capacity = capacity;
    dq->data = (State*)malloc(capacity * sizeof(State));
    dq->front = capacity / 2;
    dq->rear = capacity / 2;
    return dq;
}

bool isEmpty(Deque* dq) {
    return dq->front == dq->rear;
}

void pushFront(Deque* dq, State s) {
    dq->front--;
    dq->data[dq->front] = s;
}

void pushBack(Deque* dq, State s) {
    dq->data[dq->rear] = s;
    dq->rear++;
}

State popFront(Deque* dq) {
    State s = dq->data[dq->front];
    dq->front++;
    return s;
}

// 0-1 BFS Function
void solveShortestPath(Graph* graph, int S, int C) {
    int V = graph->numVertices;
    
    // dist[u][0]: min weight sum to reach u with EVEN count of 1s
    // dist[u][1]: min weight sum to reach u with ODD count of 1s
    int dist[V][2];
    for (int i = 0; i < V; i++) {
        dist[i][0] = INF;
        dist[i][1] = INF;
    }

    // Capacity reserved for 4 * V state pushes max
    Deque* dq = createDeque(4 * V + 10);

    // Source starts at state (S, 0) with distance 0
    dist[S][0] = 0;
    pushBack(dq, (State){S, 0});

    while (!isEmpty(dq)) {
        State curr = popFront(dq);
        int u = curr.u;
        int p = curr.parity;

        EdgeNode* edge = graph->head[u];
        while (edge != NULL) {
            int v = edge->to;
            int w = edge->weight;
            int next_p = p ^ w; // 0-weight retains parity, 1-weight flips parity

            if (dist[v][next_p] > dist[u][p] + w) {
                dist[v][next_p] = dist[u][p] + w;
                
                if (w == 0) {
                    pushFront(dq, (State){v, next_p}); // Weight 0 edge -> push front
                } else {
                    pushBack(dq, (State){v, next_p});  // Weight 1 edge -> push back
                }
            }
            edge = edge->next;
        }
    }

    // Display Results
    printf("--- Minimum Cost from Source Node %d ---\n", S);
    for (int v = 0; v < V; v++) {
        int evenCost = (dist[v][0] == INF) ? INF : dist[v][0];
        int oddCost = (dist[v][1] == INF) ? INF : (dist[v][1] + C);

        int minCost = (evenCost < oddCost) ? evenCost : oddCost;

        if (minCost == INF) {
            printf("Vertex %d: Unreachable\n", v);
        } else {
            printf("Vertex %d: %d\n", v, minCost);
        }
    }

    free(dq->data);
    free(dq);
}

// Driver Code
int main() {
    int V = 5; // Number of vertices: 0, 1, 2, 3, 4
    Graph* graph = createGraph(V);
    int C = 5; // Penalty cost for odd weight-1 edges

    // Add Directed Edges (u, v, weight)
    addEdge(graph, 0, 1, 1);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 0, 3, 0);
    addEdge(graph, 3, 2, 1);
    addEdge(graph, 2, 4, 0);

    int source = 0;
    solveShortestPath(graph, source, C);

    return 0;
}