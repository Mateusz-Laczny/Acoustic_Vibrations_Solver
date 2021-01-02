#include "FunctionCombination.h"

#include <utility>
#include "../Eigen/Dense"

FunctionCombination::FunctionCombination(std::vector<std::shared_ptr<Function>> functions, Eigen::VectorXd coefficients) {
    this->functions = std::move(functions);
    this->coefficients = std::move(coefficients);
}

double FunctionCombination::value_at_point(double point) const {
    double result = 0;

    for(int i = 0; i < functions.size(); i++) {
        result += functions[i]->value_at_point(point) * coefficients(i);
    }

    return result;
}

FunctionCombination::FunctionCombination() = default;
