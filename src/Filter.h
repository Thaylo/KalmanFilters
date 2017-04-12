#ifndef FILTER_H
#define FILTER_H

#include "MatrixUtils.h"
#include <list>

class Filter
{
protected:
	int dimensions;
	virtual void performFiltering(std::list<Matrix<double>> &inputList) = 0;

public:

	virtual int getDimensionality()
	{
		return dimensions;
	};

	virtual void inputValue(std::list<Matrix<double>> &inputList) = 0;
	virtual void readValue(Matrix<double> & z) = 0;

};


#endif /* FILTER_H */