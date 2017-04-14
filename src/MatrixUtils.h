#ifndef MATRIX_H
#define MATRIX_H

#include "Debug.h"

#include <new>
#include <iostream>
#include <string.h>
#include <iostream>
#include <cmath>



template <class ValueType>
class Matrix
{
private:
    ValueType ** values;
    int numRows;
    int numColumns;

public:

    /*--------------------------------------------------------------------------------------------*/
    Matrix<ValueType>()
    {
        numRows = numColumns = 0;
        values = NULL;
    }



    /*--------------------------------------------------------------------------------------------*/
    Matrix<ValueType>( int a, int b )
    {
        numRows = a;
        numColumns = b;
        values = new ValueType*[numRows];
        for( int i = 0; i < numRows; ++i )
        {
            values[i] = new ValueType [numColumns];
            memset((void*) values[i], 0, numColumns * sizeof(ValueType) );
        }
    }



    /*--------------------------------------------------------------------------------------------*/
    Matrix<ValueType>( const Matrix &m )
    {
        numRows = m.numRows;
        numColumns = m.numColumns;

        values = new ValueType*[numRows];

        for( int i = 0; i < numRows; ++i )
        {
            values[i] = new ValueType [numColumns];

            for( int j = 0; j < numColumns; ++j )
            {
                values[i][j] = m[i][j];
            }
        }
    }



    /*--------------------------------------------------------------------------------------------*/
    int
    getNumberOfColumns() const
    {
        return numColumns;
    }



    /*--------------------------------------------------------------------------------------------*/
    int
    getNumberOfRows() const
    {
        return numRows;
    }



    /*--------------------------------------------------------------------------------------------*/
    ~Matrix<ValueType>()
    {
        if ( NULL != values )
        {
            for( int i = 0; i < numRows; ++i )
            {
                delete values[i];
            }

            delete values;
        }
    }



    /*--------------------------------------------------------------------------------------------*/
    ValueType *
    operator[](int a) const
    {
        return values[a];
    }



    /*--------------------------------------------------------------------------------------------*/
    void
    resize( int rows, int columns )
    {
        if ( values != NULL )
        {
            for( int i = 0; i < numRows; ++i )
            {
                delete values[i];
            }

            delete values;
        }

        numRows = rows;
        numColumns = columns;

        values = new ValueType*[numRows];

        for( int i = 0; i < numRows; ++i )
        {
            values[i] = new ValueType[numColumns];
            memset((void*) values[i], 0, numColumns * sizeof(ValueType) );
        }
    }



    /*--------------------------------------------------------------------------------------------*/
    Matrix
    conjugateGradientSolver(Matrix &b)
    {
        Matrix<ValueType> x(b);
        Matrix<ValueType> A(*this);
        ValueType rsnew;

        for(int repetition = 0; repetition < 10; ++ repetition)
        {
            Matrix<ValueType> r(b - A * x);
            Matrix<ValueType> p(r);
            ValueType rsold = r.dot(r);

            Matrix<ValueType> Ap(b);
            int bColumns = b.getNumberOfColumns();


            for(int i = 0; i < bColumns; ++i)
            {
                Ap = A * p;
                ValueType den = p.dot(Ap);
                if (den < 1e-7)
                {
                    break;
                }
                ValueType alpha = rsold / den;
                x = x + p * alpha;
                rsnew = r.dot(r);
                if (sqrt(rsnew) < 1e-10)
                {
                    break;
                }
                p = r + p*(rsnew/rsold);
                rsold = rsnew;
            }
        }
        return x;
    }



