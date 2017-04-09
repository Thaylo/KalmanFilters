#ifndef DISCRETESYSTEMSIM_H
#define DISCRETESYSTEMSIM_H

#include "MatrixUtils.h"
#include "ProbabilityDistributions.h"
#include <list>

using namespace std;

class DiscreteSystem 
{
private:

	Matrix<double> A; // A(nxn) describes how X(k) evolves from X(k-1) without inputs.
	Matrix<double> B; // B(nxl) describes how the control Uk changes the state from k-1 to k. 
	Matrix<double> C; // C(kxl) describes how to map the state X(k) to an observation Z(k).
	Matrix<double> X; // System state
	Matrix<double> Z; // System observable variables

public:

	DiscreteSystem(Matrix<double> A_value, Matrix<double> B_value, Matrix<double> C_value, 
																				 Matrix<double> X0);

	void iterate(Matrix<double> U, bool isDisturbed, Matrix<double> noiseScale, double stdDev);
	Matrix<double> observe(bool isDisturbed, Matrix<double> noiseScale, double stdDev);
	list<Matrix<double>> logIterations(list<Matrix<double>> U, bool processDisturbed,
										  		Matrix<double> processNoiseScale, double stdDevProc, 
			 bool measurementDisturbed, Matrix<double> measurementNoiseScale, double stdDevMeasure); 
};

void DiscreteSystemTest();

#endif /* DISCRETESYSTEMSIM_H */