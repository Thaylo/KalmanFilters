#include "ChargedParticleMatrixGenerator.h"

#define POSITIONNOISE 0.001
#define MEASURENOISE 0.05



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

    processNoiseStdDev[0][0] = POSITIONNOISE/2;
    processNoiseStdDev[1][0] = (POSITIONNOISE/2)*dt;

    return processNoiseStdDev;
}



/*------------------------------------------------------------------------------------------------*/
Matrix<double>
ChargedParticleMatrixGenerator::getV()
{
    Matrix<double>measurementNoiseStdDev(1,1);

    measurementNoiseStdDev[0][0] = MEASURENOISE;

    return measurementNoiseStdDev;
}



/*------------------------------------------------------------------------------------------------*/
Matrix<double>
ChargedParticleMatrixGenerator::getQ()
{
    Matrix<double>Q(2,2);
    
    Q[0][0] = pow(POSITIONNOISE, 2);
    Q[1][1] = pow((POSITIONNOISE/2)/dt, 2);
    
    return Q;
}



/*------------------------------------------------------------------------------------------------*/
Matrix<double>
ChargedParticleMatrixGenerator::getR()
{
    Matrix<double>R(1,1);
    
    R[0][0] = pow(MEASURENOISE, 2);
    
    return R;
}


