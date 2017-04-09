#include "DiscreteSystemSimulator.h"

using namespace std;

/*-----------------------------------------------------------------------------------------------_*/
DiscreteSystem::DiscreteSystem(Matrix<double> A_value, Matrix<double> B_value, 
											 			  Matrix<double> C_value, Matrix<double> X0)
{
	A = A_value;
	B = B_value;
	C = C_value;
	X = X0;
	Z = C*X0;

}



/*-----------------------------------------------------------------------------------------------_*/
void
DiscreteSystem::iterate(Matrix<double> U, bool isDisturbed, Matrix<double> noiseScale, 
																					  double stdDev)
{
	X = A*X + B*U;
	
	if(isDisturbed)
	{
		int numRows = noiseScale.getNumberOfRows(); 
		int numColumns = noiseScale.getNumberOfColumns(); 
		for(int i = 0; i < numRows; ++i)
		{
			for(int j = 0; j < numColumns; ++j)
			{
				noiseScale[i][j] *= centeredNormal(stdDev);
			}
		}
		X = X + noiseScale;
	}
}



/*-----------------------------------------------------------------------------------------------_*/
Matrix<double>
DiscreteSystem::observe(bool isDisturbed, Matrix<double> noiseScale, double stdDev)
{
	Z = C*X;

	if(isDisturbed)
	{
		int numRows = noiseScale.getNumberOfRows(); 
		int numColumns = noiseScale.getNumberOfColumns(); 
		
		for(int i = 0; i < numRows; ++i)
		{
			for(int j = 0; j < numColumns; ++j)
			{
				noiseScale[i][j] *= centeredNormal(stdDev);
			}
		}
		Z = Z + noiseScale;
	}

	return Z;
}



/*-----------------------------------------------------------------------------------------------_*/
list<Matrix<double>>
DiscreteSystem::logIterations(list<Matrix<double>> U, bool isProcDisturbed,
										  		Matrix<double> processNoiseScale, double stdDevProc, 
			    bool isMeasureDisturbed, Matrix<double> measurementNoiseScale, double stdDevMeasure) 
																		   
{
	list<Matrix<double>> outputs;

	outputs.push_back(observe(isMeasureDisturbed, measurementNoiseScale, stdDevMeasure));

	for(auto u : U)
	{
		this->iterate(u, isProcDisturbed, processNoiseScale, stdDevProc);
		outputs.push_back(observe(isMeasureDisturbed, measurementNoiseScale, stdDevMeasure));
	}

	return outputs;
}




/*-----------------------------------------------------------------------------------------------_*/
void
DiscreteSystemTest()
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

    Matrix<double>processNoiseScale(B);
    double processNoiseStdDev = 3;
    bool isprocessNoiseActive = true;

    Matrix<double>measureMentNoiseScale(1,1);
    measureMentNoiseScale[0][0] = 1;
	double measureMentNoiseStdDev = 0.1;

	bool isMeasurementNoiseActive = false;
    DiscreteSystem sys(A,B,C,X0);
    auto realPositions     = sys.logIterations(inputs, isprocessNoiseActive, processNoiseScale, 
       processNoiseStdDev, isMeasurementNoiseActive, measureMentNoiseScale, measureMentNoiseStdDev);

    isMeasurementNoiseActive = true;
    DiscreteSystem sys2(A,B,C,X0);
	auto measuredPositions = sys2.logIterations(inputs, isprocessNoiseActive, processNoiseScale, 
       processNoiseStdDev, isMeasurementNoiseActive, measureMentNoiseScale, measureMentNoiseStdDev);



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


    cout << "plot(t,z, '--');\nhold on;\nplot(t,zDisturbed, '-x')\n";

}
