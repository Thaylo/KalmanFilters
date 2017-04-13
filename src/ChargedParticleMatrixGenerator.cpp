#include "ChargedParticleMatrixGenerator.h"

#define POSITIONNOISESTDEV 0.002
#define SPEEDNOISESTDDEV 0.001
#define MEASURENOISESTDDEV 0.04



/*------------------------------------------------------------------------------------------------*/
ChargedParticleMatrixGenerator::ChargedParticleMatrixGenerator(double timeStep)
{
    dt = timeStep;
}



/*------------------------------------------------------------------------------------------------*/
Matrix<double>
ChargedParticleMatrixGenerator::getA()
{
    Matrix<double> A(2,2);

    A[0][0] = 1;
    A[0][1] = dt;
    A[1][0] = 0;
    A[1][1] = 1;

    return A;
}



/*------------------------------------------------------------------------------------------------*/
Matrix<double>
ChargedParticleMatrixGenerator::getX0()
{
    Matrix<double> X0(2,1);

    X0[0][0] = 0.1;

    return X0;
}



/*------------------------------------------------------------------------------------------------*/
Matrix<double>
ChargedParticleMatrixGenerator::getB()
{
    Matrix<double> B(2,1);

    B[0][0] = dt * dt / 2;
    B[1][0] = dt;

    return B;
}



/*------------------------------------------------------------------------------------------------*/
Matrix<double>
ChargedParticleMatrixGenerator::getC()
{
    Matrix<double> C(1,2);

    C[0][0] = 1;
    C[0][1] = 0;

    return C;
}



/*------------------------------------------------------------------------------------------------*/
Matrix<double>
ChargedParticleMatrixGenerator::getW()
{
    Matrix<double>processNoiseStdDev(2,1);

    processNoiseStdDev[0][0] = POSITIONNOISESTDEV;
    processNoiseStdDev[1][0] = SPEEDNOISESTDDEV;

    return processNoiseStdDev;
}



/*------------------------------------------------------------------------------------------------*/
Matrix<double>
ChargedParticleMatrixGenerator::getV()
{
    Matrix<double>measurementNoiseStdDev(1,1);

    measurementNoiseStdDev[0][0] = MEASURENOISESTDDEV;

    return measurementNoiseStdDev;
}



/*------------------------------------------------------------------------------------------------*/
Matrix<double>
ChargedParticleMatrixGenerator::getQ()
{
    Matrix<double>Q(2,2);

    Q[0][0] = pow(POSITIONNOISESTDEV, 2);
    Q[1][1] = pow(SPEEDNOISESTDDEV, 2);

    return Q;
}



/*------------------------------------------------------------------------------------------------*/
Matrix<double>
ChargedParticleMatrixGenerator::getR()
{
    Matrix<double>R(1,1);

    R[0][0] = pow(MEASURENOISESTDDEV, 2);

    return R;
}


