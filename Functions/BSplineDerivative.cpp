#include "BoundedFunction.h"
#include "BSplineDerivative.h"

BSplineDerivative::BSplineDerivative(double left_bound, double dividing_point, double right_bound) {
    this->left_bound = left_bound;
    this->dividing_point = dividing_point;
    this->right_bound = right_bound;
}

double BSplineDerivative::value_at_point(double point) const {
    if(point <= left_bound || point >= right_bound) {
        return 0;
    }

    if(point <= dividing_point) {
        return 1.0 / (dividing_point - left_bound);
    } else {
        return (-1.0) / (right_bound - dividing_point);
    }
}

double BSplineDerivative::getDividingPoint() const {
    return dividing_point;
}

double BSplineDerivative::getLeftBound() const {
    return left_bound;
}

double BSplineDerivative::getRightBound() const {
    return right_bound;
}

