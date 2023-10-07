#include <stdio.h>
#include <stdlib.h>

// Defining the binary tree root node
struct RtNd {
    int val;
    struct RtNd* left;
    struct RtNd* right;
};

// Structure to represent a stack node
struct StckNd {
    struct RtNd* data;
    struct StckNd* next;
};

// representation of stack
struct Stack {
    struct StckNd* top;
};

// creating a new stack node
struct StckNd* createStckNd(struct RtNd* RtNd) {
    struct StckNd* StckNd = (struct StckNd*)malloc(sizeof(struct StckNd));
    StckNd->data = RtNd;
    StckNd->next = NULL;
    return StckNd;
}

// creating an empty stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// Fn to push a node onto the stack
void push(struct Stack* stack, struct RtNd* RtNd) {
    struct StckNd* StckNd = createStckNd(RtNd);
    StckNd->next = stack->top;
    stack->top = StckNd;
}

// Fn to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return (stack->top == NULL);
}

// pop a node from the stack and place it in empty stack
struct RtNd* pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    struct StckNd* StckNd = stack->top;
    stack->top = stack->top->next;
    struct RtNd* RtNd = StckNd->data;
    free(StckNd);
    return RtNd;
}

// Fn for inorder traversal without recursion
void Inorder(struct RtNd* root) {
    struct Stack* stack = createStack();
    struct RtNd* currentNode = root;

    while (currentNode != NULL || !isEmpty(stack)) {
        while (currentNode != NULL) {
            push(stack, currentNode);
            currentNode = currentNode->left;
        }

        currentNode = pop(stack);
        printf("%d ", currentNode->val);
        currentNode = currentNode->right;
    }

    free(stack);
}

// test
int main() {
    // Random Binary tree w small numbers for ease
    struct RtNd* root = (struct RtNd*)malloc(sizeof(struct RtNd));
    root->val = 1;
    root->left = (struct RtNd*)malloc(sizeof(struct RtNd));
    root->left->val = 2;
    root->left->left = NULL;
    root->left->right = NULL;
    root->right = (struct RtNd*)malloc(sizeof(struct RtNd));
    root->right->val = 3;
    root->right->left = NULL;
    root->right->right = NULL;

    printf("Inorder traversal without recursion: ");
    Inorder(root);
    printf("\n");

    // final
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}




