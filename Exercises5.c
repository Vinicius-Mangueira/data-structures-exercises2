/*5. Implemente uma estrutura (ou classe) Node para armazenar nós de uma árvore binária de busca. Cada nó deve
armazenar valor, esquerda e direita. Implemente o método inserir(valor) para montar a árvore.*/
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
