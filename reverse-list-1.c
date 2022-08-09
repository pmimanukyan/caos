#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node *next;
};

struct Node* reverseList(struct Node* head) {
    struct Node *prev = NULL;
    while (head != NULL) {
        struct Node *next_ = head->next;
        head->next = prev;
        prev = head;
        head = next_;
    }
    return prev;
}

void deleting_nodes(struct Node* head) {
    while(head != NULL) {
        struct Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    struct Node *n = NULL;
    struct Node *cur = NULL;
    struct Node *head = NULL;

    int number;
    int f = 0;
    int res;
    while ((res = scanf("%d", &number)) == 1) {
        n = calloc(1, sizeof(*n));
        if (n == NULL) {
            return 1;
        }
        n->val = number;
        if (head == NULL) {
            f = 1;

            head = n;
            cur = n;
            continue;
        }

        n->val = number;
        cur->next = n;
        cur = cur->next;
    }
    if (res != EOF) {
        return -1;
    }
    if (f == 1) {
        cur->next = NULL;
    }
    struct Node* new_head = reverseList(head);
    struct Node* head_for_deleting = new_head;
    while (new_head != NULL) {
        printf("%d\n", new_head->val);
        new_head = new_head->next;
    }

    deleting_nodes(head_for_deleting);
}