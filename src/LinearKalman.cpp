#include "LinearKalman.h"


/*------------------------------------------------------------------------------------------------*/
void
LinearKalman::performFiltering(list<Matrix<double>> &inputList)
{
    common_assert(inputList.size() == 2);

    auto u = inputList.front(); 
    inputList.pop_front();

    auto z = inputList.front();
    inputList.pop_front();


    Matrix<double> predictedMean(dimensions, 1);
    Matrix<double> predictedSigma(dimensions, dimensions);


    preditionStep(u, R, predictedMean, predictedSigma);
    correctionStep(predictedMean, predictedSigma, z, Q);
    
}



/*------------------------------------------------------------------------------------------------*/
void
LinearKalman::inputValue(list<Matrix<double>> &inputList)
{
	performFiltering(inputList);
}



/*------------------------------------------------------------------------------------------------*/
void
LinearKalman::readValue(Matrix<double> &zk)
{
    zk = C*currentState;
}



/*------------------------------------------------------------------------------------------------*/
void
LinearKalman::preditionStep(Matrix<double> U, Matrix<double> R, Matrix<double> &predictedMean, 
																	 Matrix<double> &predictedSigma)
{
	predictedMean = A*currentState + B*U;
	predictedSigma = A*Sigma*A.transpose() + Q;
}



/*------------------------------------------------------------------------------------------------*/
void
LinearKalman::correctionStep(Matrix<double> predictedMean, Matrix<double> predictedSigma, 
	  															 Matrix<double> z, Matrix<double> Q)
{

	Matrix<double> Ct(C.transpose());


	Matrix<double> K = predictedSigma*Ct*(C*predictedSigma*Ct + R).computeInverseBySolver();


	currentState = predictedMean + K*(z - C*predictedMean); // Correct State
	auto KC = K * C;
	auto I = KC.identityMatrix(KC.getNumberOfColumns()); // Implementar eye(dim) igual ao matlab.
	Sigma = (I - KC) * predictedSigma; // Correct Sigma
}