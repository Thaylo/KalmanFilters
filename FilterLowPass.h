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

	void performFiltering(vector<float> &input);
};


#endif /* FILTERLOWPASS */