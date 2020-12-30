#ifndef ACOUSTIC_VIBRATIONS_SOLVER_FUNCTION_H
#define ACOUSTIC_VIBRATIONS_SOLVER_FUNCTION_H


class Function {
public:
    virtual double value_at_point(double point) const = 0;
};


#endif //ACOUSTIC_VIBRATIONS_SOLVER_FUNCTION_H
