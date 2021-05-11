/*! \file Matrix3x3.h File Reference
    \author   Copyright:  
              \n Code part: Danielius Zurlys (StudentID: 20130611)
              \n Documentation part: Danielius Zurlys and Chen xu  (StudenTID: 20187733)
    \brief    Required header files: iostream(for printing with cout), vector, string, fstream, maths.h
*/


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>
#ifndef Matrix3x3_H_INCLUDED
#define Matrix3x3_H_INCLUDED


class Vector3D;//! Vector3D class is used with Matrix3x3 class, because of that, it is declared.

/*! \class Matrix3x3
    \brief Creates a virtual Matrix3x3 by storing information.
        \n   Class is made to be row major
    \n  Stored values:
    \n     int rowDimension;
    \n     int columnDimension;
    \n Available functions:
    \n public:
    \n  void setValue(int, int, double);
    \n  std::vector<std::vector<double>> getMatrix3x3();
    \n  void setIdentityMatrix3x3();
    \n   void invert();
    \n   void transpose();
    \n   void rotateMatrix3x3(double, double, double, double);
    \n Available operator overloading
    \n   Matrix3x3()
    \n   Matrix3x3+Matrix3x3
    \n    Matrix3x3-Matrix3x3
    \n    Matrix3x3*Matrix3x3
    \n    Matrix3x3*Vector3D
    \n Constructor1:
    \n    Creates empty matrix with all values set to zero
    \n Constructor2:
    \n    Creates matrix with specified diagonal values
    \n Destructor:
    \n    clears array of matrix values
    \n Copy constructor
    \n  creates a copy of a specified object
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
    \arg double - value to be set diagonally. 
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
     \arg operator (): int - row index, int - column index
     \return double - value at specified position
     \note:
     1) Will give error if any of the indexes are out of range 
    */
    double operator () (int,int);

    /*! Operator of class Matrix3x3, +Matrix3x3
     \n   Action:
     \n   adds two matrices together.
     \arg  operator +: Matrix3x3 - another Matrix3x3 to add
     \return  Matrix3x3 - new added Matrix3x3
     \note
      1) Will give error if Matrix3x3 is added with other types. 
    */
    Matrix3x3 operator + (Matrix3x3&);
    /*! Operator of class Matrix3x3, -Matrix3x3
      \n Action:
      \n Subtracts one matrix form another
      \arg operator -: Matrix3x3 - another Matrix3x3 that will be subtracted from the main one
      \return Matrix3x3 - new subtracted Matrix3x3
      \note
      1) Will give error if Matrix3x3 is subtracted by other types. 
    */
    Matrix3x3 operator - (Matrix3x3&);
    /*! Operator of class Matrix3x3, *Matrix3x3
     \n Action:
     \n multiplies two matrices together
     \arg operator *: Matrix3x3 - another Matrix3x3 to multiply with
     \return Matrix3x3 - new multiplied Matrix3x3
     \note
     1) Will give error if Matrix3x3 is multiplied with other types.
    */
    Matrix3x3 operator * (Matrix3x3&);
    //! multiplies two matrices together
    Vector3D operator * (Vector3D&);

    /*! Function of class Matrix3x3, setValue()  \n
        Function set the value at specific position of Matrix3x3 
       \arg setValue(): int - row index, int - column index, double new value to set
       \return  none(new value is set)
       \note
        1) Will give error if any of the indexes are out of range
    */
    void setValue(int, int, double);

    /*! Function of class Matrix3x3, getMatrix3x3() \n
        Function to get the 2D Matrix3x3 array 
        \arg setValue(): int - row index, int - column index, double new value to set
        \return  none(new value is set)
        \note
        1) Will give error if any of the indexes are out of range
    */
    std::vector<std::vector<double>> getMatrix3x3();

    /*! Function of class Matrix3x3, setIdentityMatrix3x3() \n
        Function to turn the matrix into identity matrix 
        \arg setIdentityMatrix3x3(): none
        \return none(matrix turned into identity matrix)
    */
    void setIdentityMatrix3x3();

    /*! Function of class Matrix3x3, invert()   \n
        Function to perform invert operation on matrix 
        \arg invert(): none
        \return none(invert operation performed)
    */
    void invert();

    /*! Function of class Matrix3x3, transpose()   \n
        Function to perform transpose operation on matrix 
        \arg transpose(): none
        \return none(transpose operation performed)
        */
    void transpose();

    /*! Function of class Matrix3x3, rotateMatrix3x3()   \n
        Function to get matrix of current matrix 
        \arg rotateMatrix3x3(): double - rotation angle in degrees, double - rotation x axis, double - rotation y axis, double - rotation z axis,
        \return Matrix3x3 - rotation matrix
    */
    Matrix3x3 getRotationMatrix3x3(double, double, double, double);
};

#endif //! Matrix3x3_H_INCLUDED
