#ifndef LINEARKALMAN
#define LINEARKALMAN

#include "FilterDiscret.h"
#include "MatrixUtils.h"

using namespace std;

class  LinearKalman : public FilterDiscret
{

protected:

	/*
		General discrete dynamics formulation:

		Equation for state evolution:
		X(k) = A(k) X(k-1) + B(k) U(k) + epsilon(k)

		Equation for state observation:
		Z(k) = C(k) X(k) + delta(k)

			Note that:
			1) epsilon and delta represents movement and measurement
		noise that are assumed to be independent and NORMALY DISTRIBUTED with
		covariance R(t) and Q(t) respectively.
			2) Given a state X, you will have a mean and a covariance matrix P,
			namely SIGMA. To the best of our knowledge, 'P' stands for state covariance.


	*/
	bool lowPassMode;
	Matrix<double> A; // A(nxn) describes how X(k) evolves from X(k-1) without inputs.
	Matrix<double> B; // B(nxl) describes how the control Uk changes the state from k-1 to k. 
	Matrix<double> C; // C(kxl) describes how to map the state X(k) to an observation Z(k).
	

	Matrix<double> Q; // Q(lxl) is the covariance matrix of observation noise.
	Matrix<double> R; // R(nxn) os tke covariance matrix of state evolution noise.
	Matrix<double> Sigma; // Sigma(nxn) State covariance, sometimes called P

    void performFiltering(list<Matrix<double>> &inputList);
    
public:

	LinearKalman( Matrix<double> initialState, Matrix<double> A_matrix, Matrix<double> B_matrix, 
							Matrix<double> C_matrix, Matrix<double> Q_matrix, Matrix<double> R_matrix) 
	: FilterDiscret(A_matrix.getNumberOfRows())
	{
		currentState = initialState;
		A = A_matrix;
		B = B_matrix;
		C = C_matrix;
		Q = Q_matrix;
		R = R_matrix;
        Sigma = Q;
	};

    

    void inputValue(list<Matrix<double>> &inputList);

    void readValue(Matrix<double> &zk);

    void preditionStep(Matrix<double> U, Matrix<double> R, Matrix<double> &predictedMean,
                                                                      Matrix<double> &updatedSigma);

    void correctionStep(Matrix<double> predictedMean, Matrix<double> predictedSigma,
                                                                Matrix<double> z, Matrix<double> Q);
};


#endif /* LINEARKALMAN */
