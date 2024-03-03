#include <iostream>
#include "Stack.h"

// compile:  g++ -std=c++1y  mainStack.cpp

int main() {

    Stack <char> *stack = new Stack <char>;
    char a='5';
    char b='2';
    char c='2';
    char d='s';
    char e='c';


    stack->push(a);
    stack->push(b);
    stack->push(c);
    stack->push(d);
    stack->push(e);

    // uncomment this and see what happens
    // stack->push('!');
    // why did this work in lecture11 code?

    stack->printStack();

    stack->pop();
    stack->pop();

    stack->printStack();

    stack->pop();
    stack->pop();
    stack->pop();

    delete stack;


    return 0;
}

