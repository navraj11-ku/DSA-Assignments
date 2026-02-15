#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char data[MAX];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return (s->top == -1);
}

int isFull(Stack *s) {
    return (s->top == MAX - 1);
}

void push(Stack *s, char value) {
    if (!isFull(s)) {
        s->data[++(s->top)] = value;
    }
}

char pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return '\0';
}

int isMatchingPair(char open, char close) {
    if (open == '(' && close == ')') return 1;
    if (open == '{' && close == '}') return 1;
    if (open == '[' && close == ']') return 1;
    return 0;
}

int isBalanced(char expression[]) {
    Stack s;
    initStack(&s);

    for (int i = 0; i < strlen(expression); i++) {
        char ch = expression[i];

        if (ch == '(' || ch == '{' || ch == '[') {
            push(&s, ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']') {

            if (isEmpty(&s)) {
                return 0;
            }

            char top = pop(&s);

            if (!isMatchingPair(top, ch)) {
                return 0;
            }
        }
    }

    return isEmpty(&s);
}

int main() {

    char *expressions[] = {
        "a + (b - c) * (d)",
        "m + [a - b * (c + d * {m})]",
        "a + (b - c)"
    };

    int n = 3;

    printf("Checking Balanced Parentheses:\n\n");

    for (int i = 0; i < n; i++) {

        printf("Expression: %s\n", expressions[i]);

        if (isBalanced(expressions[i])) {
            printf("Result: Balanced\n\n");
        } else {
            printf("Result: Not Balanced\n\n");
        }
    }

    return 0;
}