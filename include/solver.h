#pragma once 

#include "object.h"

struct EulerSolver {
    double dt_;
    int n_;
    EulerSolver(double dt, int n);
    ~EulerSolver();
    void solve(Object* obj); 
};