   /*--------------------------------------------------------------------------------------------*/
    Matrix
    Bicgstab(Matrix &b, int maxIter = 1)
    {
        Matrix A(*this);
        Matrix x(b);
        auto r0 = b - A*x;
        Matrix r0Tilde(r0);
        Matrix ri(r0);


        ValueType rho, alpha, omega;
        rho = alpha = omega = 1.0;

        Matrix v(b.getNumberOfRows(),1);
        Matrix p(b.getNumberOfRows(),1);

        auto pastRi = ri;
        auto pastRho = rho;
        auto pastOmega = omega;
        auto pastP = p;
        auto pastV = v;
        auto pastX = x;

        for(int iter = 0; iter < maxIter; iter++)
        {
            rho = r0Tilde.dot(pastRi);
            auto beta = (rho/pastRho)*(alpha/pastOmega);
            p = pastRi + ( pastP - pastV * pastOmega) * beta;
            v = A*p;
            alpha = rho/r0Tilde.dot(v);
            auto h = pastX + p*alpha;

            auto hres = b - A*h;
            if(hres.dot(hres) < 1e-10)
            {
                return h;
            }

            auto s = pastRi - v * alpha;
            auto t = A*s;
            omega = t.dot(s)/t.dot(t);

            x = h + s * omega;

            auto xres = b - A*x;
            if(xres.dot(xres) < 1e-10)
            {
                return x;
            }

            ri = s - t*omega;

            pastRi = ri;
            pastRho = rho;
            pastOmega = omega;
            pastP = p;
            pastV = v;
            pastX = x;
        }
    }


    /*--------------------------------------------------------------------------------------------*/
    Matrix
    concatenateColumns(Matrix &B)
    {
        int aColumns = this->getNumberOfColumns();
        int aRows = this->getNumberOfRows();
        int bColumns = B.getNumberOfColumns();


        Matrix<ValueType> A(*this);
        Matrix<ValueType> AB(aRows, aColumns + bColumns);
        for(int i = 0; i < aRows; ++i)
        {
            for(int j = 0; j < aColumns; ++j)
            {
                AB[i][j] = A[i][j];
            }
            for(int j = 0; j < bColumns; ++j)
            {
                AB[i][j+aColumns] = B[i][j];
            }
        }

        return AB;
    }

    /*--------------------------------------------------------------------------------------------*/
    Matrix
    computeInverseBySolver()
    {
        Matrix<ValueType> A(*this);
        int aRows = A.getNumberOfRows();


        Matrix<ValueType> identityColumn(aRows, 1);
        Matrix<ValueType> inverseColumn(aRows, 1);

        identityColumn[0][0] = 1.0f;
        inverseColumn = A.conjugateGradientSolver(identityColumn);
        identityColumn[0][0] = 0.0f;

        Matrix<ValueType> inverse(inverseColumn);

        for(int i = 1; i < aRows; ++i)
        {
            identityColumn[i][0] = 1.0f;
            inverseColumn = A.conjugateGradientSolver(identityColumn);
            identityColumn[i][0] = 0.0f;
            inverse = inverse.concatenateColumns(inverseColumn);
        }

        return inverse;
    }




    /*--------------------------------------------------------------------------------------------*/
    Matrix
    identityMatrix(int dim)
    {
        Matrix<ValueType> I(dim, dim);

        for(int i = 0; i < dim; ++i)
        {
            I[i][i] = 1.0;
        }

        return I;
    }


    /*--------------------------------------------------------------------------------------------*/
    Matrix
    generateNormalVector()
    {
        Matrix v(3,1);

        v.values[0][0] = -values[1][0];
        v.values[1][0] =  values[0][0] - values[2][0];
        v.values[2][0] =  values[1][0];

        return v;
    }



    /*--------------------------------------------------------------------------------------------*/
    Matrix
    operator=( const Matrix &matrix )
    {
        Matrix m( matrix.numRows, matrix.numColumns );

        if ( numRows != matrix.numRows || numColumns != matrix.numColumns )
        {
            resize( matrix.numRows, matrix.numColumns );
        }

        for( int i = 0; i < numRows; ++i )
        {
            for( int j = 0; j < numColumns; ++j )
            {
                m[i][j] = values[i][j] = matrix[i][j];
            }
        }

        return m;
    }



    /*--------------------------------------------------------------------------------------------*/
    Matrix
    operator+( const Matrix &matrix )
    {
        Matrix m( numRows, numColumns );
        m = *this;

        common_assert( numRows == matrix.numRows
                                           && numColumns == matrix.numColumns );

        for( int i = 0; i < numRows; ++i )
        {
            for( int j = 0; j < numColumns; ++j )
            {
                m[i][j] += matrix[i][j];
            }
        }

        return m;
    }



