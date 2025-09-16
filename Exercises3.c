/*3. Insira os valores na ordem: 10,20,30,40,50,25
Mostre passo a passo as rotações realizadas para manter o balanceamento da árvore AVL.*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
} Node;
typedef struct Tree {
    Node* root;
} Tree;
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; // New node is initially added at leaf
    return newNode;
}
Tree* createTree() {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}
int getHeight(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}
int getBalance(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    // Perform rotation
    x->right = y;
    y->left = T2;
    // Update heights
    y->height = fmax(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = fmax(getHeight(x->left), getHeight(x->right)) + 1;
    // Return new root
    return x;
}
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    // Perform rotation
    y->left = x;
    x->right = T2;
    // Update heights
    x->height = fmax(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = fmax(getHeight(y->left), getHeight(y->right)) + 1;
    // Return new root
    return y;
}

