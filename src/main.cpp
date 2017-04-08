#include "LinearKalman.h"
#include "FilterLowPass.h"
#include "MatrixUtils.h"

using namespace std;



/*------------------------------------------------------------------------------------------------*/
int 
main(int argc, char **argv)
{

    LinearKalman f;
    int dim = f.getDimensionality();

    Matrix<float> input(dim,1);
    input[0][0] = 1.0f;

    list<Matrix<float>> inputList;
    inputList.push_back(input);

    Matrix<float> output(dim,1);

    f.readValue(output);
    cout << "Out = " << output << "\n"; 

    for(int i = 0; i < 20; ++i)
    {
        f.inputValue(inputList);
        f.readValue(output);
        cout << "Out = " << output << "\n";
    }


    return 0;

    
}