#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    int k;
    struct Node *next;
    struct Node *prev;
};

void deleting_nodes(struct Node* head) {
    while(head != NULL) {
        struct Node *tmp = head;
        head = head->prev;
        free(tmp);
    }
}

int main() {
    struct Node *head = NULL;
    int number;
    int res;
    while ((res = scanf("%d", &number)) == 1) {
        struct Node *iter = head;
        while (iter != NULL) {
            if (iter->val == number) {
                ++iter->k;
                if (iter != head) {
                    struct Node *tmp = iter->prev;
                    struct Node *tmp2 = iter->next;
                    iter->next = head;
                    head->prev = iter;
                    tmp->next = tmp2;
                    if (tmp2 != NULL) {
                        tmp2->prev = tmp;
                    }
                    head = iter;
                    head->prev = NULL;
                }
                break;
            }
            iter = iter->next;
        }
        if (iter == NULL) {
            struct Node *new_node = calloc(1, sizeof(*new_node));
            if (new_node == NULL) {
                return 1;
            }
            new_node->val = number;
            new_node->k = 1;
            struct Node *tmp = head;
            head = new_node;
            head->next = tmp;
            if(tmp != NULL) {
                tmp->prev = head;
            }
        }
    }
    if (res != EOF) {
        return 1;
    }
    struct Node* curr = NULL;
    while (head != NULL) {
        curr = head;
        head = head->next;
    }

    struct Node* head_for_deleting = curr;
    while (curr != NULL) {
        printf("%d %d\n", curr->val, curr->k);
        curr = curr->prev;
    }

    deleting_nodes(head_for_deleting);
}


// Input
// 1 2 3 2 1

// Output
// 3 1
// 2 2
// 1 2