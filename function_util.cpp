#include <iostream>
#include <vector>
#include <memory>
#include "Eigen/Dense"
#include "BSplineFunction.h"
#include "FunctionProduct.h"
#include "SineFunction.h"

using namespace Eigen;

#define LEFT_BOUND 0.0
#define RIGHT_BOUND 2.0

// Constants for integral approximation
const double GAUSS_QUADRATURE_STEP = sqrt(3.0/5.0);
const double ZERO_POINT_WEIGHT = 8.0/9.0;
const double NON_ZERO_POINT_WEIGHT = 5.0/9.0;

VectorXd solve_equation(const MatrixXd& b_mapping_values, const VectorXd& l_mapping_values) {
    VectorXd solution(b_mapping_values.rows());
    solution = b_mapping_values.colPivHouseholderQr().solve(l_mapping_values);

    return solution;
}

/*
 * Function approximating the integral
 * using the Gauss-Legendre quadrature with 3 points
 */
double integral_approximation(const Function& function, double left_bound, double right_bound) {
    double approximation = 0.0;
    double domain_shift_coefficient = (right_bound - left_bound) / 2;
    double domain_shift_constant = (left_bound + right_bound) / 2;

    approximation += ZERO_POINT_WEIGHT * function.value_at_point(0 * domain_shift_coefficient + domain_shift_constant);
    approximation += NON_ZERO_POINT_WEIGHT * function.value_at_point((-GAUSS_QUADRATURE_STEP) * domain_shift_coefficient + domain_shift_constant);
    approximation += NON_ZERO_POINT_WEIGHT * function.value_at_point((GAUSS_QUADRATURE_STEP) * domain_shift_coefficient + domain_shift_constant);

    approximation *= domain_shift_coefficient;
    return approximation;
}

double B_mapping_value(const BSplineFunction& u_function, const BSplineFunction& v_function) {
    // Weak form of the equation is hard-coded here
    std::vector<std::shared_ptr<Function>> first_function_components;
    std::shared_ptr<Function> u_function_derivative_ptr = std::make_shared<BSplineDerivative>(u_function.get_derivative());
    std::shared_ptr<Function> v_function_derivative_ptr = std::make_shared<BSplineDerivative>(u_function.get_derivative());

    first_function_components.emplace_back(u_function_derivative_ptr);
    first_function_components.emplace_back(v_function_derivative_ptr);

    FunctionProduct first_under_integral_function = FunctionProduct(first_function_components);

    std::vector<std::shared_ptr<Function>> second_function_components;
    second_function_components.emplace_back(std::make_shared<BSplineFunction>(u_function));
    second_function_components.emplace_back(std::make_shared<BSplineFunction>(v_function));

    FunctionProduct second_under_integral_function = FunctionProduct(second_function_components);

    double first_sum_component = -(u_function.value_at_point(2) * v_function.value_at_point(2));
    // If u and v don't "cross" eachother then the integrals will be equal to 0
    double second_sum_component = 0;
    double third_sum_component = 0;

    if(u_function.get_dividing_point() == v_function.getLeftBound()) {
        // Functions "cross" eachother so there will be non-zero integrals
        second_sum_component = integral_approximation(first_under_integral_function, u_function.get_dividing_point(),
                                                      v_function.get_dividing_point());
        third_sum_component = integral_approximation(second_under_integral_function, u_function.get_dividing_point(),
                                                     v_function.get_dividing_point());
    } else if(u_function.getLeftBound() == v_function.getLeftBound()) {
        // u and v are the same function
        second_sum_component = integral_approximation(first_under_integral_function, u_function.getLeftBound(),
                                                      u_function.get_dividing_point());
        second_sum_component += integral_approximation(first_under_integral_function, u_function.get_dividing_point(),
                                                       u_function.getRightBound());

        third_sum_component = integral_approximation(second_under_integral_function, u_function.getLeftBound(),
                                                      u_function.get_dividing_point());
        third_sum_component += integral_approximation(second_under_integral_function, u_function.get_dividing_point(),
                                                       u_function.getRightBound());
    }

    return first_sum_component + second_sum_component - third_sum_component;
}

double L_mapping_value(const BSplineFunction& v_function) {
    // Hardcoded like above
    SineFunction sine = SineFunction();
    std::vector<std::shared_ptr<Function>> function_components;

    function_components.emplace_back(std::make_shared<BSplineFunction>(v_function));
    function_components.emplace_back(std::make_shared<SineFunction>(sine));

    FunctionProduct function_product = FunctionProduct(function_components);

    double left_bound = std::max(LEFT_BOUND, v_function.getLeftBound());
    double right_bound = std::min(RIGHT_BOUND, v_function.getRightBound());

    return integral_approximation(function_product, left_bound, v_function.get_dividing_point()) +
    integral_approximation(function_product, v_function.get_dividing_point(), right_bound);
}

void solve(int number_of_parts) {
    // In this problem the first testing function
    // will always have a zero coefficient
    int number_of_functions = number_of_parts;

    // Dividing the problem domain
    double domain_length = RIGHT_BOUND - LEFT_BOUND;
    double step = domain_length / number_of_parts;

    // Creating the test functions
    std::vector <BSplineFunction> functions;
    double current_left_bound = LEFT_BOUND;
    double current_dividing_point = LEFT_BOUND + step;
    double current_right_bound = current_dividing_point + step;

    for(int i = 0; i < number_of_functions; i++) {
        functions.emplace_back(current_left_bound, current_dividing_point, current_right_bound);
        current_left_bound = current_dividing_point;
        current_dividing_point = current_right_bound;
        current_right_bound += step;
    }

    // Calculating the matrix coefficients
    MatrixXd coefficients_matrix(number_of_functions, number_of_functions);

    for(int i = 0; i < number_of_functions; i++) {
        for(int j = 0; j < number_of_functions; j++) {
            coefficients_matrix(j, i) = B_mapping_value(functions[j], functions[i]);
        }
    }

    std::cout << "Coefficients matrix \n" << coefficients_matrix << std::endl;
    std::cout << std::endl;

    // Calculating the coefficients vector
    VectorXd l_mapping_values(coefficients_matrix.rows());

    for(int i = 0; i < coefficients_matrix.rows(); i++) {
        l_mapping_values(i) = L_mapping_value(functions[i]);
    }

    std::cout << "L mapping values: \n" << l_mapping_values << std::endl;
    std::cout << std::endl;

    VectorXd solution = solve_equation(coefficients_matrix, l_mapping_values);
    std::cout << "Solution: \n" << solution << std::endl;
}