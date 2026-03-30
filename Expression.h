#pragma once
#include <iostream>
#include <cctype>
#include <cstring>
#include "Stack.h"

using namespace std;


class Node {
public:
    char value;   // Stores the character (digit or operator)
    Node* left;   // Pointer to left child
    Node* right;  // Pointer to right child

    // Constructor initializes the node with a value
    // and sets child pointers to nullptr.
    Node(char v) {
        value = v;
        left = nullptr;
        right = nullptr;
    }
};



class ExpressionTree {
private:
    Node* root; // Root of the expression tree

    // precedence: Returns the precedence level of an operator.
    // Higher value means higher precedence.
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    // isOperator: Checks if a character is a valid operator.
    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/');
    }

    // applyOperator: Pops two nodes (operands) and one operator
    // from their respective stacks, builds a subtree, and pushes
    // the resulting node back onto the node stack.
    void applyOperator(Stack& nodes, Stack& ops) {
        Node* right = nodes.pop(); // Right operand
        Node* left = nodes.pop();  // Left operand
        Node* op = ops.pop();      // Operator node

        // Attach operands to operator
        op->left = left;
        op->right = right;

        // Push the resulting subtree back onto the node stack
        nodes.push(op);
    }

    // prefix: Recursively performs a preorder traversal
    // (root, left, right) and prints the expression in prefix form.
    void prefix(Node* node) {
        if (!node) return;           // Base case: empty node
        cout << node->value << " ";  // Visit root
        prefix(node->left);          // Traverse left subtree
        prefix(node->right);         // Traverse right subtree
    }

    // postfix: Recursively performs a postorder traversal
    // (left, right, root) and prints the expression in postfix form.
    void postfix(Node* node) {
        if (!node) return;           // Base case: empty node
        postfix(node->left);         // Traverse left subtree
        postfix(node->right);        // Traverse right subtree
        cout << node->value << " ";  // Visit root
    }

    // evaluate: Recursively evaluates the expression tree.
    // Leaf nodes (digits) are converted to integers.
    // Internal nodes (operators) apply the operation to results
    // of left and right subtrees.
    int evaluate(Node* node) {
        if (!node) return 0; // Safety check for null nodes

        // If the node is an operand (digit), convert char to int
        if (!isOperator(node->value)) {
            return node->value - '0';
        }

        // Recursively evaluate left and right subtrees
        int left = evaluate(node->left);
        int right = evaluate(node->right);

        // Apply the operator stored in this node
        switch (node->value) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return right != 0 ? left / right : 0; // Avoid division by zero
        }
        return 0; // Default return (should not normally reach here)
    }

public:
    // Constructor initializes an empty expression tree.
    ExpressionTree() { root = nullptr; }

    // buildTree: Constructs an expression tree from an infix expression.
    // Uses two stacks: one for nodes (operands) and one for operators.
    // Follows standard infix-to-expression-tree logic with precedence handling.
    void buildTree(char expr[]) {
        Stack nodes; // Stack to store operand nodes
        Stack ops;   // Stack to store operator nodes

        int len = strlen(expr); // Length of input expression

        // Iterate through each character in the expression
        for (int i = 0; i < len; i++) {
            char c = expr[i];

            if (c == ' ') continue; // Skip spaces

            // If the character is a digit, create a node and push to node stack
            if (isdigit(c)) {
                nodes.push(new Node(c));
            }
            // If opening parenthesis, push to operator stack
            else if (c == '(') {
                ops.push(new Node(c));
            }
            // If closing parenthesis, resolve the entire subexpression
            else if (c == ')') {
                while (!ops.isEmpty() && ops.peek()->value != '(') {
                    applyOperator(nodes, ops);
                }
                ops.pop(); // Remove the '('
            }
            // If operator, apply all higher or equal precedence operators first
            else if (isOperator(c)) {
                while (!ops.isEmpty() && precedence(ops.peek()->value) >= precedence(c)) {
                    applyOperator(nodes, ops);
                }
                ops.push(new Node(c)); // Push current operator
            }
        }

        // Apply any remaining operators in the stack
        while (!ops.isEmpty()) {
            applyOperator(nodes, ops);
        }

        // Final node in the node stack is the root of the expression tree
        root = nodes.pop();
    }

    // printPrefix: Public function to display the expression
    // in prefix notation.
    void printPrefix() {
        prefix(root);
        cout << endl;
    }

    // printPostfix: Public function to display the expression
    // in postfix notation.
    void printPostfix() {
        postfix(root);
        cout << endl;
    }

    // getResult: Evaluates the expression tree and returns the result.
    int getResult() {
        return evaluate(root);
    }
};