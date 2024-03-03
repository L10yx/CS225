#include <iostream>
#include "polynomial.h"

using namespace std;

// Default constructor
// constructs a first-order polynomial with all coefficients set to 1.
Polynomial::Polynomial(){
    order_ = 1;
    a_ = new float[order_+1];
    a_[0] = 1;
    a_[1] = 1;
}

// One-parameter constructor
// constructs a polynomial of user-supplied order with all coefficients set to 1.
Polynomial::Polynomial(unsigned int order){
    order_ = order;
    a_ = new float[order_+1];
    for (unsigned int i = 0; i <= order; i++){
        a_[i] = 1;
    }
}

// helper function to copy - IMPLEMENT ME
void Polynomial::copy_(const Polynomial &p) {
    // Clear self
    delete[] a_;
    // Copy `other` to self
    order_ = p.order_;
    a_ = new float[order_];
    for (unsigned i = 0; i <= order_; i++) {
      a_[i] = p.a_[i];
    }
}

// helper function to destroy - IMPLEMENT ME
void Polynomial::destroy_() {
    delete[] a_;
}

// Copy constructor - must use copy_() function
// constructs a new polynomial that is a copy of an existing polynomial
Polynomial::Polynomial(Polynomial const & other){
    a_ = NULL;
    copy_(other);
}

// Destructor - must use destroy_() function
// destroys a polynomial object
Polynomial::~Polynomial(){
    destroy_();
}

// Assignment operator - must use copy_() function
// assigns rhs Polynomial object to 'this' Polynomial object
Polynomial const & Polynomial::operator= (Polynomial const & other){
    if (this != &other) { copy_(other); }
    return *this;
}

// getPolyOrder
// returns the polynomial order
unsigned int Polynomial::getPolyOrder(){
    return order_;
}

// getCoeff
// returns the coefficient of the x^i term in polynomial
// note: If the object does not contain a term with power i (e.g., 
//       i>order_), a coefficient value of zero is returned.
float Polynomial::getCoeff(unsigned int i){
    if (i > order_) return 0;
    return a_[i];
}

// setCoeff
// If i <= order_, set a term, value*x^i, in a polynomial
void Polynomial::setCoeff(unsigned int i, float value){
    if (i <= order_) a_[i] = value;
}

// addition operator
// adds two polynomials together and returns a new polynomial 
Polynomial const & Polynomial::operator+ (Polynomial & other){
    other.order_ += order_;
    for (unsigned int i = 0; i <= other.order_; i++){
        other.a_[i] = 1;
    }
    return other;
}

// insertion operator for output
// note: This function has been provided for you -- DO NOT CHANGE IT!
ostream & operator << (ostream &out, const Polynomial& p)
{
    bool printed = false;

    for (int i = p.order_; i >= 0; i--)
    {
        float c = p.a_[i];

        if (c != 0.0)
        {
            if (printed) out << " + ";
            printed = true;
            out << c << "*X^" << i;
        }
    }

    return out;
}
