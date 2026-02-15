#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
    int top;
    char items[MAX];
} CharStack;

typedef struct {
    int top;
    int items[MAX];
} IntStack;

void initCharStack(CharStack *s) { s->top = -1; }
void initIntStack(IntStack *s) { s->top = -1; }

int isCharEmpty(CharStack *s) { return s->top == -1; }
int isIntEmpty(IntStack *s) { return s->top == -1; }

void pushChar(CharStack *s, char c) { s->items[++s->top] = c; }
char popChar(CharStack *s) { return s->items[s->top--]; }
char peekChar(CharStack *s) { return s->items[s->top]; }

void pushInt(IntStack *s, int x) { s->items[++s->top] = x; }
int popInt(IntStack *s) { return s->items[s->top--]; }

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfix(char infix[], char postfix[]) {
    CharStack s;
    initCharStack(&s);
    int i = 0, k = 0;

    while (infix[i] != '\0') {
        if (isdigit(infix[i])) {
            postfix[k++] = infix[i];
        }
        else if (infix[i] == '(') {
            pushChar(&s, infix[i]);
        }
        else if (infix[i] == ')') {
            while (!isCharEmpty(&s) && peekChar(&s) != '(') {
                postfix[k++] = popChar(&s);
            }
            popChar(&s);
        }
        else {
            while (!isCharEmpty(&s) && precedence(peekChar(&s)) >= precedence(infix[i])) {
                postfix[k++] = popChar(&s);
            }
            pushChar(&s, infix[i]);
        }
        i++;
    }

    while (!isCharEmpty(&s)) {
        postfix[k++] = popChar(&s);
    }

    postfix[k] = '\0';
}

int evaluatePostfix(char postfix[]) {
    IntStack s;
    initIntStack(&s);
    int i = 0;

    while (postfix[i] != '\0') {
        if (isdigit(postfix[i])) {
            pushInt(&s, postfix[i] - '0');
        }
        else {
            int val2 = popInt(&s);
            int val1 = popInt(&s);
            int result;

            switch (postfix[i]) {
                case '+': result = val1 + val2; break;
                case '-': result = val1 - val2; break;
                case '*': result = val1 * val2; break;
                case '/': result = val1 / val2; break;
            }
            pushInt(&s, result);
        }
        i++;
    }

    return popInt(&s);
}

int main() {
    char infix[MAX];
    char postfix[MAX];

    printf("Enter infix expression (single digit operands only): ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix Expression: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("Evaluation Result: %d\n", result);

    return 0;
}