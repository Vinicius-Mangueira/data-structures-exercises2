/* 4. Considere o grafo não direcionado representado pela lista de adjacência:
A: B, C
B: A, D, E
C: A, F
D: B
E: B, F
F: C, E
Construa a matriz de adjacência e a ordem de percurso dos vértices (em ordem alfabética) usando: (a) Busca em
Largura (BFS) iniciando em A e (b) Busca em Profundidade (DFS) iniciando em A.*/

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#define MAX 6
#define QUEUE_SIZE 100
#define STACK_SIZE 100
#define ALPHABET_SIZE 26
#define VERTEX_COUNT 6
#define INDEX(c) ((c) - 'A')
typedef struct Graph {
    int adjMatrix[MAX][MAX];
    char vertices[MAX];
    int vertexCount;
} Graph;
typedef struct Queue {
    int items[QUEUE_SIZE];
    int front;
    int rear;
} Queue;
typedef struct Stack {
    int items[STACK_SIZE];
    int top;
} Stack;
Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertexCount = 0;
    memset(graph->adjMatrix, 0, sizeof(graph->adjMatrix));
    return graph;
}
void addVertex(Graph* graph, char vertex) {
    graph->vertices[graph->vertexCount++] = vertex;
}
void addEdge(Graph* graph, char src, char dest) {
    int srcIndex = INDEX(src);
    int destIndex = INDEX(dest);
    graph->adjMatrix[srcIndex][destIndex] = 1;
    graph->adjMatrix[destIndex][srcIndex] = 1; // Undirected graph
}
void printAdjMatrix(Graph* graph) {
    printf("Matriz de Adjacência:\n  ");
    for (int i = 0; i < graph->vertexCount; i++) {
        printf("%c ", graph->vertices[i]);
    }
    printf("\n");
    for (int i = 0; i < graph->vertexCount; i++) {
        printf("%c ", graph->vertices[i]);
        for (int j = 0; j < graph->vertexCount; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}
int isQueueEmpty(Queue* queue) {
    return queue->front == -1;
}
void enqueue(Queue* queue, int value) {
    if (queue->rear == QUEUE_SIZE - 1) {
        printf("Queue is full\n");
        return;
    }
    if (isQueueEmpty(queue)) {
        queue->front = 0;
    }
    queue->items[++queue->rear] = value;
}
int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = queue->items[queue->front];
    if (queue->front >= queue->rear) {
        queue->front = queue->rear = -1; // Reset queue
    } else {
        queue->front++;
    }
    return item;
}
void bfs(Graph* graph, char startVertex) {
    int visited[MAX] = {0};
    Queue* queue = createQueue();
    int startIndex = INDEX(startVertex);
    visited[startIndex] = 1;
    enqueue(queue, startIndex);
    printf("BFS starting from vertex %c: ", startVertex);
    while (!isQueueEmpty(queue)) {
        int currentIndex = dequeue(queue);
        printf("%c ", graph->vertices[currentIndex]);
        for (int i = 0; i < graph->vertexCount; i++) {
            if (graph->adjMatrix[currentIndex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(queue, i);
            }
        }
    }
    printf("\n");
    free(queue);
}
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}
int isStackEmpty(Stack* stack) {
    return stack->top == -1;
}
void push(Stack* stack, int value) {
    if (stack->top == STACK_SIZE - 1) {
        printf("Stack is full\n");
        return;
    }
    stack->items[++stack->top] = value;
}

int pop(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->items[stack->top--];
}
void dfs(Graph* graph, char startVertex) {
    int visited[MAX] = {0};
    Stack* stack = createStack();
    int startIndex = INDEX(startVertex);
    push(stack, startIndex);
    printf("DFS starting from vertex %c: ", startVertex);
    while (!isStackEmpty(stack)) {
        int currentIndex = pop(stack);
        if (!visited[currentIndex]) {
            visited[currentIndex] = 1;
            printf("%c ", graph->vertices[currentIndex]);
            for (int i = graph->vertexCount - 1; i >= 0; i--) {
                if (graph->adjMatrix[currentIndex][i] == 1 && !visited[i]) {
                    push(stack, i);
                }
            }
        }
    }
    printf("\n");
    free(stack);
}
int main() {
    Graph* graph = createGraph();
    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    for (int i = 0; i < VERTEX_COUNT; i++) {
        addVertex(graph, vertices[i]);
    }
    addEdge(graph, 'A', 'B');
    addEdge(graph, 'A', 'C');
    addEdge(graph, 'B', 'D');
    addEdge(graph, 'B', 'E');
    addEdge(graph, 'C', 'F');
    addEdge(graph, 'E', 'F');
    printAdjMatrix(graph);
    bfs(graph, 'A');
    dfs(graph, 'A');
    free(graph);
    return 0;
}
