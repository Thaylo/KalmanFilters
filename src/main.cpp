#include "FilterLowPass.h"
#include "MatrixUtils.h"

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


    #define CTE 2

    cout << "Hello matrix!\n";

    Matrix<float> A(CTE,CTE);
    Matrix<float> B(CTE,1);

    double n = 0.25;
    double theta = n * 2 * M_PI;

    A[0][0] = cos(theta);
    A[0][1] = -sin(theta);
    A[1][0] = sin(theta);
    A[1][1] = cos(theta);
    std::cout << A;

    B[0][0] = 1;
    B[1][0] = 1;
    std::cout << B;

    Matrix<float> C = A*B;
    cout << C;

    return 0;

    
}