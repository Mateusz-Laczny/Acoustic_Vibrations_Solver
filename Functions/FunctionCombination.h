#ifndef ACOUSTIC_VIBRATIONS_SOLVER_FUNCTIONCOMBINATION_H
#define ACOUSTIC_VIBRATIONS_SOLVER_FUNCTIONCOMBINATION_H



#include <memory>
#include <vector>
#include "Function.h"
#include "../Eigen/Dense"

class FunctionCombination : public Function {
private:
    std::vector<std::shared_ptr<Function>> functions;
    Eigen::VectorXd coefficients;
public:
    FunctionCombination(std::vector<std::shared_ptr<Function>> functions, Eigen::VectorXd coefficients);

    FunctionCombination();

    double value_at_point(double point) const override;
};


#endif //ACOUSTIC_VIBRATIONS_SOLVER_FUNCTIONCOMBINATION_H
