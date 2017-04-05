#ifndef FILTERDISCRET_H
#define FILTERDISCRET_H

#include "Filter.h"

class FilterDiscret :  public Filter
{

protected:
	vector<float> currentState;	

public:
	
	FilterDiscret(int dim)
	{
		dimensions = dim;
		for(int i = 0; i < dimensions; ++i)
		{
			currentState.push_back(0.0f);
		}
	}


	/*--------------------------------------------------------------------------------------------*/
	void
	inputValue(vector<float> &value)
	{
		performFiltering(value);
	}



	/*--------------------------------------------------------------------------------------------*/
	void readValue(vector<float> &ret)
	{
		ret = currentState; 
	}

};


#endif /* FILTERDISCRET_H */