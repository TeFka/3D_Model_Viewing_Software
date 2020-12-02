#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include<math.h>
#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

enum matrixType
{
    MAT3x3,
    MAT4x4,
};

//class is made to be row major
class Matrix
{

private:
    int matIterator1;
    int matIterator2;
    int rowDimension;
    int columnDimension;
    //3x3
    std::vector<std::vector<float>> theMatrix;
public:
    //constructors
    Matrix(matrixType);
    Matrix(matrixType,float);
    //destructor
    ~Matrix();
    float operator () (int,int);

    Matrix operator +(Matrix&);
    Matrix operator - (Matrix&);
    Matrix operator * (Matrix&);

    float setValue(int, int, float);
    std::vector<std::vector<float>> getMatrix();
    void setIdentityMatrix();
    void invert();
    void transpose();

    void rotateMatrix(float, float, float, float);
};

#endif // MATRIX_H_INCLUDED
