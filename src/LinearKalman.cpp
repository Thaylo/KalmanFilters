#include "LinearKalman.h"



/*------------------------------------------------------------------------------------------------*/
void
LinearKalman::performFiltering(vector<float> &input)
{
	float alpha = 0.8f;
	
	for(int i = 0; i < A.getNumberOfColumns(); ++i)
	{
		currentState[i] = currentState[i] * alpha + input[i] * (1-alpha); 
	}
}



/*------------------------------------------------------------------------------------------------*/
void
LinearKalman::preditionStep(Matrix<float> previousMean, Matrix<float> U, Matrix<float> Sigma, 
						 Matrix<float> R, Matrix<float> &predictedMean, Matrix<float> &updatedSigma)
{
	predictedMean = A*previousMean + B*U;
	updatedSigma = A*Sigma*A.transpose() + R;
}



/*------------------------------------------------------------------------------------------------*/
void
LinearKalman::correctionStep(Matrix<float> predictedMean, Matrix<float> updatedSigma, 
	  Matrix<float> Z, Matrix<float> Q, Matrix<float> &correctedMean, Matrix<float> &correctedSigma)
{
	Matrix<float> Ctrans(C.transpose());

	Matrix<float> K = updatedSigma*Ctrans*(C*updatedSigma*Ctrans + Q).computeInverseBySolver();
	correctedMean = predictedMean + K*(Z - C*predictedMean);
	auto aux = K * C;
	auto I = aux.identityMatrix(aux.getNumberOfColumns()); // Implementar eye(dim) igual ao matlab.
	correctedSigma = (I - aux) * updatedSigma;
}