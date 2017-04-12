#ifndef DISCRETELTISYS_H
#define DISCRETELTISYS_H

#include "MatrixUtils.h"
#include "ProbabilityDistributions.h"
#include <list>

using namespace std;

class DiscreteLTISystem
{
protected:

	Matrix<double> A; // A(nxn) describes how X(k) evolves from X(k-1) without inputs.
	Matrix<double> B; // B(nxl) describes how the control Uk changes the state from k-1 to k. 
	Matrix<double> C; // C(kxl) describes how to map the state X(k) to an observation Z(k).

	Matrix<double> X; // System state
    Matrix<double> X0; // System initial state

	Matrix<double> Z; // System observable variables

public:

    DiscreteLTISystem();
    DiscreteLTISystem(const Matrix<double> &A_value, const Matrix<double> &B_value, 
                                     const Matrix<double> &C_value, const Matrix<double> &X0_value);

    void resetSystemState();
	virtual void evolve(const Matrix<double> &U);
	virtual Matrix<double> observe();
	list<Matrix<double>> logSystemStates(list<Matrix<double>> &U);
    list<Matrix<double>> logSystemMeasures(list<Matrix<double>> &states);
};

void DiscreteLTISystemTest();


#endif /* DISCRETELTISYS_H */