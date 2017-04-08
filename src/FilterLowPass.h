#ifndef FILTERLOWPASS
#define FILTERLOWPASS

#include "FilterDiscret.h"

class  FilterLowPass : public FilterDiscret
{

protected:

	float alpha; // smoothness

public:
	
	FilterLowPass(int dim = 1, float alphaValue = 0.5) : FilterDiscret(dim)
	{
		alpha = alphaValue;
	}

	void performFiltering(std::list<Matrix<float>> &inputList);

	virtual void readValue(Matrix<float> &ret)
	{
		ret = currentState;
	}

};


#endif /* FILTERLOWPASS */