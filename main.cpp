#include "FilterLowPass.h"
using namespace std;



/*------------------------------------------------------------------------------------------------*/
int 
main(int argc, char **argv)
{
    FilterLowPass f(2, 0.5); // dimensionality and smoothness

    vector<float> input;
    vector<float> output;

    int dim = f.getDimensionality();

    for(int i = 0; i < dim; ++i)
    {
        input.push_back(1.0f);
        output.push_back(0.0f);
    }
    

    f.readValue(output);
    displayVector(output); 

    for(int i = 0; i < 20; ++i)
    {
        f.inputValue(input);
        f.readValue(output);
        displayVector(output);
    }
    
}