    /*--------------------------------------------------------------------------------------------*/
    Matrix
    operator-( const Matrix &matrix )
    {
        Matrix m( numRows, numColumns );
        m = *this;

        common_assert( numRows == matrix.numRows
                                           && numColumns == matrix.numColumns );

        for( int i = 0; i < numRows; ++i )
        {
            for( int j = 0; j < numColumns; ++j )
            {
                m[i][j] -= matrix[i][j];
            }
        }


        return m;
    }



    /*--------------------------------------------------------------------------------------------*/
    Matrix
    operator*( const Matrix &matrix )
    {
        common_assert( numColumns == matrix.numRows );

        Matrix m( numRows, matrix.numColumns );
        int p = numColumns;

        for( int i = 0; i < numRows; ++i )
        {
            for( int j = 0; j < matrix.numColumns; ++j )
            {
                for (int k = 0; k < p; ++k )
                {
                    m[i][j] += values[i][k] * matrix[k][j];
                }
            }
        }

        return m;
    }



    /*--------------------------------------------------------------------------------------------*/
    Matrix
    operator*( const ValueType lambda )
    {
        Matrix m( numRows, numColumns );

        for( int i = 0; i < numRows; ++i )
        {
            for( int j = 0; j < numColumns; ++j )
            {
                m[i][j] = values[i][j]*lambda;
            }
        }

        return m;
    }




    /*--------------------------------------------------------------------------------------------*/
    Matrix
    operator/( const ValueType lambda )
    {
        Matrix m( numRows, numColumns );

        for( int i = 0; i < numRows; ++i )
        {
            for( int j = 0; j < numColumns; ++j )
            {
                m[i][j] = values[i][j]/lambda;
            }
        }

        return m;
    }



    /*--------------------------------------------------------------------------------------------*/
    Matrix
    transpose() const
    {
        Matrix m( numColumns, numRows );

        for( int i = 0; i < numColumns; ++i )
        {
            for( int j = 0; j < numRows; ++j )
            {
                m[i][j] = values[j][i];
            }
        }

        return m;
    }




    /*--------------------------------------------------------------------------------------------*/
    Matrix
    CholeskyLFactorization() const
    {
        Matrix L( numColumns, numColumns );
        Matrix A(*this);

        for( int j = 0; j < numColumns; ++j )
        {
            ValueType acumulator = 0.0f;

            for(int k = 0; k < j - 1; ++ k)
            {
                acumulator += pow(L[j][k], 2.0);
            }

            L[j][j] = sqrt(A[j][j] - acumulator);
        }

        for( int j = 0; j < numColumns; ++j )
        {
            for( int i = j + 1; i < numColumns; ++i )
            {
                ValueType acumulator = 0.0f;

                for(int k = 0; k < j - 1; ++ k)
                {
                    acumulator += L[i][k]*L[j][k];
                }
                L[i][j] = (A[i][j] - acumulator)/L[j][j];
            }
        }

        return L;
    }



    /*--------------------------------------------------------------------------------------------*/
    double
    length()
    {
        return pow(lengthSquared(),0.5);
    }



    /*--------------------------------------------------------------------------------------------*/
    double
    lengthSquared()
    {

        double acum = 0.0;

        for( int i = 0; i < numRows; ++i )
        {
            for( int j = 0; j < numColumns; ++j )

            {
                acum += values[i][j]*values[i][j];
            }
        }

        return acum;
    }



    /*--------------------------------------------------------------------------------------------*/
    ValueType
    dot( const Matrix &B )
    {
        return (this->transpose()*B)[0][0];
    }


};


    /*--------------------------------------------------------------------------------------------*/
    template <class ValueType>
    std::ostream& operator<<( std::ostream& os, const Matrix<ValueType> & matrix)
    {
        int rSz = matrix.getNumberOfRows();
        int cSz = matrix.getNumberOfColumns();
        os << "[";
        for( int i = 0; i < rSz; ++i )
        {
            for( int j = 0; j < cSz; ++j )
            {
                os << "\t" << matrix[i][j] << " ";
            }
            if(i != rSz-1)
            {
                os << ";\n";
            }
            else
            {
                os << "]";
            }
        }
        os << "\n";

        return os;
    }



#endif /* MATRIX_H */
