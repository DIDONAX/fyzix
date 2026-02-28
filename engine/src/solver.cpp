#include "solver.h"


EulerSolver::EulerSolver(double dt, int n): dt_(dt), n_(n) {}
EulerSolver::~EulerSolver(){}

void EulerSolver::solve(Mass* obj) {
    for (int i = 0; i < n_; ++i) {
        vec2 temp = obj->p_;

        obj->p_.x_ = 2 * obj->p_.x_ - obj->prev_.x_ + obj->a_.x_ * dt_ * dt_; 
        obj->p_.y_ = 2 * obj->p_.y_ - obj->prev_.y_ + obj->a_.y_ * dt_ * dt_; 

        obj->prev_ = temp;

        obj->a_.x_ = 0.0;
        obj->a_.y_ = 0.0; 
    }
}
