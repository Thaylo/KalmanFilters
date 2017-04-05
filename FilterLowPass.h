#ifndef FILTERLOWPASS
#define FILTERLOWPASS

#include "FilterDiscret.h"

class  FilterLowPass : public FilterDiscret
{

protected:

	float alpha; // smoothness

	vector<float> currentState;

	void performFiltering(vector<float> &input);

public:
	
	FilterLowPass();
	void  setTimeStep(float value);
	float getTimeStep();
	void inputValue(vector<float> &value);
	void readValue(vector<float> &ret);
};


#endif /* FILTERLOWPASS */