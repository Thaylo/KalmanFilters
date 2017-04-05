#ifndef FILTERDISCRET_H
#define FILTERDISCRET_H

#include "Filter.h"

class FilterDiscret :  public Filter
{

protected:
	float timeStep;

public:
	
	virtual void  setTimeStep(float value) = 0;
	virtual float getTimeStep() = 0;
};


#endif /* FILTERDISCRET_H */