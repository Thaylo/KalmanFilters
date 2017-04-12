#ifndef FILTERLOWPASS
#define FILTERLOWPASS

#include "FilterDiscret.h"

class  FilterLowPass : public FilterDiscret
{

protected:

	double alpha; // smoothness
    void performFiltering(std::list<Matrix<double>> &inputList);
    
public:
	
	FilterLowPass(int dim = 1, double alphaValue = 0.5) : FilterDiscret(dim)
	{
		alpha = alphaValue;
	}

	

	virtual void readValue(Matrix<double> &ret)
	{
		ret = currentState;
	}

};


#endif /* FILTERLOWPASS */