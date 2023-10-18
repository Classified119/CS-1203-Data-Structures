#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node *left;
    struct node *right;
    int height;
};

// Function to get the height of a node
int getHeight(struct node *n) {
    if (n == NULL)
        return 0;
    return n->height;
}

// Function to create a new node
struct node *createNode(int key) {
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Function to find the maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to get the balance factor of a node
int getBalanceFactor(struct node *n) {
    if (n == NULL) {
        return 0;
    }
    return getHeight(n->left) - getHeight(n->right);
}

// Function to perform a right rotation
struct node *rightRotate(struct node *y) {
    struct node *x = y->left;
    struct node *T2 = x->right;
    x->right = y;
    y->left = T2;
    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
    return x;
}

// Function to perform a left rotation
struct node *leftRotate(struct node *x) {
    struct node *y = x->right;
    struct node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
    return y;
}

// Function to insert a node into the AVL tree
struct node *insert(struct node *node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int bf = getBalanceFactor(node);

    // Left Left Case
    if (bf > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (bf < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (bf > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (bf < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to find the node with the minimum key value in the tree
struct node *minValueNode(struct node *node) {
    struct node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node with the given key from the AVL tree
struct node *deleteNode(struct node *root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct node *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            struct node *temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bf = getBalanceFactor(root);

    // Left Left Case
    if (bf > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (bf > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (bf < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (bf < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to perform a preorder traversal
void preOrder(struct node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Function to perform an inorder traversal
void inOrder(struct node *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

// Function to display the AVL tree's structure
void displayTree(struct node *root, int level) {
    if (root != NULL) {
        displayTree(root->right, level + 1);
        printf("\n");
        if (root == root->right)
            printf("Root -> ");
        for (int i = 0; i < level && root != root->right; i++)
            printf("        ");
        printf("%d", root->key);
        displayTree(root->left, level + 1);
    }
}

int main() {
    struct node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 60);
    root = insert(root, 70);
    root = insert(root, 80);
    root = insert(root, 90);

    printf("Preorder Traversal: ");
    preOrder(root);
    printf("\n");

    printf("Inorder Traversal: ");
    inOrder(root);
    printf("\n");

    printf("Displaying Tree Structure:\n");
    displayTree(root, 10);

    printf("\n\n");

    // Deleting nodes
    root = deleteNode(root, 20);
    root = deleteNode(root, 40);
    root = deleteNode(root, 70);

    printf("Preorder Traversal after deletion: ");
    preOrder(root);
    printf("\n");

    printf("Inorder Traversal after deletion: ");
    inOrder(root);
    printf("\n");

    printf("Displaying Tree Structure after deletion:\n");
    displayTree(root, 10);

    return 0;
}