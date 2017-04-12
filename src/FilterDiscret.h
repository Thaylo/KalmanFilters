#ifndef FILTERDISCRET_H
#define FILTERDISCRET_H

#include "Filter.h"

class FilterDiscret :  public Filter
{

protected:
	Matrix<double> currentState;	

public:
	
	FilterDiscret(int dim)
	{
		dimensions = dim;
		currentState = Matrix<double>(dim, 1);
	};


	/*--------------------------------------------------------------------------------------------*/
	void
	inputValue(std::list<Matrix<double>> &inputList)
	{
		performFiltering(inputList);
	};



	/*--------------------------------------------------------------------------------------------*/
	virtual void readValue(Matrix<double> &ret) = 0;

};


#endif /* FILTERDISCRET_H */