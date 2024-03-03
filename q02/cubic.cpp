#include <iostream>
#include "cubic.h"

using namespace std;

Cubic::Cubic(){
    
    Polynomial(3);
}

Cubic::Cubic(float a3, float a2, float a1, float a0){
    Polynomial(3);
    setCoeff(3, a3);
    setCoeff(2, a2);
    setCoeff(1, a1);
    setCoeff(0, a0);
}