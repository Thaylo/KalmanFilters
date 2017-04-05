#include "FilterLowPass.h"


FilterLowPass::FilterLowPass()
{
	alpha = 0.5f;
	dimensions = 3;
	timeStep = 0.1f;

	for(int i = 0; i < dimensions; ++i)
	{
		currentState.push_back(0.0f);
	}
}



void
FilterLowPass::performFiltering(vector<float> &input)
{
	for(int i = 0; i < dimensions; ++i)
	{
		currentState[i] = currentState[i] * alpha + input[i] * (1-alpha); 
	}
}

float
FilterLowPass::getTimeStep()
{
	return timeStep;
}

void
FilterLowPass::setTimeStep(float value)
{
	timeStep = value;
}

void
FilterLowPass::inputValue(vector<float> &value)
{
	performFiltering(value);
}

void
FilterLowPass::readValue(vector<float> &ret)
{
	ret = currentState; 
}