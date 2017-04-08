#include "LinearKalman.h"



/*------------------------------------------------------------------------------------------------*/
void
LinearKalman::performFiltering(list<Matrix<float>> &inputList)
{
	if (inputList.size() == 1)
	{
		lowPassMode = true;
		// Performs lowpass filter as fallback.
		auto u = inputList.front();
		float alpha = 0.2; // stup
		for(int i = 0; i < u.getNumberOfRows(); ++i)
		{
			currentState[i][0] = currentState[i][0] * alpha + u[i][0] * (1-alpha); 
		}	
	}
	else 
	{
		common_assert(inputList.size() == 2);

		lowPassMode = false;
		auto u = inputList.front();
		auto z = inputList.back();

		Matrix<float> predictedMean(dimensions, 0);
		Matrix<float> predictedSigma(dimensions, dimensions);

		preditionStep(u, R, predictedMean, predictedSigma);
		correctionStep(predictedMean, predictedSigma, z, Q);
	}
	
}



/*------------------------------------------------------------------------------------------------*/
void
LinearKalman::inputValue(list<Matrix<float>> &inputList)
{
	performFiltering(inputList);
}



/*------------------------------------------------------------------------------------------------*/
void
LinearKalman::readValue(Matrix<float> &zk)
{
	if(lowPassMode)
	{
		zk = currentState;
	}
	else
	{
		zk = C*currentState;
	}
	
}



/*------------------------------------------------------------------------------------------------*/
void
LinearKalman::preditionStep(Matrix<float> U, Matrix<float> R, Matrix<float> &predictedMean, 
																		Matrix<float> &updatedSigma)
{
	predictedMean = A*currentState + B*U;
	updatedSigma = A*Sigma*A.transpose() + R;
}



/*------------------------------------------------------------------------------------------------*/
void
LinearKalman::correctionStep(Matrix<float> predictedMean, Matrix<float> predictedSigma, 
	  															   Matrix<float> z, Matrix<float> Q)
{
	Matrix<float> Ct(C.transpose());

	Matrix<float> K = predictedSigma*Ct*(C*predictedSigma*Ct + Q).computeInverseBySolver();
	currentState = predictedMean + K*(z - C*predictedMean); // Correct State
	auto aux = K * C;
	auto I = aux.identityMatrix(aux.getNumberOfColumns()); // Implementar eye(dim) igual ao matlab.
	Sigma = (I - aux) * predictedSigma; // Correct Sigma
}