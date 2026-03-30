#include <iostream>                
#include "Expression.h"      // Contains the ExpressionTree class definition

using namespace std;


int main() {
    char choice = 'y';  // Stores user's decision to continue or exit program

    // Display welcome message to the user
    cout << "GREETINGS....WELCOME To Tree Calculator" << endl;

    // Loop allows user to evaluate multiple expressions
    while (choice == 'y' || choice == 'Y') {
        char expr[100];  // Character array to store the user's infix expression

        // Prompt user to input an infix expression
        cout << "\nPlease enter an infix expression: ";
        cin.getline(expr, 100);  // Reads full line including spaces

        // Create an ExpressionTree object
        ExpressionTree tree;

        // Build the expression tree from the given infix expression
        tree.buildTree(expr);

        // Display the prefix (preorder traversal) form of the expression
        cout << "Prefix: ";
        tree.printPrefix();

        // Display the postfix (postorder traversal) form of the expression
        cout << "Postfix: ";
        tree.printPostfix();

        // Evaluate the expression tree and display the result
        cout << "Result: " << tree.getResult() << endl;

        // Ask user if they want to evaluate another expression
        cout << "\nWould you like to enter another expression (y/n)?: ";
        cin >> choice;

        cin.ignore();  // Clears newline character from input buffer to avoid input issues
    }

    // Display exit message when user chooses to stop
    cout << "Thank you for using my program!" << endl;

    return 0;  // Indicates successful program termination
}
