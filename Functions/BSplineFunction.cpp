#include <memory>
#include "BSplineFunction.h"
#include "BSplineDerivative.h"

BSplineFunction::BSplineFunction(double left_bound, double dividing_point, double right_bound)
        : derivative(BSplineDerivative(left_bound, dividing_point, right_bound)) {
    this->left_bound = left_bound;
    this->right_bound = right_bound;
    this->dividing_point = dividing_point;
}

double BSplineFunction::value_at_point(double point) const {
    if(point <= left_bound || point >= right_bound) {
        return 0;
    }

    if(point <= dividing_point) {
        return (point - left_bound) / (dividing_point - left_bound);
    } else {
        return (right_bound - point) / (right_bound - dividing_point);
    }
}

double BSplineFunction::derivative_at_point(double point) {
    return derivative.value_at_point(point);
}

double BSplineFunction::get_dividing_point() const {
    return dividing_point;
}

BSplineDerivative BSplineFunction::get_derivative() const{
    return derivative;
}

double BSplineFunction::getLeftBound() const {
    return left_bound;
}

double BSplineFunction::getDividingPoint() const {
    return dividing_point;
}

double BSplineFunction::getRightBound() const {
    return right_bound;
}
