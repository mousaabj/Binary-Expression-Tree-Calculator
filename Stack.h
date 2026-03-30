#pragma once
#include "Expression.h"


class Stack {
private:
    // Internal structure representing a single element in the stack.
    // Each StackNode stores a pointer to a Node and a pointer to the next element.
    struct StackNode {
        Node* data;        // Pointer to the Node stored in the stack
        StackNode* next;   // Pointer to the next StackNode in the stack
    };

    StackNode* top; // Pointer to the top element of the stack

public:
    // Constructor initializes an empty stack by setting top to nullptr.
    Stack() { top = nullptr; }

    // push: Adds a new Node pointer to the top of the stack.
    // A new StackNode is dynamically allocated, and its next pointer
    // is set to the current top before updating top.
    void push(Node* n) {
        StackNode* temp = new StackNode; // Allocate new stack node
        temp->data = n;                  // Store the given Node pointer
        temp->next = top;                // Link new node to previous top
        top = temp;                      // Update top to the new node
    }

    // pop: Removes and returns the Node pointer from the top of the stack.
    // If the stack is empty, nullptr is returned.
    // The top node is deleted to prevent memory leaks.
    Node* pop() {
        if (!top) return nullptr;        // Check for empty stack
        StackNode* temp = top;           // Store current top
        Node* val = temp->data;          // Retrieve stored Node pointer
        top = top->next;                 // Move top to the next element
        delete temp;                     // Free memory of removed node
        return val;                      // Return the popped Node pointer
    }

    // peek: Returns the Node pointer at the top of the stack without removing it.
    // If the stack is empty, nullptr is returned.
    Node* peek() {
        if (!top) return nullptr;        // Check for empty stack
        return top->data;                // Return top element's data
    }

    // isEmpty: Checks whether the stack is empty.
    // Returns true if there are no elements, otherwise false.
    bool isEmpty() {
        return top == nullptr;
    }
};
