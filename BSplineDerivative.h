#ifndef ACOUSTIC_VIBRATIONS_SOLVER_BSPLINEDERIVATIVE_H
#define ACOUSTIC_VIBRATIONS_SOLVER_BSPLINEDERIVATIVE_H


class BSplineDerivative : public Function {
private:
    double left_bound;
    double dividing_point;
    double right_bound;
public:
    BSplineDerivative(double left_bound, double dividing_point, double right_bound);

    double value_at_point(double point) const override;

    double getDividingPoint() const;

    double getLeftBound() const;

    double getRightBound() const;
};


#endif //ACOUSTIC_VIBRATIONS_SOLVER_BSPLINEDERIVATIVE_H
