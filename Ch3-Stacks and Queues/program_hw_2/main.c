#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

typedef struct _stack {
    char actions[MAX_SIZE][1];
    int top;
} Stack;

void initialize(Stack *s) {
    s->top = -1;
}

int is_empty(Stack *s) {
    return s->top == -1;
}

int is_full(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack *stack_Undo, Stack *stack_Redo, const char *action) {
    if (is_full(stack_Undo)) {
        printf("Stack Overflow!\n");
        return;
    }
    strcpy(stack_Undo->actions[++stack_Undo->top], action);
    initialize(stack_Redo);
}

char* pop(Stack *s) {
    if (is_empty(s)) {
        printf("Stack Underflow!\n");
        return NULL;
    }
    return s->actions[s->top--];
}

int main() {

    char char_String[MAX_SIZE] = {0};

    Stack stack_Undo, stack_Redo;
    initialize(&stack_Undo);
    initialize(&stack_Redo);

    printf("Please enter an initial string consisting a/A-z/Z and space: ");
    scanf("%[^\n]s", char_String);


    // Loops for the user to enter the actions
    // while (1) {
    //     char action[1];
    //     printf("Please enter an action (a/A~z/Z, space) Add word, (0) Delete word, (1) Move cursor left, (2) Move cursor right, (3) Undo, (4) Redo :");
    //     scanf("%s", action);

    //     if (strcmp(action, "i") == 0) {
    //         char insert_String[MAX_SIZE] = {0};
    //         printf("Please enter a string to insert: ");
    //         scanf("%s", insert_String);

    //         // Insert the string
    //         int i = 0;
    //         while (insert_String[i] != '\0') {
    //             char_String[strlen(char_String) + 1] = '\0';
    //             char_String[strlen(char_String)] = insert_String[i];
    //             i++;
    //         }

    //         // Push the action to the stack
    //         push(&stack_Undo, &stack_Redo, "i");
    //     }
    // }


    int i = 0;
    while (char_String[i] != '\0') {
        printf("%c", char_String[i]);
        i++;
    }
    printf("\n");



    

    // push(&stack_Undo, &stack_Redo, "1");
    // push(&stack_Undo, &stack_Redo, "2");
    // push(&stack_Undo, &stack_Redo, "3");
    
    // printf("Undoing: %s\n", pop(&stack_Undo));
    // printf("Undoing: %s\n", pop(&stack_Undo));

    // push(&stack_Undo, &stack_Redo, "4");
    // printf("Redoing: %s\n", pop(&stack_Redo));

    return 0;
}
