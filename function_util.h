#ifndef ACOUSTIC_VIBRATIONS_SOLVER_FUNCTION_UTIL_H
#define ACOUSTIC_VIBRATIONS_SOLVER_FUNCTION_UTIL_H

#include "Eigen/Dense"
#include "Functions/Function.h"

Eigen::VectorXd solve_equation(const Eigen::MatrixXd& b_mapping_values, const Eigen::VectorXd& l_mapping_values);

double integral_approximation(const Function& function, double left_bound, double right_bound);

void visualize(const Function& function, double left_range_bound, double right_range_bound);

#endif //ACOUSTIC_VIBRATIONS_SOLVER_FUNCTION_UTIL_H
