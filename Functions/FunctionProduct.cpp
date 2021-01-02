#include <utility>
#include <vector>
#include "FunctionProduct.h"

FunctionProduct::FunctionProduct(std::vector<std::shared_ptr<Function>> functions) {
    this->functions = std::move(functions);
}

double FunctionProduct::value_at_point(double point) const{
    double result = 1;

    for(const auto & function : functions) {
        result *= function->value_at_point(point);
    }

    return result;
}


