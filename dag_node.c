#include <stdlib.h>

struct dag_node {
    struct dag_node *left, *right;
    void *data;
};

void dfs(struct dag_node* node, int *b) {
    if (node == NULL) {
        return;
    }
    node->data = (void*) b;
    if (node->left && node->left->data == (void*) b) {
        node->left = NULL;
    }
    dfs(node->left, b);
    if (node->right && node->right->data == (void*) b) {
        node->right = NULL;
    }
    dfs(node->right, b);
}

void binary_tree_clean(struct dag_node *node) {
    if (node == NULL) {
        return;
    }
    binary_tree_clean(node->left);
    binary_tree_clean(node->right);
    free(node);
}

void free_dag(struct dag_node *root) {
    int a;
    int *b = &a;
    dfs(root, b);
    binary_tree_clean(root);
}