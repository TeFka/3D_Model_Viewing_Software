//-------------------------------------------------------------
// Header file to store the interfaces of Matrix3x3 class and all their functions
//-------------------------------------------------------------

//Copyright Danielius Zurlys (StudentID: 20130611)

// Required header files: iostream(for printing with cout), vector, string, fstream, maths.h

//-------------------------------------------------------------
//-------------------------------------------------------------

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>
#ifndef Matrix3x3_H_INCLUDED
#define Matrix3x3_H_INCLUDED

//Vector3D class is used with Matrix3x3 class, because of that, it is declared.
class Vector3D;

// Class 'Matrix3x3'
// Creates a virtual Matrix3x3 by storing information.
// Class is made to be row major
//Stored values:
//       int rowDimension;
//       int columnDimension;
//Available functions:
//  public:
//      void setValue(int, int, double);
//      std::vector<std::vector<double>> getMatrix3x3();
//      void setIdentityMatrix3x3();
//      void invert();
//      void transpose();
//      void rotateMatrix3x3(double, double, double, double);
//Available operator overloading
//      Matrix3x3()
//      Matrix3x3+Matrix3x3
//      Matrix3x3-Matrix3x3
//      Matrix3x3*Matrix3x3
//      Matrix3x3*Vector3D
//Constructor1:
//      Creates empty matrix with all values set to zero
//Constructor2:
//      Creates matrix with specified diagonal values
//Destructor:
//      clears array of matrix values
//Copy constructor
//      creates a copy of a specified object
class Matrix3x3
{
    friend class Vector3D;
private:
    //amount of rows
    int rowDimension;
    //amount of columns
    int columnDimension;
    //2D array to store matrix values
    std::vector<std::vector<double>> theMatrix3x3;
public:
    //constructors1
    Matrix3x3();
    //contructor2
    Matrix3x3(double);
    //destructor
    ~Matrix3x3();
    //copy contructor
    Matrix3x3(const Matrix3x3&);
    //retrieves specified Matrix3x3 value
    double operator () (int,int);

    //adds two matrices together
    Matrix3x3 operator + (Matrix3x3&);
    //Subtracts one matrix form another
    Matrix3x3 operator - (Matrix3x3&);
    //multiplies two matrices together
    Matrix3x3 operator * (Matrix3x3&);
    //multiplies two matrices together
    Vector3D operator * (Vector3D&);

    //Function of class Matrix3x3, setValue()
    //Function set the value at specific position of Matrix3x3
    void setValue(int, int, double);

    //Function of class Matrix3x3, getMatrix3x3()
    //Function to get the 2D Matrix3x3 array
    std::vector<std::vector<double>> getMatrix3x3();

    //Function of class Matrix3x3, setIdentityMatrix3x3()
    //Function to turn the matrix into identity matrix
    void setIdentityMatrix3x3();

    //Function of class Matrix3x3, invert()
    //Function to perform invert operation on matrix
    void invert();

    //Function of class Matrix3x3, transpose()
    //Function to perform transpose operation on matrix
    void transpose();

    //Function of class Matrix3x3, rotateMatrix3x3()
    //Function to get matrix of current matrix
    Matrix3x3 getRotationMatrix3x3(double, double, double, double);
};

#endif // Matrix3x3_H_INCLUDED
