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
DiscreteSystem::iterate(Matrix<double> U)
{
	X = A*X + B*U;
	Z = C*X;
}



/*-----------------------------------------------------------------------------------------------_*/
Matrix<double>
DiscreteSystem::observe()
{
	return Z;
}


/*-----------------------------------------------------------------------------------------------_*/
list<Matrix<double>>
DiscreteSystem::logIterations(list<Matrix<double>> U)
{
	list<Matrix<double>> outputs;

	outputs.push_back(observe());

	for(auto u : U)
	{
		this->iterate(u);
		outputs.push_back(observe());
	}

	return outputs;
}