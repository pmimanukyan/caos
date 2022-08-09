#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef double (*funcptr_t)(double);

struct FunctionTable {
    char *name;
    funcptr_t func;
    struct FunctionTable *next;
};

struct FunctionTable *add_func(struct FunctionTable *head, char *name, funcptr_t func) {
    struct FunctionTable *cur = calloc(1, sizeof(*cur));
    if (!cur) {
        return NULL;
    }

    cur->func = func;
    cur->name = name;
    cur->next = head;
    return cur;
}

int main() {
    double x;
    struct FunctionTable *head = NULL;

    head = add_func(head, "sin", sin);
    head = add_func(head, "cos", cos);
    head = add_func(head, "exp", exp);
    head = add_func(head, "log", log);
    head = add_func(head, "tan", tan);
    head = add_func(head, "sqrt", sqrt);

    int res;
    char *name = NULL;
    while ((res = scanf("%ms%lf", &name, &x)) == 2) {
        struct FunctionTable *cur = head;
        while (cur != NULL && strcmp(name, cur->name) != 0) {
            cur = cur->next;
        }
        free(name);

        if (!cur) {
            printf("%f\n", NAN);
        } else {
            printf("%a\n", cur->func(x));
        }
    }

    while (head != NULL) {
        struct FunctionTable *next = head->next;
        free(head);
        head = next;
    }

    if (res != EOF) {
        return 1;
    }
}