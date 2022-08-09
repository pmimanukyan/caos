#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
    
struct Node {
    int val;
    struct Node* next;
};

void fprint7(FILE *f, int64_t number) {
    if (number == 0) {
        fputc('0', f);
        return;
    }
    int isnegative = 0;
    if (number < 0) {
        isnegative = 1;
    }

    struct Node* head = NULL;
    while (number != 0) {
        struct Node* n = calloc(1, sizeof(*n));
        if (n == NULL) {
            while (head != NULL) {
                struct Node* head_copy = head;
                head = head->next;
                free(head_copy);
            }
            return;
        }
        int digit = number % 7;
        if (digit < 0) {
            digit *= -1;
        }
        n->val = digit;
        number /= 7;
        if (head == NULL) {
            head = n;
            continue;
        }
        struct Node *tmp = head;
        head = n;
        head->next = tmp;
    }

    if (isnegative) {
        fputc('-', f);
    }
    while (head != NULL) {
        fprintf(f, "%d", head->val);
        struct Node* head_copy = head;
        head = head->next;
        free(head_copy);
    }
}


// fprint7(stdout, -42) prints -60;
// fprint7(stdout, 0) prints 0;
// fprint7(stdout, 49) prints 100.