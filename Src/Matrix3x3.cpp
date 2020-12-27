//-------------------------------------------------------------
// File to store all implementations of functions of Matrx class.
//-------------------------------------------------------------

//Copyright Danielius Zurlys (StudentID: 20130611)

// Required header files: iostream(for printing with cout), Matrix.h(to get function interfaces)

//-------------------------------------------------------------
//-------------------------------------------------------------

#include "../Inc/Matrix3x3.h"
#include "../Inc/Vector3D.h"

//Constructor of Matrix3x3 class
//Action:
//      Fills the 2D array with zeros, creates an empty Matrix3x3
//Arguments: none
Matrix3x3::Matrix3x3()
{
        for(int matIterator1 = 0; matIterator1<3; matIterator1++)
        {
            std::vector<double> tempMat;
            for(int matIterator2 = 0; matIterator2<3; matIterator2++)
            {
                tempMat.push_back(0);
            }
            this->theMatrix3x3.push_back(tempMat);
        }
        this->rowDimension = 3;
        this->columnDimension = 3;
}

//Constructor of Matrix3x3 class
//Action:
//      Fills the 2D Matrix3x3 array with zeros, except in middle diagonally, diagonal values are set to specified value.
//      Example 3x3 Matrix3x3: X00
//                             0X0
//                             00X
//Arguments: double - value to be set diagonally.
Matrix3x3::Matrix3x3(double generalVal)
{
        for(int matIterator1 = 0; matIterator1<3; matIterator1++)
        {
            std::vector<double> tempMat;
            for(int matIterator2 = 0; matIterator2<3; matIterator2++)
            {
                if(matIterator1==matIterator2)
                {
                    tempMat.push_back(generalVal);
                }
                else
                {
                    tempMat.push_back(0);
                }
            }
            this->theMatrix3x3.push_back(tempMat);
        }
        this->rowDimension = 3;
        this->columnDimension = 3;
}

//Destructor for Matrix3x3 class
// Action:
//      Clears values in Matrix3x3 2D array.
Matrix3x3::~Matrix3x3()
{
    this->theMatrix3x3.clear();
}

//Copy constructor of Model class
//Action:
//copies the Matrix3x3 2D array.
Matrix3x3::Matrix3x3(const Matrix3x3& copied_Matrix3x3)
{
    theMatrix3x3 = copied_Matrix3x3.theMatrix3x3;

}

//Function of class Matrix3x3, setValue()
//Function set the value at specific position of Matrix3x3
// Arguments for setValue(): int - row index, int - column index, double new value to set
// return value: none(new value is set)
//Notes:
// 1) Will give error if any of the indexes are out of range
void Matrix3x3::setValue(int index1, int index2, double val)
{
    if(index1>this->rowDimension)
    {
        std::cout<<"row index out of range"<<std::endl;
    }
    else if(index2>this->columnDimension)
    {
        std::cout<<"column index out of range"<<std::endl;
    }
    else
    {
        this->theMatrix3x3[index1][index2] = val;
    }
}

//Function of class Matrix3x3, getMatrix3x3()
//Function to get the 2D Matrix3x3 array
// Arguments for getMatrix3x3(): none
// return value: std::vector<std::vector<double>> - the 2D Matrix3x3 array
std::vector<std::vector<double>> Matrix3x3::getMatrix3x3()
{
    return this->theMatrix3x3;
}

//Operator of class Matrix3x3, ()
//Action:
//  retrieves specified Matrix3x3 value
// Arguments for operator (): int - row index, int - column index
// return value: double - value at specified position
//Notes:
// 1) Will give error if any of the indexes are out of range
double Matrix3x3::operator()(int index1, int index2)
{
    if(index1>this->rowDimension)
    {
        std::cout<<"row index out of range"<<std::endl;
    }
    else if(index2>this->columnDimension)
    {
        std::cout<<"column index out of range"<<std::endl;
    }
    else
    {
        return this->theMatrix3x3[index1][index2];
    }
}

//Operator of class Matrix3x3, +Matrix3x3
//Action:
//  adds two matrices together
// Arguments for operator +: Matrix3x3 - another Matrix3x3 to add
// return value: Matrix3x3 - new added Matrix3x3
//Notes:
// 1) Will give error if Matrix3x3 is added with other types.
Matrix3x3 Matrix3x3::operator+(Matrix3x3& mat)
{
    Matrix3x3 tempMat;
    for(int matIterator1 = 0; matIterator1<this->theMatrix3x3.size(); matIterator1++)
    {
        for(int matIterator2 = 0; matIterator2<this->theMatrix3x3.size(); matIterator2++)
        {
            tempMat.setValue(matIterator1,matIterator2,
                             this->theMatrix3x3[matIterator1][matIterator2]+mat(matIterator1,matIterator2));
        }
    }
    return tempMat;
}

