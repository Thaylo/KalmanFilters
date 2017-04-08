#ifndef FILTERDISCRET_H
#define FILTERDISCRET_H

#include "Filter.h"

class FilterDiscret :  public Filter
{

protected:
	Matrix<float> currentState;	

public:
	
	FilterDiscret(int dim)
	{
		dimensions = dim;
		currentState = Matrix<float>(dim, 1);
	};


	/*--------------------------------------------------------------------------------------------*/
	void
	inputValue(std::list<Matrix<float>> &inputList)
	{
		performFiltering(inputList);
	};



	/*--------------------------------------------------------------------------------------------*/
	virtual void readValue(Matrix<float> &ret) = 0;

};


#endif /* FILTERDISCRET_H */