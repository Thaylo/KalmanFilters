#ifndef MATRIX_H
#define MATRIX_H

#include "Debug.h"

#include <new>
#include <iostream>
#include <vector>
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
    operator*( const double lambda )
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
    operator/( const double lambda )
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
    double
    dot( const Matrix<double> &B )
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

    for( int i = 0; i < rSz; ++i )
    {
        for( int j = 0; j < cSz; ++j )
        {
            os << "\t" << matrix[i][j] << " ";
        }
        os << ";\n";
    }
    os << "\n";

    return os;
}

#endif /* MATRIX_H */
