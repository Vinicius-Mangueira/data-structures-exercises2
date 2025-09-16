/*1. Construa a árvore binária de busca resultante após a inserção dos valores na ordem:
45,20,60,15,25,50,70,65,80. Em seguida, mostre a árvore após a remoção do nó 60.
*/

#include <stdio.h>
#include <stdlib.h>

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

Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* removeNode(Node* root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = removeNode(root->left, data);
    } else if (data > root->data) {
        root->right = removeNode(root->right, data);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node* temp = findMin(root->right);
        root->data = temp->data; // Copy the inorder successor's content to this node
        root->right = removeNode(root->right, temp->data); // Delete the inorder successor
    }
    return root;
}
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}
int main() {
    Tree* tree = createTree();
    int valuesToInsert[] = {45, 20, 60, 15, 25, 50, 70, 65, 80};
    int n = sizeof(valuesToInsert) / sizeof(valuesToInsert[0]);

    for (int i = 0; i < n; i++) {
        tree->root = insertNode(tree->root, valuesToInsert[i]);
    }

    printf("Inorder traversal of the tree after insertion:\n");
    inorderTraversal(tree->root);
    printf("\n");

    tree->root = removeNode(tree->root, 60);

    printf("Inorder traversal of the tree after removing 60:\n");
    inorderTraversal(tree->root);
    printf("\n");

    return 0;
}