#ifndef QUAD_H
#define QUAD_H

#include "polynomial.h"

class Cubic : public Polynomial {

  public:
    // Default constructor
    Cubic();

    // four-parameter constructor
    Cubic(float a3, float a2, float a1, float a0);

};

#endif


