/*! \file Matrix3x3.h File Reference
    \author   Copyright:  
              \n Code part: Danielius Zurlys (StudentID: 20130611)
              \n Documentation part: Chen xu  (StudenTID: 20187733)
    \brief    Required header files: iostream(for printing with cout), vector, string, fstream, maths.h
*/


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>
#ifndef Matrix3x3_H_INCLUDED
#define Matrix3x3_H_INCLUDED

//! Vector3D class is used with Matrix3x3 class, because of that, it is declared.
class Vector3D;

/*! \class Matrix3x3
    \brief Creates a virtual Matrix3x3 by storing information.
*/
class Matrix3x3
{
    friend class Vector3D;
private:
    //! amount of rows
    int rowDimension;
    //! amount of columns
    int columnDimension;
    //! 2D array to store matrix values
    std::vector<std::vector<double>> theMatrix3x3;
public:
    /*! constructors1:
    \note Action:
    \n      Fills the 2D array with zeros, creates an empty Matrix3x3
    \arg  none 
    */
    Matrix3x3();
    /*! contructor2:
    \note Action:
    \n     Fills the 2D Matrix3x3 array with zeros, except in middle diagonally, diagonal values are set to specified value.
    \n    Example 3x3 Matrix3x3: X00
    \n                           0X0
    \n                           00X
    \n Argument: double - value to be set diagonally. 
    */
    Matrix3x3(double);
    /*! destructor:
    \note Action:
    \n    Clears values in Matrix3x3 2D array. 
    */
    ~Matrix3x3();
    /*! copy contructor 
    \note Action:
    \n copies the Matrix3x3 2D array.
    */    
    Matrix3x3(const Matrix3x3&);
    /*! Operator of class Matrix3x3()
     \n Action:
     \n retrieves specified Matrix3x3 value
     \n Argument: operator (): int - row index, int - column index
     \return double - value at specified position
     \note:
     1) Will give error if any of the indexes are out of range 
    */
    double operator () (int,int);

    /*! Operator of class Matrix3x3, +Matrix3x3
     \n   Action:
     \n   adds two matrices together.
     \n Argument:  operator +: Matrix3x3 - another Matrix3x3 to add
     \return  Matrix3x3 - new added Matrix3x3
     \note
      1) Will give error if Matrix3x3 is added with other types. 
    */
    Matrix3x3 operator + (Matrix3x3&);
    /*! Operator of class Matrix3x3, -Matrix3x3
      \n Action:
      \n Subtracts one matrix form another
      \n Argument: operator -: Matrix3x3 - another Matrix3x3 that will be subtracted from the main one
      \return Matrix3x3 - new subtracted Matrix3x3
      \note
      1) Will give error if Matrix3x3 is subtracted by other types. 
    */
    Matrix3x3 operator - (Matrix3x3&);
    /*! Operator of class Matrix3x3, *Matrix3x3
     \n Action:
     \n multiplies two matrices together
     \n Argument: operator *: Matrix3x3 - another Matrix3x3 to multiply with
     \return Matrix3x3 - new multiplied Matrix3x3
     \note
     1) Will give error if Matrix3x3 is multiplied with other types.
    */
    Matrix3x3 operator * (Matrix3x3&);
    //! multiplies two matrices together
    Vector3D operator * (Vector3D&);

    /*! Function of class Matrix3x3, setValue()  \n
        Function set the value at specific position of Matrix3x3 
       \n Argument: setValue(): int - row index, int - column index, double new value to set
       \return  none(new value is set)
       \note
        1) Will give error if any of the indexes are out of range
    */
    void setValue(int, int, double);

    /*! Function of class Matrix3x3, getMatrix3x3() \n
        Function to get the 2D Matrix3x3 array 
        \arg setValue(): int - row index, int - column index, double new value to set
        \n Argument:  none(new value is set)
        \note
        1) Will give error if any of the indexes are out of range
    */
    std::vector<std::vector<double>> getMatrix3x3();

    /*! Function of class Matrix3x3, setIdentityMatrix3x3() \n
        Function to turn the matrix into identity matrix 
        \n Argument: setIdentityMatrix3x3(): none
        \return none(matrix turned into identity matrix)
    */
    void setIdentityMatrix3x3();

    /*! Function of class Matrix3x3, invert()   \n
        Function to perform invert operation on matrix 
        \n Argument: invert(): none
        \return none(invert operation performed)
    */
    void invert();

    /*! Function of class Matrix3x3, transpose()   \n
        Function to perform transpose operation on matrix 
        \n Argument: transpose(): none
        \return none(transpose operation performed)
        */
    void transpose();

    /*! Function of class Matrix3x3, rotateMatrix3x3()   \n
        Function to get matrix of current matrix 
        \n Argument: rotateMatrix3x3(): double - rotation angle in degrees, double - rotation x axis, double - rotation y axis, double - rotation z axis,
        \return Matrix3x3 - rotation matrix
    */
    Matrix3x3 getRotationMatrix3x3(double, double, double, double);
};

#endif //! Matrix3x3_H_INCLUDED
