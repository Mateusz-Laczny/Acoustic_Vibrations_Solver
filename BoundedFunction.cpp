#include "BoundedFunction.h"

BoundedFunction::BoundedFunction(double left_bound, double right_bound) : Function() {
    this->left_bound = left_bound;
    this->right_bound = right_bound;
}

double BoundedFunction::getLeftBound() const {
    return left_bound;
}

double BoundedFunction::getRightBound() const {
    return right_bound;
}

double BoundedFunction::value_at_point(double point) const {
    return point;
}
