#ifndef ACOUSTIC_VIBRATIONS_SOLVER_FUNCTION_UTIL_H
#define ACOUSTIC_VIBRATIONS_SOLVER_FUNCTION_UTIL_H

class Function;

double integral_approximation(Function function, double left_bound, double right_bound);

void solve(int number_of_parts);

#endif //ACOUSTIC_VIBRATIONS_SOLVER_FUNCTION_UTIL_H
