#pragma once

#include "includes.h"

typedef struct _node {
    float floatCoefficient;
    int32_t intExponent;
    struct _node *ptr_Next;
}Node;

Node *create_polynomial(Node *Head);
Node *insert_node(Node *Head, float floatCoefficient, int32_t intExponent);
void clean_zero_coefficient(Node **Head);
void clean_specfic_exponent(Node **Head);
void print_polynomial(Node *Head, int32_t intOffset, WINDOW *win);
void print_polynomial_specfic_coefficient(Node *Head);
Node *add_polynomial(Node *Head1, Node *Head2, float floatSign);
Node *multiply_polynomial(Node *Head1, Node *Head2);
Node *divide_polynomial(Node *Head1, Node *Head2);