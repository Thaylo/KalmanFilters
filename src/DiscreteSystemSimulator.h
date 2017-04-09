#ifndef DISCRETESYSTEMSIM_H
#define DISCRETESYSTEMSIM_H

#include "MatrixUtils.h"
#include <list>

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

	void iterate(Matrix<double> U);
	Matrix<double> observe();
	std::list<Matrix<double>> logIterations(std::list<Matrix<double>> U);
};

#endif /* DISCRETESYSTEMSIM_H */