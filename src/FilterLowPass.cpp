#include "FilterLowPass.h"



/*------------------------------------------------------------------------------------------------*/
void
FilterLowPass::performFiltering(std::list<Matrix<double>> &inputList)
{
	auto input = inputList.front();
	for(int i = 0; i < input.getNumberOfRows(); ++i)
	{
		currentState[i][0] = currentState[i][0] * alpha + input[i][0] * (1-alpha); 
	}
}