//Operator of class Matrix3x3, -Matrix3x3
//Action:
//  Subtracts one matrix form another
// Arguments for operator -: Matrix3x3 - another Matrix3x3 that will be subtracted from the main one
// return value: Matrix3x3 - new subtracted Matrix3x3
//Notes:
// 1) Will give error if Matrix3x3 is subtracted by other types.
Matrix3x3 Matrix3x3::operator-(Matrix3x3& mat)
{
    Matrix3x3 tempMat;
    for(int matIterator1 = 0; matIterator1<this->theMatrix3x3.size(); matIterator1++)
    {
        for(int matIterator2 = 0; matIterator2<this->theMatrix3x3.size(); matIterator2++)
        {
            tempMat.setValue(matIterator1,matIterator2,
                             this->theMatrix3x3[matIterator1][matIterator2]-mat(matIterator1,matIterator2));
        }
    }
    return tempMat;
}

//Operator of class Matrix3x3, *Matrix3x3
//Action:
//  multiplies two matrices together
// Arguments for operator *: Matrix3x3 - another Matrix3x3 to multiply with
// return value: Matrix3x3 - new multiplied Matrix3x3
//Notes:
// 1) Will give error if Matrix3x3 is multiplied with other types.
Matrix3x3 Matrix3x3::operator*(Matrix3x3& mat)
{
        Matrix3x3 tempMat;
        for(int matIterator1 = 0; matIterator1<3; matIterator1++)
        {
            for(int matIterator2 = 0; matIterator2<3; matIterator2++)
            {
                tempMat.setValue(matIterator1,matIterator2,
                                 this->theMatrix3x3[matIterator1][0]*mat(0,matIterator2)+
                                 this->theMatrix3x3[matIterator1][1]*mat(1,matIterator2)+
                                 this->theMatrix3x3[matIterator1][2]*mat(2,matIterator2));
            }
        }
        return tempMat;
}

//Function of class Matrix3x3, setIdentityMatrix3x3()
//Function to turn the matrix into identity matrix
// Arguments for setIdentityMatrix3x3(): none
// return value: none(matrix turned into identity matrix)
void Matrix3x3::setIdentityMatrix3x3()
{
    for(int matIterator1 = 0; matIterator1<this->theMatrix3x3.size(); matIterator1++)
    {
        for(int matIterator2 = 0; matIterator2<this->theMatrix3x3.size(); matIterator2++)
        {
            if(matIterator1==matIterator2)
            {
                this->theMatrix3x3[matIterator1][matIterator2]=1;
            }
            else
            {
                this->theMatrix3x3[matIterator1][matIterator2]=0;
            }
        }
    }
}

//Operator of class Matrix3x3, *Vector3D
//Action:
//  multiplies two matrices together
// Arguments for operator *: Vector3D - 3D vector to multiply with
// return value: Vector3D - new multiplied 3D vector
// 1) Will give error if Matrix3x3 is multiplied with other types.
Vector3D Matrix3x3::operator*(Vector3D& vec)
{
    Vector3D tempVec;
    tempVec.setx((this->theMatrix3x3[0][0]*vec.getx())+(this->theMatrix3x3[0][1]*vec.gety())+(this->theMatrix3x3[0][2]*vec.getz()));
    tempVec.sety((this->theMatrix3x3[1][0]*vec.getx())+(this->theMatrix3x3[1][1]*vec.gety())+(this->theMatrix3x3[1][2]*vec.getz()));
    tempVec.setz((this->theMatrix3x3[2][0]*vec.getx())+(this->theMatrix3x3[2][1]*vec.gety())+(this->theMatrix3x3[2][2]*vec.getz()));
    return tempVec;
}

//Function of class Matrix3x3, transpose()
//Function to perform transpose operation on matrix
// Arguments for transpose(): none
// return value: none(transpose operation performed)
void Matrix3x3::transpose()
{
    if(this->theMatrix3x3.size()==3)
    {
        std::swap(this->theMatrix3x3[0][1],this->theMatrix3x3[1][0]);
        std::swap(this->theMatrix3x3[0][2],this->theMatrix3x3[2][0]);
        std::swap(this->theMatrix3x3[1][2],this->theMatrix3x3[2][1]);
    }
}

