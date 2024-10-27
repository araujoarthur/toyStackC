/*
This program implements a simple integer stack.
*/

#include <stdlib.h>
#include <stdio.h>

#define CAPACITY_FACTOR 4

typedef struct {
    int **data; // It is in fact a dynamic array of integer pointers.
    int top;
    unsigned int cap;
} stack;

/*
Creates the stack.
*/
stack* createStack() {
    stack* s = malloc(sizeof(stack));
    if (s == NULL) {
        fprintf(stderr, "failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    s->top = -1;
    s->cap = CAPACITY_FACTOR; // initial capacity
    s->data = malloc(s->cap * sizeof(int*));
    if (s->data == NULL) {
        fprintf(stderr, "failed to allocate inner memory\n");
        exit(EXIT_FAILURE);   
    } 

    return s;
}

/*
Inserts an item into the top of the stack.
*/
void push(stack* s, int i) {
    if (s->top == s->cap) { // The stack is at its limit, we need to reallocate
        s->cap += CAPACITY_FACTOR;
        s->data = realloc(s->data, s->cap * sizeof(int*));
        if (s->data == NULL) {
            fprintf(stderr, "failed to reallocate inner memory\n");
            exit(EXIT_FAILURE);        
        }
    }

    // Creates a pointer to store the given int
    int *ptr = malloc(sizeof(int));
    if (ptr == NULL) {
        fprintf(stderr, "failed to allocate item memory\n");
        exit(EXIT_FAILURE);          
    }
    *ptr = i;

    s->data[++s->top] = ptr;
}


/*
Retrieves the item at the top of the stack.
*/
int pop(stack* s) {
    if (s->top == -1) {
        fprintf(stderr, "stack is empty, nothing to pop");
        exit(EXIT_FAILURE);
    }

    int *ptr = s->data[s->top--];
    int val = *ptr;
    free(ptr);
    return val;
}


void main()
{
    stack stck = *createStack();
    push(&stck, 2);
    push(&stck, 3);
    push(&stck, 4);
    push(&stck, 5);
    push(&stck, 10);
    push(&stck, 15);
    push(&stck, 20);
    push(&stck, 40);
    push(&stck, 80);
    int popped = pop(&stck);
    printf("Popped value: %d\n", popped);

    popped = pop(&stck);
    printf("Popped value: %d\n", popped);

    popped = pop(&stck);
    printf("Popped value: %d\n", popped);
}