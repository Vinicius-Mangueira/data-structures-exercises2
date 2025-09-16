/*6. Implemente o método buscar(valor) que retorna True se o valor estiver na árvore e False caso contrário.*/
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
    if (queue->front == -1) {
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
int searchNode(Node* root, int data) {
    if (root == NULL) {
        return 0; // Not found
    }
    if (root->data == data) {
        return 1; // Found
    }
    if (data < root->data) {
        return searchNode(root->left, data);
    } else {
        return searchNode(root->right, data);
    }
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