//Function of class Matrix3x3, invert()
//Function to perform invert operation on matrix
// Arguments for invert(): none
// return value: none(invert operation performed)
void Matrix3x3::invert()
{
    if(this->theMatrix3x3.size()==3)
    {
        double tempStorage[9] = { this->theMatrix3x3[0][0],this->theMatrix3x3[0][1],this->theMatrix3x3[0][2],
                                  this->theMatrix3x3[1][0],this->theMatrix3x3[1][1],this->theMatrix3x3[1][2],
                                  this->theMatrix3x3[2][0],this->theMatrix3x3[2][1],this->theMatrix3x3[2][2]
                                };
        double D = (this->theMatrix3x3[0][0]*(this->theMatrix3x3[1][1]*this->theMatrix3x3[2][2]-this->theMatrix3x3[1][2]*this->theMatrix3x3[2][1])-
                    this->theMatrix3x3[0][1]*(this->theMatrix3x3[1][0]*this->theMatrix3x3[2][2]-this->theMatrix3x3[1][2]*this->theMatrix3x3[2][0])+
                    this->theMatrix3x3[0][2]*(this->theMatrix3x3[1][0]*this->theMatrix3x3[2][1]-this->theMatrix3x3[1][1]*this->theMatrix3x3[2][0]));
        this->theMatrix3x3[0][0] = ((1/D)*(tempStorage[4]*tempStorage[8]-tempStorage[5]*tempStorage[7]));
        this->theMatrix3x3[0][1] = ((1/D)*-(tempStorage[3]*tempStorage[8]-tempStorage[5]*tempStorage[6]));
        this->theMatrix3x3[0][2] = ((1/D)*(tempStorage[3]*tempStorage[7]-tempStorage[4]*tempStorage[6]));
        this->theMatrix3x3[1][0] = ((1/D)*-(tempStorage[1]*tempStorage[8]-tempStorage[2]*tempStorage[7]));
        this->theMatrix3x3[1][1] = ((1/D)*(tempStorage[0]*tempStorage[8]-tempStorage[2]*tempStorage[6]));
        this->theMatrix3x3[1][2] = ((1/D)*-(tempStorage[0]*tempStorage[7]-tempStorage[1]*tempStorage[6]));
        this->theMatrix3x3[2][0] = ((1/D)*(tempStorage[1]*tempStorage[5]-tempStorage[2]*tempStorage[4]));
        this->theMatrix3x3[2][1] = ((1/D)*-(tempStorage[0]*tempStorage[5]-tempStorage[2]*tempStorage[3]));
        this->theMatrix3x3[2][2] = ((1/D)*(tempStorage[0]*tempStorage[4]-tempStorage[1]*tempStorage[3]));
        this->transpose();
    }
}


//Function of class Matrix3x3, rotateMatrix3x3()
//Function to add rotation to matrix
// Arguments for rotateMatrix3x3(): double - rotation angle in degrees, double - rotation x axis, double - rotation y axis, double - rotation z axis,
// return value: none(matrix is rotated)
void Matrix3x3::rotateMatrix3x3(double degrees, double xAxis, double yAxis, double zAxis)
{

    Matrix3x3 tempMatX(1.0f);
    Matrix3x3 tempMatY(1.0f);
    Matrix3x3 tempMatZ(1.0f);
    Matrix3x3 rotationMat(1.0f);
    if(xAxis!=0.0f)
    {
        tempMatX.setValue(1,1,cos(degrees));
        tempMatX.setValue(1,2,-sin(degrees));
        tempMatX.setValue(2,1,sin(degrees));
        tempMatX.setValue(2,2,cos(degrees));
    }
    if(yAxis!=0.0f)
    {
        tempMatX.setValue(0,0,cos(degrees));
        tempMatX.setValue(0,2,sin(degrees));
        tempMatX.setValue(2,0,-sin(degrees));
        tempMatX.setValue(2,2,cos(degrees));
    }
    if(zAxis!=0.0f)
    {
        tempMatX.setValue(0,0,cos(degrees));
        tempMatX.setValue(0,1,-sin(degrees));
        tempMatX.setValue(1,0,sin(degrees));
        tempMatX.setValue(1,1,cos(degrees));
    }

    std::vector<std::vector<double>> tempMatVals = (tempMatX*tempMatY*tempMatZ).getMatrix3x3();
    std::vector<double> vals;
    for(int matIterator1 = 0; matIterator1<this->theMatrix3x3.size(); matIterator1++)
    {
        for(int matIterator2 = 0; matIterator2<this->theMatrix3x3.size(); matIterator2++)
        {
            vals.push_back((this->theMatrix3x3[matIterator1][0]*tempMatVals[0][matIterator2]+
                            this->theMatrix3x3[matIterator1][1]*tempMatVals[1][matIterator2]+
                            this->theMatrix3x3[matIterator1][2]*tempMatVals[2][matIterator2]));
        }
    }
    this->theMatrix3x3[0][0] = vals[0];
    this->theMatrix3x3[0][1] = vals[1];
    this->theMatrix3x3[0][2] = vals[2];
    this->theMatrix3x3[1][0] = vals[3];
    this->theMatrix3x3[1][1] = vals[4];
    this->theMatrix3x3[1][2] = vals[5];
    this->theMatrix3x3[2][0] = vals[6];
    this->theMatrix3x3[2][1] = vals[7];
    this->theMatrix3x3[2][2] = vals[8];
}
