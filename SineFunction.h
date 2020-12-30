#ifndef ACOUSTIC_VIBRATIONS_SOLVER_SINEFUNCTION_H
#define ACOUSTIC_VIBRATIONS_SOLVER_SINEFUNCTION_H


#include "Function.h"

// Simple container for the sine function
class SineFunction : public Function{
public:
    double value_at_point(double point) const override;
};


#endif //ACOUSTIC_VIBRATIONS_SOLVER_SINEFUNCTION_H
