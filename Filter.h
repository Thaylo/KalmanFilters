#ifndef FILTER_H
#define FILTER_H

#include "VectorUtils.h"

class Filter
{
protected:
	int dimensions;
public:

	virtual void setDimensionality(int dim)
	{
		dimensions = dim;
	}
	virtual void performFiltering(vector<float> &inputValues) = 0;
	virtual void inputValue(vector<float> &value) = 0;
	virtual void readValue(vector<float> &ret) = 0;

};


#endif /* FILTER_H */