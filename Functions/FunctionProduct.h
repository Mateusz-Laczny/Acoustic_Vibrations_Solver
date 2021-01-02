#ifndef ACOUSTIC_VIBRATIONS_SOLVER_FUNCTIONPRODUCT_H
#define ACOUSTIC_VIBRATIONS_SOLVER_FUNCTIONPRODUCT_H

#include <vector>
#include <memory>
#include "Function.h"

class FunctionProduct : public Function {
    std::vector<std::shared_ptr<Function>> functions;

public:
    explicit FunctionProduct(std::vector<std::shared_ptr<Function>> functions);

    double value_at_point(double point) const override;
};


#endif //ACOUSTIC_VIBRATIONS_SOLVER_FUNCTIONPRODUCT_H
