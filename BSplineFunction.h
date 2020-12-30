#ifndef ACOUSTIC_VIBRATIONS_SOLVER_BSPLINEFUNCTION_H
#define ACOUSTIC_VIBRATIONS_SOLVER_BSPLINEFUNCTION_H


#include "BoundedFunction.h"
#include "BSplineDerivative.h"

class BSplineFunction : public Function {
private:
    double left_bound;
    // Point of division, where the value of the function is 1
    double dividing_point;
    double right_bound;

    BSplineDerivative derivative;
public:
    BSplineFunction(double left_bound, double dividing_point, double right_bound);

    double value_at_point(double point) const override;

    double derivative_at_point(double point);

    double get_dividing_point() const;

    BSplineDerivative get_derivative() const;

    double getLeftBound() const;

    double getDividingPoint() const;

    double getRightBound() const;
};


#endif //ACOUSTIC_VIBRATIONS_SOLVER_BSPLINEFUNCTION_H
