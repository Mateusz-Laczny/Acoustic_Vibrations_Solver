#ifndef ACOUSTIC_VIBRATIONS_SOLVER_BOUNDEDFUNCTION_H
#define ACOUSTIC_VIBRATIONS_SOLVER_BOUNDEDFUNCTION_H


#include "Function.h"

class BoundedFunction : public Function {
protected:
    double left_bound;
    double right_bound;
public:
    BoundedFunction(double left_bound, double right_bound);

    double value_at_point(double point) const override;

    double getLeftBound() const;

    double getRightBound() const;
};


#endif //ACOUSTIC_VIBRATIONS_SOLVER_BOUNDEDFUNCTION_H
