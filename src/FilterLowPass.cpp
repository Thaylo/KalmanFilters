#include "FilterLowPass.h"



/*------------------------------------------------------------------------------------------------*/
void
FilterLowPass::performFiltering(vector<float> &input)
{
	for(int i = 0; i < dimensions; ++i)
	{
		currentState[i] = currentState[i] * alpha + input[i] * (1-alpha); 
	}
}



