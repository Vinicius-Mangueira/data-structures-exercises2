/*7. Implemente os métodos de percurso: pre_ordem(), em_ordem(), pos_ordem().*/
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
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;
typedef struct Tree {
    Node* root;
} Tree;
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
Tree* createTree() {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}
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

void preOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}
void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}
Node* insertNode(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else {
        root->right = insertNode(root->right, data);
    }
    return root;
}
int main() {
    Tree* tree = createTree();
    int valuesToInsert[] = {45, 20, 60, 15, 25, 50, 70, 65, 80};
    int n = sizeof(valuesToInsert) / sizeof(valuesToInsert[0]);
    for (int i = 0; i < n; i++) {
        tree->root = insertNode(tree->root, valuesToInsert[i]);
    }
    printf("Pre-order traversal: ");
    preOrder(tree->root);
    printf("\nIn-order traversal: ");
    inOrder(tree->root);
    printf("\nPost-order traversal: ");
    postOrder(tree->root);
    printf("\n");
    return 0;
}

