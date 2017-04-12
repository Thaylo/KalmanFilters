#ifndef DISTURBEDINVARIANTDSYS_H
#define DISTURBEDINVARIANTDSYS_H

#include "DiscreteLTISystem.h"

class DisturbedInvariantDiscreteSystem: public DiscreteLTISystem
{
protected:

    Matrix<double> WstdDev; // Evolution noise
    Matrix<double> VstdDev; // Measurement noise

    

public:
    DisturbedInvariantDiscreteSystem(){};
    void configureSystem(const Matrix<double> &A_value, const Matrix<double> &B_value, 
                                      const Matrix<double> &C_value, const Matrix<double> &X0_value,
                                        const Matrix<double> WstdDev, const Matrix<double> VstdDev);

    Matrix<double> observe();
    void evolve(const Matrix<double> &U);
    list<Matrix<double>> logSystemStates(list<Matrix<double>> &U);
    list<Matrix<double>> logSystemMeasures(list<Matrix<double>> &states);
    Matrix<double> observe(Matrix<double> &state);
};

void DisturbedInvariantDiscreteSystemTest();

#endif /* DISTURBEDINVARIANTDSYS_H */