#include "solver.h"


EulerSolver::EulerSolver(double dt, int n): dt_(dt), n_(n) {}
EulerSolver::~EulerSolver(){}

void EulerSolver::solve(Object* obj) {
    for (int i = 0; i < n_; ++i) {
        // 1. Calculate Half-Step Velocity
        // v(t + 0.5dt) = v(t) + 0.5 * a(t) * dt
        double v_half_x = obj->v_.x_ + 0.5 * obj->a_.x_ * dt_;
        double v_half_y = obj->v_.y_ + 0.5 * obj->a_.y_ * dt_;

        // 2. Update Position using the half-step velocity
        // p(t + dt) = p(t) + v(half) * dt
        obj->p_.x_ += v_half_x * dt_;
        obj->p_.y_ += v_half_y * dt_;

        // 3. Update Full-Step Velocity
        // v(t + dt) = v(half) + 0.5 * a(t) * dt
        // Note: In a true Verlet, we'd use the NEW acceleration here.
        // In this single-pass version, this is effectively "Second-Order" accurate.
        obj->v_.x_ = v_half_x + 0.5 * obj->a_.x_ * dt_;
        obj->v_.y_ = v_half_y + 0.5 * obj->a_.y_ * dt_;

        // 4. RESET Acceleration for the next frame's GravF calculation
        obj->a_.x_ = 0.0;
        obj->a_.y_ = 0.0; 
    }
}
