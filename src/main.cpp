#include "LinearKalman.h"
#include "FilterLowPass.h"
#include "MatrixUtils.h"
#include "DiscreteLTISystem.h"
#include "DisturbedInvariantDiscreteSystem.h"
#include "ProbabilityDistributions.h"
#include "ChargedParticleMatrixGenerator.h"
#include <list>

using namespace std;



/*------------------------------------------------------------------------------------------------*/
int 
main(int argc, char **argv)
{

    int maxIter = 100;
    double timeStep = 1.34/maxIter;
    
    double timeElapsed = 0;
    cout << "t = [";
    for( int i = 0; i < maxIter+1; ++i)
    { 
        cout << timeElapsed;
        
        if(i < maxIter)
        {
            cout << ", ";
        }
        else
        {
            cout << "];\n\n";
        }

        timeElapsed += timeStep;
    }

    Matrix<double> U(1,1);
    U[0][0] = 1;

    list<Matrix<double>> inputs;
    for(int i = 0; i < maxIter; ++i)
    {
        inputs.push_back(U);
    }

    Matrix<double> X0(2,1);
    X0[0][0] = 0.1f;
    X0[1][0] = 0;

    ChargedParticleMatrixGenerator chargedParticleMatGenerator(timeStep);

    auto A = chargedParticleMatGenerator.getA();
    auto B = chargedParticleMatGenerator.getB();
    auto C = chargedParticleMatGenerator.getC();
    auto W = chargedParticleMatGenerator.getW();
    auto V = chargedParticleMatGenerator.getV();

    DiscreteLTISystem ltiSys(A,B,C,X0);

    DisturbedInvariantDiscreteSystem disturbedSys;
    disturbedSys.configureSystem(A,B,C,X0,W,V);
    
    auto realStates = disturbedSys.logSystemStates(inputs);
    auto disturbedtMeasures = ltiSys.logSystemMeasures(realStates);
    auto noisyMeasures = disturbedSys.logSystemMeasures(realStates);

    int cnt = 0;
    cout << "disturbedtMeasures = [";
    for( auto e : disturbedtMeasures)
    { 
        cnt++;
        cout << e[0][0];
        
        if(cnt < maxIter+1)
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
        
        if(cnt < maxIter+1)
        {
            cout << ", ";
        }
        else
        {
            cout << "];\n\n";
        }
    }

    cout << "plot(t,disturbedtMeasures);\nhold on;\nplot3(t,noisyMeasures, \"-.\")\n";
    cout << "legend(\"Posicao\", \"Posicao Medida\")\n";
    cout << "print -dpdf particula.pdf";

    return 0;    
}