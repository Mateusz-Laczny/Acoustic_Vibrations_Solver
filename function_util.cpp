#include <fstream>
#include <iostream>
#include "function_util.h"

Eigen::VectorXd solve_equation(const Eigen::MatrixXd& matrix, const Eigen::VectorXd& l_mapping_values) {
    Eigen::VectorXd solution(matrix.rows());
    solution = matrix.colPivHouseholderQr().solve(l_mapping_values);

    return solution;
}

/*
 * Function approximating the integral
 * using the Gauss-Legendre quadrature with 3 points
 */
double integral_approximation(const Function& function, double left_bound, double right_bound) {
    // Constants for integral approximation
    const double GAUSS_QUADRATURE_STEP = sqrt(3.0/5.0);
    const double ZERO_POINT_WEIGHT = 8.0/9.0;
    const double NON_ZERO_POINT_WEIGHT = 5.0/9.0;

    double approximation = 0.0;
    double domain_shift_coefficient = (right_bound - left_bound) / 2;
    double domain_shift_constant = (left_bound + right_bound) / 2;

    approximation += ZERO_POINT_WEIGHT * function.value_at_point(0 * domain_shift_coefficient + domain_shift_constant);
    approximation += NON_ZERO_POINT_WEIGHT * function.value_at_point((-GAUSS_QUADRATURE_STEP) * domain_shift_coefficient + domain_shift_constant);
    approximation += NON_ZERO_POINT_WEIGHT * function.value_at_point((GAUSS_QUADRATURE_STEP) * domain_shift_coefficient + domain_shift_constant);

    approximation *= domain_shift_coefficient;
    return approximation;
}

void visualize(const Function& function, double left_range_bound, double right_range_bound) {
    const int NUMBER_OF_SAMPLE_POINTS = 1000;

    // Creating a .dat file
    std::string data_file_name = "plotpoints.dat";
    std::ofstream ofs(data_file_name.c_str());

    double step = (right_range_bound - left_range_bound) / NUMBER_OF_SAMPLE_POINTS;
    double current_point = left_range_bound;

    // Populating the file with 1000 sample points
    for(int i = 0; i < NUMBER_OF_SAMPLE_POINTS; i++) {
        ofs << "  " << current_point << "   " << function.value_at_point(current_point) << '\n';
        current_point += step;
    }

    ofs.close();
    if (!ofs) {
        perror(data_file_name.c_str());
        return;
    }

    // Creating a .plt file
    std::string commands_file_name = "plotcommands.plt";
    std::ofstream ofs2(commands_file_name.c_str());

    ofs2 << "unset key \n";
    ofs2 << "set term pngcairo size 1024,768 \n";
    ofs2 << "set output \'function_plot.png\' \n";
    ofs2 << "set xrange [" << left_range_bound << ":" << right_range_bound + 1 << "] \n";
    ofs2 << "plot \'plotpoints.dat\' linecolor -1 linewidth 2 with lines";

    ofs2.close();
    if (!ofs2) {
        perror(commands_file_name.c_str());
        return;
    }

    std::string command = "gnuplot " + commands_file_name;

    int res = system(command.c_str());

    if (res) {
        std::cerr << "  gnuplot seems to fail, return status=" << res << std::endl;
        return;
    }
}
