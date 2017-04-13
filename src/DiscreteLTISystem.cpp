#include "DiscreteLTISystem.h"

using namespace std;


/*-----------------------------------------------------------------------------------------------_*/
DiscreteLTISystem::DiscreteLTISystem()
{

}



/*-----------------------------------------------------------------------------------------------_*/
DiscreteLTISystem::DiscreteLTISystem(const Matrix<double> &A_value, const Matrix<double> &B_value,
                                      const Matrix<double> &C_value, const Matrix<double> &X0_value)
{
    A = A_value;
    B = B_value;
    C = C_value;

    X0 = X0_value;
    X = X0_value;
}



/*-----------------------------------------------------------------------------------------------_*/
void
DiscreteLTISystem::resetSystemState()
{
    X = X0;
}



/*-----------------------------------------------------------------------------------------------_*/
void
DiscreteLTISystem::evolve(const Matrix<double> &U)
{
	X = A*X + B*U;
}



/*-----------------------------------------------------------------------------------------------_*/
Matrix<double>
DiscreteLTISystem::observe()
{
	Z = C*X;
	return Z;
}



/*-----------------------------------------------------------------------------------------------_*/
list<Matrix<double>>
DiscreteLTISystem::logSystemStates(list<Matrix<double>> &U)
{
	list<Matrix<double>> outputs;
    Matrix<double> stub;

	for(auto u : U)
	{
		this->evolve(u);
		outputs.push_back(X);
	}

	return outputs;
}



/*-----------------------------------------------------------------------------------------------_*/
list<Matrix<double>>
DiscreteLTISystem::logSystemMeasures(list<Matrix<double>> &states)

{
	list<Matrix<double>> measures;

	for(auto s : states)
	{
		measures.push_back(C*s);
	}
	return measures;
}



/*-----------------------------------------------------------------------------------------------_*/
void
DiscreteLTISystemTest()
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


    DiscreteLTISystem sys(A,B,C,X0);
    auto states = sys.logSystemStates(inputs);
    auto measurements = sys.logSystemMeasures(states);

    int cnt = 0;
    cout << "z = [";
    for( auto e : measurements)
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

    cout << "plot(t,z, \"--\");\nhold on;\nplot3(t,z, \"-.\")\n";
    cout << "legend(\"Posicao da particula\")\n";
    cout << "print -dpdf particula.pdf";

}