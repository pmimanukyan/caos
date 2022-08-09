#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node *left;
    struct Node *right;
};

struct Node* create_node(int val) {
    struct Node *n = calloc(1, sizeof(*n));
    if (n == NULL) {
        return NULL;
    }
    n->val = val;
    n->left = NULL;
    n->right = NULL;
    return n;
}

struct Node* insert(struct Node *node, int val) {
    if (node == NULL) {
        return create_node(val);
    }
    if (val > node->val) {
        node->left = insert(node->left, val);
    } else if (val < node->val) {
        node->right = insert(node->right, val);
    }
    return node;
}

void print(struct Node *root) {
    if (root != NULL) {
        print(root->left);
        printf("%d ", root->val);
        print(root->right);
    }
}

void delete_tree(struct Node* root) {
    if (root == NULL) {
        return;
    }
    delete_tree(root->left);
    delete_tree(root->right);
    free(root);
}

int main() {
    struct Node* root = NULL;
    int number;
    int res;
    while ((res = scanf("%d", &number)) == 1) {
        if (number == 0) {
            print(root);
            delete_tree(root);
            root = NULL;
            printf("%d ", 0);
            continue;
        }
        if (root == NULL) {
            root = insert(root, number);
            if (root == NULL) {
                return 1;
            }
            continue;
        }
        struct Node *tmp = insert(root, number);
        if (tmp == NULL) {
            delete_tree(root);
            return 1;
        }
    }
    if (res != EOF) {
        return 1;
    }
    if (root != NULL) {
        print(root);
        delete_tree(root);
        root = NULL;
        printf("%d ", 0);
    }
    printf("\n");
}


// Input
// 3 5 1 0 2 0

// Output
// 5 3 1 0 2 0