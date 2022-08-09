#include <stdio.h>
#include <stdlib.h>

struct data {
    int (*get_rank)(const struct data*);
    char secret[];
};

void rank_sort(struct data* elements[], size_t size) {
    int no_swap;
    for (int i = size - 1; i >= 0; i--) {
        no_swap = 1;
        for (int j = 0; j < i; j++){
            if (elements[j]->get_rank(elements[j]) > elements[j + 1]->get_rank(elements[j + 1])) {
                struct data* tmp = elements[j];
                elements[j] = elements[j + 1];
                elements[j + 1] = tmp;
                no_swap = 0;
            }
        }
        if (no_swap == 1) {
            break;
        }
    }
}