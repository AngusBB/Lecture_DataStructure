#include "includes.h"
#include "function.h"
#include "window.h"

// ==============================================================================================================================
Node *create_polynomial(Node *Head){

    int32_t intAmount;
    float floatCoefficient;
    int32_t intExponent;

    echo();

    mvwprintw(winTERMINAL, 2, 1 + WINDOW_TERMINAL_WIDTH/2, "Amount of terms: ");
    wrefresh(winTERMINAL);
    wscanw(winTERMINAL, "%d", &intAmount);

    for (int32_t i = 0; i < intAmount; i++){

        mvwprintw(winTERMINAL, 3 + i, 1, "Coefficient for term %d: ", i + 1);
        wrefresh(winTERMINAL);
        wscanw(winTERMINAL, "%f", &floatCoefficient);
        mvwprintw(winTERMINAL, 3 + i, 1 + WINDOW_TERMINAL_WIDTH/2, "Exponent for term %d: ", i + 1);
        wrefresh(winTERMINAL);
        wscanw(winTERMINAL, "%d", &intExponent);

        Head = insert_node(Head, floatCoefficient, intExponent);
    }

    noecho();

    clean_zero_coefficient(&Head);

    clean_message(1);

    return Head;
}
// ==============================================================================================================================
Node *insert_node(Node *Head, float floatCoefficient, int32_t intExponent){
    
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->floatCoefficient = floatCoefficient;
    newNode->intExponent = intExponent;
    newNode->ptr_Next = NULL;

    if (Head == NULL){ // empty list
        Head = newNode;
    }
    else if (Head->ptr_Next == NULL){ // only one node

        if (Head->intExponent < newNode->intExponent){
            newNode->ptr_Next = Head;
            Head = newNode;
        }
        else if (Head->intExponent == newNode->intExponent){
            Head->floatCoefficient += newNode->floatCoefficient;
            free(newNode);
        }
        else
            Head->ptr_Next = newNode;
    }
    else { // more than one node

        Node *current = Head;
        Node *prev = NULL;

        while (current != NULL && current->intExponent > newNode->intExponent){
            prev = current;
            current = current->ptr_Next;
        }

        if (current == Head && current->intExponent < newNode->intExponent){ // insert at the beginning, e.g. ax^4 insert in bx^3+cx^2+dx^1
            // printf("insert at the beginning\n");
            newNode->ptr_Next = Head;
            Head = newNode;
        }
        else if (current != NULL && current->intExponent == newNode->intExponent){ // equal exponent e.g. ax^3, ax^2, ax^1 insert in bx^3+cx^2+dx^1
            // printf("equal exponent\n");
            current->floatCoefficient += newNode->floatCoefficient;
            free(newNode);
        }
        else if (current == NULL){ // insert at the end, e.g. ax^0 insert in bx^3+cx^2+dx^1
            // printf("insert at the end\n");
            prev->ptr_Next = newNode;
        }
        else { // insert in the middle, e.g. ax^2 insert in bx^3+cx^1
            // printf("insert in the middle\n");
            prev->ptr_Next = newNode;
            newNode->ptr_Next = current;
        }
    }

    return Head;
}
// ==============================================================================================================================
void clean_zero_coefficient(Node **Head){

    Node *temp = *Head;
    Node *prev = NULL;

    while (temp != NULL){
        if (temp->floatCoefficient == 0){
            if (temp == *Head){
                *Head = temp->ptr_Next;
                free(temp);
                temp = *Head;
            }
            else {
                prev->ptr_Next = temp->ptr_Next;
                free(temp);
                temp = prev->ptr_Next;
            }
        }
        else {
            prev = temp;
            temp = temp->ptr_Next;
        }
    }
}
// ==============================================================================================================================
void clean_specfic_exponent(Node **Head){

    int32_t intExponent;
    
    mvwprintw(winTERMINAL, 3, 1, "Exponent to delete: ");
    wscanw(winTERMINAL, "%d", &intExponent);

    Node *temp = *Head;
    Node *prev = NULL;
    while (temp != NULL){
        if (temp->intExponent == intExponent){
            if (temp == *Head){
                *Head = temp->ptr_Next;
                free(temp);
                temp = *Head;
            }
            else {
                prev->ptr_Next = temp->ptr_Next;
                free(temp);
                temp = prev->ptr_Next;
            }
        }
        else {
            prev = temp;
            temp = temp->ptr_Next;
        }
    }
}
// ==============================================================================================================================
void print_polynomial(Node *Head, int32_t intOffset, WINDOW *win){

    if (Head == NULL){
        // mvwprintw(winSTORAGE, "The polynomial is empty.\n");
    }
    else{
        int32_t intTerm = 0;

        Node *temp = Head;
        while (temp != NULL){
            mvwprintw(win, 1 + intOffset, 10 + intTerm * 11, "%.1fx^%d", temp->floatCoefficient, temp->intExponent);
            intTerm++;
            temp = temp->ptr_Next;

            if (temp != NULL)
                wprintw(win, " + ");
            else
                wprintw(win, "            ");
        }
    }
    wrefresh(win);
}
// ==============================================================================================================================
void print_polynomial_specfic_coefficient(Node *Head){

    if (Head == NULL){
        // mvwprintw(winTERMINAL, 1, 1, "The polynomial is empty.");
    }
    else {
        int32_t intExponent;
        bool boolFound = false;

        mvwprintw(winTERMINAL, 3, 1, "Coefficient of exponent to print: ");
        wrefresh(winTERMINAL);
        wscanw(winTERMINAL, "%d", &intExponent);

        Node *temp = Head;
        while (temp != NULL){
            if (temp->intExponent == intExponent){
                mvwprintw(winTERMINAL, 4, 1, "The coefficient of x^%d is: %.1f", intExponent, temp->floatCoefficient);
                boolFound = true;
                break;
            }
            temp = temp->ptr_Next;
        }
        if (!boolFound)
            mvwprintw(winTERMINAL, 4, 1, "The coefficient of x^%d is: 0", intExponent);
            
    }
    wrefresh(winTERMINAL);
}
// ==============================================================================================================================
Node *add_polynomial(Node *Head1, Node *Head2, float floatSign){
    
        Node *Head3 = NULL;
    
        Node *temp1 = Head1;
        Node *temp2 = Head2;
    
        while (temp1 != NULL && temp2 != NULL){
    
            if (temp1->intExponent > temp2->intExponent){
                Head3 = insert_node(Head3, temp1->floatCoefficient, temp1->intExponent);
                temp1 = temp1->ptr_Next;
            }
            else if (temp1->intExponent < temp2->intExponent){
                Head3 = insert_node(Head3, floatSign * temp2->floatCoefficient, temp2->intExponent); //TODO: fix this
                temp2 = temp2->ptr_Next;
            }
            else {
                Head3 = insert_node(Head3, temp1->floatCoefficient + floatSign * temp2->floatCoefficient, temp1->intExponent); //TODO: fix this
                temp1 = temp1->ptr_Next;
                temp2 = temp2->ptr_Next;
            }
        }
    
        while (temp1 != NULL){
            Head3 = insert_node(Head3, temp1->floatCoefficient, temp1->intExponent);
            temp1 = temp1->ptr_Next;
        }
    
        while (temp2 != NULL){
            Head3 = insert_node(Head3, floatSign * temp2->floatCoefficient, temp2->intExponent); //TODO: fix this
            temp2 = temp2->ptr_Next;
        }

        clean_zero_coefficient(&Head3);

        return Head3;
}
// ==============================================================================================================================
Node *multiply_polynomial(Node *Head1, Node *Head2){
    
        Node *Head3 = NULL;
    
        Node *temp1 = Head1;
        Node *temp2 = Head2;
    
        while (temp1 != NULL){
            while (temp2 != NULL){
                Head3 = insert_node(Head3, temp1->floatCoefficient * temp2->floatCoefficient, temp1->intExponent + temp2->intExponent);
                temp2 = temp2->ptr_Next;
            }
            temp1 = temp1->ptr_Next;
            temp2 = Head2;
        }

        clean_zero_coefficient(&Head3);
    
        return Head3;
}
// ==============================================================================================================================
Node *divide_polynomial(Node *Head1, Node *Head2){
    
    Node *Quotient = NULL;

    Node *temp0 = Head1;
    Node *temp1 = Head1;
    Node *temp2 = Head2;

    while(temp1 != NULL && temp2 != NULL && temp1->intExponent >= temp2->intExponent){
        Quotient = insert_node(Quotient, temp1->floatCoefficient / temp2->floatCoefficient, temp1->intExponent - temp2->intExponent);
        temp1 = add_polynomial(temp0, multiply_polynomial(Quotient, Head2), -1);
    }
    
    clean_zero_coefficient(&Quotient);

    return Quotient;
}