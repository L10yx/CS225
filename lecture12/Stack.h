#ifndef LIST_H
#define LIST_H

#include <iostream>

using namespace std;

template <class T>
class Stack {

  public:
    Stack(); 
    Stack(const Stack &other);
    ~Stack();
    Stack& operator=(const Stack &other);

    void push(T &t);
    T& pop();
    bool isEmpty() const;

    void printStack() const;

  private:
    T ** arr_;
    unsigned size_, count_;

};

#include "Stack.cpp"

#endif
