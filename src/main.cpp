#include "LinearKalman.h"
#include "MatrixUtils.h"
#include "DiscreteLTISystem.h"
#include "DisturbedInvariantDiscreteSystem.h"
#include "ChargedParticleMatrixGenerator.h"
#include <list>

using namespace std;


/*------------------------------------------------------------------------------------------------*/
int
main(int argc, char **argv)
{

    int maxIter = 120;
    double timeStep = 1/30.0;
    double maxTime = maxIter*timeStep;

    double timeElapsed = 0;
    cout << "t = [";
    for( int i = 0; i < maxIter; ++i)
    {
        cout << timeElapsed;

        if(i < maxIter - 1)
        {
            cout << ", ";
        }
        else
        {
            cout << "];\n\n";
        }

        timeElapsed += timeStep;
    }



    ChargedParticleMatrixGenerator chargedParticleMatGenerator(timeStep);

    auto X0 = chargedParticleMatGenerator.getX0();
    auto A = chargedParticleMatGenerator.getA();
    auto B = chargedParticleMatGenerator.getB();
    auto C = chargedParticleMatGenerator.getC();
    auto W = chargedParticleMatGenerator.getW();
    auto V = chargedParticleMatGenerator.getV();
    auto Q = chargedParticleMatGenerator.getQ();
    auto R = chargedParticleMatGenerator.getR();

    DiscreteLTISystem ltiSys(A,B,C,X0);
    DisturbedInvariantDiscreteSystem disturbedSys;
    disturbedSys.configureSystem(A,B,C,X0,W,V);

    list<Matrix<double>> U;
    Matrix<double> u(1,1);

    for(int i = 0; i < maxIter; ++i)
    {
        u[0][0] = cos(4*M_PI*timeElapsed/maxTime);
        U.push_back(u);
        timeElapsed += timeStep;
    }

    auto realDisturbedStates = disturbedSys.logSystemStates(U);

    auto disturbedtMeasures = ltiSys.logSystemMeasures(realDisturbedStates);
    auto noisyMeasures = disturbedSys.logSystemMeasures(realDisturbedStates);

    LinearKalman KF(X0, A, B, C, Q, R);
    list<Matrix<double>> kalmanEstimatives;
    list<Matrix<double>> outputFromKalmanFiltering;


    Matrix<double> Zret(2,1);
    list<Matrix<double>>::iterator uIt = U.begin();

    list<Matrix<double>> kInputs;


    for(list<Matrix<double>>::iterator zIt = noisyMeasures.begin(); zIt != noisyMeasures.end();
                                                                                       zIt++, uIt++)
    {
        common_assert(uIt != U.end());
        kInputs.push_back(*uIt);
        kInputs.push_back(*zIt);

        KF.inputValue(kInputs);
        KF.readValue(Zret);

        outputFromKalmanFiltering.push_back(Zret);
    }

    int cnt = 0;
    cout << "disturbedtMeasures = [";
    for( auto e : disturbedtMeasures)
    {
        cnt++;
        cout << e[0][0];

        if(cnt < maxIter)
        {
            cout << ", ";
        }
        else
        {
            cout << "];\n\n";
        }
    }


    cout << "noisyMeasures = [" << endl;
    cnt = 0;
    for( auto e : noisyMeasures)
    {
        cnt++;
        cout << e[0][0];

        if(cnt < maxIter)
        {
            cout << ", ";
        }
        else
        {
            cout << "];\n\n";
        }
    }

    cout << "outputFromKalmanFiltering = [" << endl;
    cnt = 0;
    for( auto e : outputFromKalmanFiltering)
    {
        cnt++;
        cout << e[0][0];

        if(cnt < maxIter)
        {
            cout << ", ";
        }
        else
        {
            cout << "];\n\n";
        }
    }

    cout << "plot(t,disturbedtMeasures);\nhold on;\nplot3(t,noisyMeasures, \".\");\nplot3(t,outputFromKalmanFiltering, \"--\");\n";
    cout << "legend(\"Posicao real do objeto\", \"Posicao dada pelo sensor ruidoso\", \"Posicao estimada pelo Kalman Filter\");\n";
    cout << "print -dpdf particula.pdf\n";

    return 0;
}