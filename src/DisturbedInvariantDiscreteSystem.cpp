#include "DisturbedInvariantDiscreteSystem.h"
#include "ChargedParticleMatrixGenerator.h"

/*------------------------------------------------------------------------------------------------*/
void
DisturbedInvariantDiscreteSystem::configureSystem(const Matrix<double> &A_value,
       const Matrix<double> &B_value, const Matrix<double> &C_value, const Matrix<double> &X0_value,
                             const Matrix<double> WstdDev_value, const Matrix<double> VstdDev_value)
{
    A = A_value;
    B = B_value;
    C = C_value;

    X0 = X0_value;
    X = X0_value;
    Z = C*X0;

    WstdDev = WstdDev_value;
    VstdDev = VstdDev_value;
}


/*------------------------------------------------------------------------------------------------*/
void
DisturbedInvariantDiscreteSystem::evolve(const Matrix<double> &U)
{
    int numRows = WstdDev.getNumberOfRows();
    int numColumns = WstdDev.getNumberOfColumns();
    Matrix<double> noise(numRows, numColumns);

    for(int i = 0; i < numRows; ++i)
    {
        for(int j = 0; j < numColumns; ++j)
        {
            noise[i][j] = centeredNormal(WstdDev[i][j]);
        }
    }

    X = A * X + B * U + noise;
}



/*-----------------------------------------------------------------------------------------------_*/
Matrix<double>
DisturbedInvariantDiscreteSystem::observe()
{
    int numRows = VstdDev.getNumberOfRows();
    int numColumns = VstdDev.getNumberOfColumns();
    auto noise = Matrix<double>(numRows, numColumns);

    for(int i = 0; i < numRows; ++i)
    {
        for(int j = 0; j < numColumns; ++j)
        {
            noise[i][j] = centeredNormal(VstdDev[i][j]);
        }
    }

    Z = C * X + noise;

	return Z;
}


/*-----------------------------------------------------------------------------------------------_*/
Matrix<double>
DisturbedInvariantDiscreteSystem::observe(Matrix<double> &state)
{
    int numRows = VstdDev.getNumberOfRows();
    int numColumns = VstdDev.getNumberOfColumns();
    auto noise = Matrix<double>(numRows, numColumns);

    for(int i = 0; i < numRows; ++i)
    {
        for(int j = 0; j < numColumns; ++j)
        {
            noise[i][j] = centeredNormal(VstdDev[i][j]);
        }
    }

    return C * state + noise;
}


list<Matrix<double>>
DisturbedInvariantDiscreteSystem::logSystemStates(list<Matrix<double>> &U)
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
DisturbedInvariantDiscreteSystem::logSystemMeasures(list<Matrix<double>> &states)
{
    list<Matrix<double>> measures;

    for( auto e : states)
    {
        measures.push_back(this->observe(e));
    }

    return measures;
}


/*-----------------------------------------------------------------------------------------------_*/
void
DisturbedInvariantDiscreteSystemTest()
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

    DisturbedInvariantDiscreteSystem sys;
    sys.configureSystem(A,B,C,X0,W,V);

    auto realPositions = sys.logSystemStates(inputs);
	auto measuredPositions = sys.logSystemMeasures(realPositions);


    //cout << "graphics_toolkit(\"gnuplot\");\n";
    int cnt = 0;
    cout << "z = [";
    for( auto e : realPositions)
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

    cnt = 0;
    cout << "zDisturbed = [";
    for( auto e : measuredPositions)
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

    cout << "plot(t,z, \"--\");\nhold on;\nplot3(t,zDisturbed, \"-.\")\n";
    cout << "legend(\"Posicao da particula\")\n";
    cout << "print -dpdf foo.pdf";

}