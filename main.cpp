#include "FilterLowPass.h"
using namespace std;

/*------------------------------------------------------------------------------------------------*/
int 
main(int argc, char **argv)
{
    FilterLowPass f;
    float constantInput[] = {1.0,1.0,1.0};
    vector<float> input = generateVector(constantInput, 3);
    vector<float> output = generateVector(3);
    

    f.readValue(output);
    displayVector(output); 

    for(int i = 0; i < 20; ++i)
    {
        f.inputValue(input);
        f.readValue(output);
        displayVector(output);
    }
    

}