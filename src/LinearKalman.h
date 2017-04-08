#ifndef LINEARKALMAN
#define LINEARKALMAN

#include "FilterDiscret.h"
#include "MatrixUtils.h"

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

	Matrix<float> A; // A(nxn) describes how X(k) evolves from X(k-1) without inputs.
	Matrix<float> B; // B(nxl) describes how the control Uk changes the state from k-1 to k. 
	Matrix<float> C; // C(kxl) describes how to map the state X(k) to an observation Z(k).
	

	Matrix<float> Q; // Q(lxl) is the covariance matrix of observation noise.
	Matrix<float> R; // R(nxn) os tke covariance matrix of state evolution noise.
	Matrix<float> S; // Is 'S(lxn) or transposed' the Cross-covariance of all noise?

public:

	LinearKalman( Matrix<float> A_matrix, Matrix<float> B_matrix, Matrix<float> C_matrix,
				  Matrix<float> Q_matrix, Matrix<float> R_matrix, Matrix<float> S_matrix) 
	: FilterDiscret(3)
	{
		A = A_matrix;
		B = B_matrix;
		C = C_matrix;
		Q = Q_matrix;
		R = R_matrix;
		S = S_matrix;
	};

	LinearKalman() : FilterDiscret(1)
	{
		A = Matrix<float>(1,1);
		B = Matrix<float>(1,1);
		C = Matrix<float>(1,1);
		Q = Matrix<float>(1,1);
		R = Matrix<float>(1,1);
		S = Matrix<float>(1,1);
	};

	void performFiltering(vector<float> &input);

	void preditionStep(Matrix<float> previousMean, Matrix<float> U, Matrix<float> Sigma, 
						Matrix<float> R, Matrix<float> &predictedMean, Matrix<float> &updatedSigma);

	void correctionStep(Matrix<float> predictedMean, Matrix<float> updatedSigma, 
	 Matrix<float> Z, Matrix<float> Q, Matrix<float> &correctedMean, Matrix<float> &correctedSigma);

};


#endif /* LINEARKALMAN */
