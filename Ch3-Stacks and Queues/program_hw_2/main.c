#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_SIZE 10000

typedef struct _stack {
    char words[MAX_SIZE][MAX_SIZE];
    int wordsSize[MAX_SIZE];
    int cursor[MAX_SIZE];
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

void push(Stack *stack, const char *word) {
    if (is_full(stack)) {
        printf("Stack Overflow!\n");
        return;
    }
    
    strcpy(stack->words[stack->top + 1], word);
    stack->wordsSize[++stack->top] = strlen(word);
}

char* pop(Stack *s) {
    if (is_empty(s)) {
        printf("Stack Underflow!\n");
        return NULL;
    }
    return s->words[s->top--];
}

char* get_word(Stack *s) {
    if (is_empty(s)) {
        printf("Stack Underflow!\n");
        return NULL;
    }
    return s->words[s->top];
}

int get_cursor(Stack *s) {
    if (is_empty(s)) {
        printf("Stack Underflow!\n");
        return 0;
    }
    return s->cursor[s->top];
}

int print_word(Stack *s, int option) {
    if (option == 1)
        printf("Current words: ");
    else if (option == 2)
        printf("After  action: ");
    else
        printf("Init word: ");
    
    if (is_empty(s)) {
        printf("Stack Underflow!\n");
        return -1;
    }

    for (int i = 0; i < s->cursor[s->top]; ++i) {
        printf("%c", s->words[s->top][i]);
    }
    if (s->cursor[s->top] != s->wordsSize[s->top]) {
        printf("|");
    }
    for (int i = s->cursor[s->top]; i < s->wordsSize[s->top]; ++i) {
        printf("%c", s->words[s->top][i]);
    }
    printf("\n\n");

    return 0;
}

char char_Init[MAX_SIZE] = {0};
char temp_String[MAX_SIZE] = {0};

Stack stack;


int main() {

    int redo = 0;
    int cursor = 0;
    
    initialize(&stack);
    
    printf("Welcome to the simple text editor!\nPlease enter an initial string consisting a/A-z/Z and space: ");
    scanf("%[^\n]s", char_Init);

    push(&stack, char_Init);
    stack.cursor[stack.top] = strlen(char_Init);

    print_word(&stack, 0);

    while (1) {
        printf("Wait 1 seconds to continue...\n");
        sleep(1);
        system("clear");

        print_word(&stack, 1);

        char action;
        printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("Please enter an action (a/A~z/Z, space) Add word, (0) Delete word, (1) Move cursor left, (2) Move cursor right, (3) Undo, (4) Redo, (esc) Exit: ");

        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);

        action = getchar();
        if (isalpha(action) || action == ' ') {
            printf("Adding word...\n");
            strcpy(temp_String, get_word(&stack));
            cursor = get_cursor(&stack);
            if (cursor == stack.wordsSize[stack.top]) {
                temp_String[cursor] = action;
                temp_String[cursor + 1] = '\0';
            }
            else {
                for (int i = stack.wordsSize[stack.top]; i > cursor; --i)
                    temp_String[i] = temp_String[i - 1];
                temp_String[cursor] = action;
                temp_String[stack.wordsSize[stack.top] + 1] = '\0';
            }
            push(&stack, temp_String);
            stack.cursor[stack.top] = cursor + 1;
            redo = 0;
        }
        else {
            switch (action) {
                case '0':
                    printf("Deleting word...\n");
                    cursor = get_cursor(&stack);
                    if (cursor == 0) {
                        printf("Cursor is at the beginning of the string!\n");
                        break;
                    }
                    strcpy(temp_String, get_word(&stack));
                    for (int i = cursor - 1; i < stack.wordsSize[stack.top] - 1; ++i)
                        temp_String[i] = temp_String[i + 1];
                    temp_String[stack.wordsSize[stack.top] - 1] = '\0';
                    push(&stack, temp_String);
                    stack.cursor[stack.top] = cursor - 1;
                    redo = 0;
                    break;
                case '1':
                    printf("Moving cursor left...\n");
                    strcpy(temp_String, get_word(&stack));
                    cursor = get_cursor(&stack);
                    push(&stack, temp_String);
                    if (cursor == 0)
                        stack.cursor[stack.top] = 0;
                    else
                        stack.cursor[stack.top] = cursor - 1;
                    redo = 0;
                    break;
                case '2':
                    printf("Moving cursor right...\n");
                    strcpy(temp_String, get_word(&stack));
                    cursor = get_cursor(&stack);
                    push(&stack, temp_String);
                    if (cursor != stack.wordsSize[stack.top])
                        stack.cursor[stack.top] = cursor + 1;
                    else
                        stack.cursor[stack.top] = cursor;
                    redo = 0;
                    break;
                case '3':
                    printf("Undoing...\n");
                    if (stack.top == 0) {
                        printf("No more undo...\n");
                        break;
                    }
                    stack.top--;
                    redo++;
                    break;
                case '4':
                    printf("Redoing...\n");
                    if (redo == 0) {
                        printf("No more redo...\n");
                        break;
                    }
                    stack.top++;
                    redo--;
                    break;
                default:
                    printf("exit...\n");
                    return 0;
            }
        }
        print_word(&stack, 2);
    }
    return 0;
}
