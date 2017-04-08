#include "LinearKalman.h"
#include "FilterLowPass.h"
#include "MatrixUtils.h"

using namespace std;



/*------------------------------------------------------------------------------------------------*/
int 
main(int argc, char **argv)
{

#if 0
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
#endif

    #define dim 100
    Matrix<double> A(dim,dim);
    Matrix<double> x(dim,1);
    Matrix<double> b(dim,1);

    for(int i = 0; i < dim; ++i)
    {
        x[i][0] = i;
        A[i][i] = 1.0;

        for(int j = 0; j < dim; ++j)
        {
            A[i][j] += 200;
        }
    }
    b = A*x;

    auto xBCGSTAB = A.Bicgstab(b);
    auto xCG = A.conjugateGradientSolver(b);
    
    cout << "A = " << A << "\n";
    cout << "b = " << b << "\n";
    cout << "xBCGSTAB = " << xBCGSTAB << "\n";
    cout << "xCG = " << xCG << "\n";

    return 0;

    
}