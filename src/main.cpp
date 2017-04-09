#include "LinearKalman.h"
#include "FilterLowPass.h"
#include "MatrixUtils.h"
#include "DiscreteSystemSimulator.h"
#include <list>

using namespace std;



/*------------------------------------------------------------------------------------------------*/
int 
main(int argc, char **argv)
{

#if 0
    
    LinearKalman f;
    int dim = f.getDimensionality();

    Matrix<float> input(dim,1);
    input[0][0] = 1.0f;

    list<Matrix<float>> inputList;
    inputList.push_back(input);

    Matrix<float> output(dim,1);

    f.readValue(output);
    cout << "Out = " << output << "\n"; 

    for(int i = 0; i < 20; ++i)
    {
        f.inputValue(inputList);
        f.readValue(output);
        cout << "Out = " << output << "\n";
    }



    #define dim 100
    Matrix<double> A(dim,dim);
    Matrix<double> x(dim,1);
    Matrix<double> b(dim,1);

    for(int i = 0; i < dim; ++i)
    {
        x[i][0] = i;
        A[i][i] = 1.0;

        for(int j = 0; j < dim; ++j)
        {
            A[i][j] += 200;
        }
    }
    b = A*x;

    auto xBCGSTAB = A.Bicgstab(b);
    auto xCG = A.conjugateGradientSolver(b);
    
    cout << "A = " << A << "\n";
    cout << "b = " << b << "\n";
    cout << "xBCGSTAB = " << xBCGSTAB << "\n";
    cout << "xCG = " << xCG << "\n";

#else
    int maxIter = 40;
    double timeStep = 1.34/maxIter;
    

    Matrix<double> A(2,2);
    A[0][0] = 1;
    A[0][1] = timeStep;
    A[1][0] = 0;
    A[1][1] = 1;
    
    Matrix<double> B(2,1);
    B[0][0] = timeStep * timeStep / 2;
    B[1][0] = timeStep;

    Matrix<double> C(1,2);
    C[0][0] = 1;
    C[0][1] = 0;

    Matrix<double> X0(2,1);
    X0[0][0] = 0.1f;
    X0[1][0] = 0;

    Matrix<double> U(1,1);
    U[0][0] = 1;

    list<Matrix<double>> inputs;
    for(int i = 0; i < maxIter; ++i)
    {
        inputs.push_back(U);
    }

    DiscreteSystem sys(A,B,C,X0);

    auto outputs = sys.logIterations(inputs);
    list<double> time;

    
    double timeElapsed = 0;

    int cnt = 0;
    cout << "z = [";
    for( auto e : outputs)
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

        time.push_back(timeElapsed);
        timeElapsed += timeStep;
    }

    cnt = 0;
    cout << "t = [";
    for( auto timeStamp : time)
    { 
        cnt++;
        cout << timeStamp;
        
        if(cnt < maxIter+1)
        {
            cout << ", ";
        }
        else
        {
            cout << "];\n\nplot(z,t);";
        }
    }

#endif
    return 0;

    
}