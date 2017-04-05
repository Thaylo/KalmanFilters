#include "VectorUtils.h"
#include <iostream>

using namespace std;

/*------------------------------------------------------------------------------------------------*/
void
displayVector( vector<float> v )
{
    cout << "|";

    for(float e : v)
    {
        cout << e << "|";
    }
    cout << endl;
}



/*------------------------------------------------------------------------------------------------*/
vector<float>
vectorFromList( list<float> l)
{
    vector<float> v = vector<float>{l.begin(), l.end()};
    return v;
}



/*------------------------------------------------------------------------------------------------*/
inline float
vectorSquaredNorm(vector<float> x)
{
    float norm2 = 0.0f;
    for(int i = 0; i < x.size(); ++i)
    {
        norm2 += x[i] * x[i];
    }
    return norm2;
}



/*------------------------------------------------------------------------------------------------*/
float
vectorMulByScalar(vector<float> &x, float factor)
{
    float norm2 = 0.0f;
    for(int i = 0; i < x.size(); ++i)
    {
        x[i] /= factor;;
    }
    return norm2;
}



/*------------------------------------------------------------------------------------------------*/
vector<float>
generateVector(float values[], int sz)
{
    vector<float> v;
    for(int i = 0; i < sz; ++i)
    {
        v.push_back(values[i]);
    }

    return v;
}



/*------------------------------------------------------------------------------------------------*/
vector<float>
generateVector(int sz)
{
    vector<float> v;
    for(int i = 0; i < sz; ++i)
    {
        v.push_back(0.0f);
    }

    return v;
}
