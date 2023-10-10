#include "includes.h"
#include "function.h"
#include "window.h"


int main(){
    
    initialize_ncurses();
    initialize_window();

    Node *Head[10] = {NULL};
    int32_t intAvailable = 0;
    char strName[15] = {0};
    int32_t intPosition1 = 0, intPosition2 = 0;
    int32_t intTerm = 0;

    Node *answer = NULL;
    Node *temp = answer;
    
    int32_t intPlayerChoice = 0;

    while(1){
        intPlayerChoice = menu_select();

        switch (intPlayerChoice) {
            case 0: // Input New Polynomial
                if (intAvailable < 10){
                    echo();
                    mvwprintw(winTERMINAL, 1, 1, "Input New Polynomial: ");
                    mvwprintw(winTERMINAL, 2, 1, "Name of polynomial: ");
                    wrefresh(winTERMINAL);
                    wgetnstr(winTERMINAL, strName, 10);
                    mvwprintw(winSTORAGE, 1 + intAvailable, 1, "%d. %s", intAvailable + 1, strName);
                    noecho();

                    Head[intAvailable] = create_polynomial(Head[intAvailable]);
                    print_polynomial(Head[intAvailable], intAvailable, winSTORAGE);
                    intAvailable++;
                }
                else {
                    echo();
                    mvwprintw(winTERMINAL, 1, 1, "Input New Polynomial: ");
                    mvwprintw(winTERMINAL, 2, 1, "No more space for new polynomial!");
                    wrefresh(winTERMINAL);
                    noecho();

                    clean_message(0);
                }

                break;
            case 1: // Display Specfic Coefficient
                echo();
                mvwprintw(winTERMINAL, 1, 1, "Display Specfic Coefficient: ");
                mvwprintw(winTERMINAL, 2, 1, "Position of polynomial: ");
                wrefresh(winTERMINAL);
                wscanw(winTERMINAL, "%d", &intPosition1);

                print_polynomial_specfic_coefficient(Head[intPosition1 - 1]);
                noecho();
                clean_message(0);
                break;
            case 2: // Add a term to the polynomial
                echo();
                mvwprintw(winTERMINAL, 1, 1, "Add a term to the polynomial: ");
                mvwprintw(winTERMINAL, 2, 1, "Position of polynomial: ");
                wrefresh(winTERMINAL);
                wscanw(winTERMINAL, "%d", &intPosition1);

                int32_t intExponent;
                float floatCoefficient;
                mvwprintw(winTERMINAL, 3, 1, "Coefficient for the term: ");
                wrefresh(winTERMINAL);
                wscanw(winTERMINAL, "%f", &floatCoefficient);
                mvwprintw(winTERMINAL, 3, 1 + WINDOW_TERMINAL_WIDTH/2, "Exponent for the term: ");
                wrefresh(winTERMINAL);
                wscanw(winTERMINAL, "%d", &intExponent);

                Head[intPosition1 - 1] = insert_node(Head[intPosition1 - 1], floatCoefficient, intExponent);

                clean_zero_coefficient(&Head[intPosition1 - 1]);

                print_polynomial(Head[intPosition1 - 1], intPosition1 - 1, winSTORAGE);
                noecho();
                clean_message(0);

                break;
            case 3: // Remove a specified exponent
                echo();
                mvwprintw(winTERMINAL, 1, 1, "Remove a specified exponent: ");
                mvwprintw(winTERMINAL, 2, 1, "Position of polynomial: ");
                wrefresh(winTERMINAL);
                wscanw(winTERMINAL, "%d", &intPosition1);

                clean_specfic_exponent(&Head[intPosition1 - 1]);

                print_polynomial(Head[intPosition1 - 1], intPosition1 - 1, winSTORAGE);
                noecho();
                clean_message(0);
                break;
            case 4: // Add two polynomials
                echo();
                mvwprintw(winTERMINAL, 1, 1, "Add two polynomials: ");
                mvwprintw(winTERMINAL, 2, 1, "Position of polynomial 1: ");
                wrefresh(winTERMINAL);
                wscanw(winTERMINAL, "%d", &intPosition1);
                mvwprintw(winTERMINAL, 3, 1, "Position of polynomial 2: ");
                wrefresh(winTERMINAL);
                wscanw(winTERMINAL, "%d", &intPosition2);

                answer = add_polynomial(Head[intPosition1 - 1], Head[intPosition2 - 1], 1);

                mvwprintw(winTERMINAL, 4, 1, "Answer: ");

                print_polynomial(answer, 3, winTERMINAL);

                noecho();
                clean_message(0);
                break;
            case 5: // Minus two polynomials
                echo();
                mvwprintw(winTERMINAL, 1, 1, "Minus two polynomials: ");
                mvwprintw(winTERMINAL, 2, 1, "Position of polynomial 1: ");
                wrefresh(winTERMINAL);
                wscanw(winTERMINAL, "%d", &intPosition1);
                mvwprintw(winTERMINAL, 3, 1, "Position of polynomial 2: ");
                wrefresh(winTERMINAL);
                wscanw(winTERMINAL, "%d", &intPosition2);

                answer = add_polynomial(Head[intPosition1 - 1], Head[intPosition2 - 1], -1);
                mvwprintw(winTERMINAL, 4, 1, "Answer: ");
                print_polynomial(answer, 3, winTERMINAL);

                noecho();
                clean_message(0);
                break;
            case 6: // Multiply two polynomials
                echo();
                mvwprintw(winTERMINAL, 1, 1, "Multiply two polynomials: ");
                mvwprintw(winTERMINAL, 2, 1, "Position of polynomial 1: ");
                wrefresh(winTERMINAL);
                wscanw(winTERMINAL, "%d", &intPosition1);
                mvwprintw(winTERMINAL, 3, 1, "Position of polynomial 2: ");
                wrefresh(winTERMINAL);
                wscanw(winTERMINAL, "%d", &intPosition2);

                answer = multiply_polynomial(Head[intPosition1 - 1], Head[intPosition2 - 1]);
                mvwprintw(winTERMINAL, 4, 1, "Answer: ");
                print_polynomial(answer, 3, winTERMINAL);

                noecho();
                clean_message(0);
                break;
            case 7: // Divide two polynomials
                echo();
                mvwprintw(winTERMINAL, 1, 1, "Divide two polynomials: ");
                mvwprintw(winTERMINAL, 2, 1, "Position of polynomial 1: ");
                wrefresh(winTERMINAL);
                wscanw(winTERMINAL, "%d", &intPosition1);
                mvwprintw(winTERMINAL, 3, 1, "Position of polynomial 2: ");
                wrefresh(winTERMINAL);
                wscanw(winTERMINAL, "%d", &intPosition2);

                if (Head[intPosition1 - 1]->intExponent >= Head[intPosition2 - 1]->intExponent){
                    answer = divide_polynomial(Head[intPosition1 - 1], Head[intPosition2 - 1]);
                    mvwprintw(winTERMINAL, 4, 1, "Quotient: ");
                    print_polynomial(answer, 3, winTERMINAL);
                }
                else 
                    mvwprintw(winTERMINAL, 4, 1, "Quotient:    Invalid");

                answer = add_polynomial(Head[intPosition1 - 1], multiply_polynomial(answer, Head[intPosition2 - 1]), -1);                
                if (answer == NULL){
                    mvwprintw(winTERMINAL, 5, 1, "Remainder:    0x^0");
                }
                else {
                    mvwprintw(winTERMINAL, 5, 1, "Remainder: ");
                    print_polynomial(answer, 4, winTERMINAL);
                }

                noecho();
                clean_message(0);

                break;
            case 8: // Quit
                endwin();
                exit(0);
            
            // default:
        }
    }


    refresh();
    getch();

    endwin();

    return 0;
}