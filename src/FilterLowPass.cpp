#include "FilterLowPass.h"



/*------------------------------------------------------------------------------------------------*/
void
FilterLowPass::performFiltering(std::list<Matrix<float>> &inputList)
{
	auto input = inputList.front();
	for(int i = 0; i < input.getNumberOfRows(); ++i)
	{
		currentState[i][0] = currentState[i][0] * alpha + input[i][0] * (1-alpha); 
	}
}



