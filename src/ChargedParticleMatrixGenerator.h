#ifndef CPMG_H
#define CPMG_H

#include "MatrixUtils.h"

class ChargedParticleMatrixGenerator
{
private:
    double dt;

public:
    ChargedParticleMatrixGenerator(double timeStep = 1.0);
    Matrix<double> getA();
    Matrix<double> getB();
    Matrix<double> getC();
    Matrix<double> getW();
    Matrix<double> getV();
    Matrix<double> getQ();
    Matrix<double> getR();
};

#endif /* CPMG_H */
