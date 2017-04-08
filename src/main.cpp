#include "FilterLowPass.h"
#include "MatrixUtils.h"

using namespace std;



/*------------------------------------------------------------------------------------------------*/
int 
main(int argc, char **argv)
{

#if 0
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
#endif

    #define CTE 2000


    Matrix<double> A(CTE,CTE);
    Matrix<double> b(CTE,1);


    for(int i = 0; i < CTE; ++i)
    {
        b[i][0] = i;

        for(int j = 0; j < CTE; ++j)
        {
            
            A[i][j] = exp(-fabs(2*(i-j)));
            
        }
    }

    Matrix<double> x(b);
    //cout << "A = " << A << "\n";
    //cout << "b = " << b << "\n"; 

 
    x = A.conjugateGradientSolver(b);

    //cout << "x = " << x << "\n";

    
    //cout << "invA = ";
    //cout << A.computeInverseBySolver() << "\n";

    return 0;

    
}