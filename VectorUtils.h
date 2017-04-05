#ifndef VECTORUTILS_H
#define VECTORUTILS_H

#include <vector>
#include <list>


using namespace std;

void displayVector( vector<float> v );
vector<float> vectorFromList( list<float> l);
float vectorSquaredNorm(vector<float> x);
float vectorMulByScalar(vector<float> &x, float factor);
vector<float> generateVector(float values[], int sz);
vector<float> generateVector(int sz);


#endif /* VECTORUTILS_H */