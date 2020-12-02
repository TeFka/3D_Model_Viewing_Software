#include "../Inc/Matrix.h"

Matrix::Matrix(matrixType type)
{
    if(type==MAT3x3)
    {
        for(this->matIterator1 = 0; this->matIterator1<3; this->matIterator1++)
        {
            std::vector<float> tempMat;
            for(this->matIterator2 = 0; this->matIterator2<3; this->matIterator2++)
            {
                tempMat.push_back(0);
            }
            this->theMatrix.push_back(tempMat);
        }
    }
    else if(type==MAT4x4)
    {
        for(this->matIterator1 = 0; this->matIterator1<4; this->matIterator1++)
        {
            std::vector<float> tempMat;
            for(this->matIterator2 = 0; this->matIterator2<4; this->matIterator2++)
            {
                tempMat.push_back(0);
            }
            this->theMatrix.push_back(tempMat);
        }
    }
}
Matrix::Matrix(matrixType type, float generalVal)
{
    if(type==MAT3x3)
    {
        for(this->matIterator1 = 0; this->matIterator1<3; this->matIterator1++)
        {
            std::vector<float> tempMat;
            for(this->matIterator2 = 0; this->matIterator2<3; this->matIterator2++)
            {
                if(this->matIterator1==this->matIterator2)
                {
                    tempMat.push_back(generalVal);
                }
                else
                {
                    tempMat.push_back(0);
                }
            }
            this->theMatrix.push_back(tempMat);
        }
    }
    else if(type==MAT4x4)
    {
        for(this->matIterator1 = 0; this->matIterator1<4; this->matIterator1++)
        {
            std::vector<float> tempMat;
            for(this->matIterator2 = 0; this->matIterator2<4; this->matIterator2++)
            {
                if(this->matIterator1==this->matIterator2)
                {
                    tempMat.push_back(generalVal);
                }
                else
                {
                    tempMat.push_back(0);
                }
            }
            this->theMatrix.push_back(tempMat);
        }
    }
}

Matrix::~Matrix()
{

}

float Matrix::setValue(int index1, int index2, float val){
    this->theMatrix[index1][index2] = val;
}

std::vector<std::vector<float>> Matrix::getMatrix(){
    return this->theMatrix;
}

//array operator
float Matrix::operator()(int val1, int val2)
{
    return this->theMatrix[val1][val2];
}

//matrix operators
Matrix Matrix::operator+(Matrix& mat){
    Matrix tempMat(MAT3x3);
    for(this->matIterator1 = 0;this->matIterator1<this->theMatrix.size();this->matIterator1++){
            for(this->matIterator2 = 0;this->matIterator2<this->theMatrix.size();this->matIterator2++){
                    tempMat.setValue(this->matIterator1,this->matIterator2,
                                     this->theMatrix[this->matIterator1][this->matIterator2]+mat(this->matIterator1,this->matIterator2));
            }
        }
    return tempMat;
}
Matrix Matrix::operator-(Matrix& mat){
    Matrix tempMat(MAT3x3);
    for(this->matIterator1 = 0;this->matIterator1<this->theMatrix.size();this->matIterator1++){
            for(this->matIterator2 = 0;this->matIterator2<this->theMatrix.size();this->matIterator2++){
                    tempMat.setValue(this->matIterator1,this->matIterator2,
                                     this->theMatrix[this->matIterator1][this->matIterator2]-mat(this->matIterator1,this->matIterator2));
            }
        }
    return tempMat;
}
Matrix Matrix::operator*(Matrix& mat){
    if(this->theMatrix.size()==3){
    Matrix tempMat(MAT3x3);
    for(this->matIterator1 = 0;this->matIterator1<3;this->matIterator1++){
            for(this->matIterator2 = 0;this->matIterator2<3;this->matIterator2++){
                    tempMat.setValue(this->matIterator1,this->matIterator2,
                                     this->theMatrix[this->matIterator1][0]*mat(0,this->matIterator2)+
                                     this->theMatrix[this->matIterator1][1]*mat(1,this->matIterator2)+
                                     this->theMatrix[this->matIterator1][2]*mat(2,this->matIterator2));
            }
        }
        return tempMat;
    }
}

void Matrix::setIdentityMatrix()
{
    for(this->matIterator1 = 0; this->matIterator1<this->theMatrix.size(); this->matIterator1++)
    {
        for(this->matIterator2 = 0; this->matIterator2<this->theMatrix.size(); this->matIterator2++)
        {
            if(this->matIterator1==this->matIterator2)
            {
                this->theMatrix[this->matIterator1][this->matIterator2]=1;
            }
            else
            {
                this->theMatrix[this->matIterator1][this->matIterator2]=0;
            }
        }
    }
}

void Matrix::transpose()
{
    if(this->theMatrix.size()==3){
    std::swap(this->theMatrix[0][1],this->theMatrix[1][0]);
    std::swap(this->theMatrix[0][2],this->theMatrix[2][0]);
    std::swap(this->theMatrix[1][2],this->theMatrix[2][1]);
    }
}

void Matrix::invert()
{
    if(this->theMatrix.size()==3){
    float tempStorage[9] = { this->theMatrix[0][0],this->theMatrix[0][1],this->theMatrix[0][2],
    this->theMatrix[1][0],this->theMatrix[1][1],this->theMatrix[1][2],
    this->theMatrix[2][0],this->theMatrix[2][1],this->theMatrix[2][2]};
        float D = (this->theMatrix[0][0]*(this->theMatrix[1][1]*this->theMatrix[2][2]-this->theMatrix[1][2]*this->theMatrix[2][1])-
                   this->theMatrix[0][1]*(this->theMatrix[1][0]*this->theMatrix[2][2]-this->theMatrix[1][2]*this->theMatrix[2][0])+
                   this->theMatrix[0][2]*(this->theMatrix[1][0]*this->theMatrix[2][1]-this->theMatrix[1][1]*this->theMatrix[2][0]));
    this->theMatrix[0][0] = ((1/D)*(tempStorage[4]*tempStorage[8]-tempStorage[5]*tempStorage[7]));
    this->theMatrix[0][1] = ((1/D)*-(tempStorage[3]*tempStorage[8]-tempStorage[5]*tempStorage[6]));
    this->theMatrix[0][2] = ((1/D)*(tempStorage[3]*tempStorage[7]-tempStorage[4]*tempStorage[6]));
    this->theMatrix[1][0] = ((1/D)*-(tempStorage[1]*tempStorage[8]-tempStorage[2]*tempStorage[7]));
    this->theMatrix[1][1] = ((1/D)*(tempStorage[0]*tempStorage[8]-tempStorage[2]*tempStorage[6]));
    this->theMatrix[1][2] = ((1/D)*-(tempStorage[0]*tempStorage[7]-tempStorage[1]*tempStorage[6]));
    this->theMatrix[2][0] = ((1/D)*(tempStorage[1]*tempStorage[5]-tempStorage[2]*tempStorage[4]));
    this->theMatrix[2][1] = ((1/D)*-(tempStorage[0]*tempStorage[5]-tempStorage[2]*tempStorage[3]));
    this->theMatrix[2][2] = ((1/D)*(tempStorage[0]*tempStorage[4]-tempStorage[1]*tempStorage[3]));
    this->transpose();
    }
}

void Matrix::rotateMatrix(float degrees, float xAxis, float yAxis, float zAxis){

    Matrix tempMatX(MAT3x3,1.0f);
    Matrix tempMatY(MAT3x3,1.0f);
    Matrix tempMatZ(MAT3x3,1.0f);
    Matrix rotationMat(MAT3x3,1.0f);
    if(xAxis!=0.0f){
    tempMatX.setValue(1,1,cos(degrees));
    tempMatX.setValue(1,2,-sin(degrees));
    tempMatX.setValue(2,1,sin(degrees));
    tempMatX.setValue(2,2,cos(degrees));
    }
    if(yAxis!=0.0f){
    tempMatX.setValue(0,0,cos(degrees));
    tempMatX.setValue(0,2,sin(degrees));
    tempMatX.setValue(2,0,-sin(degrees));
    tempMatX.setValue(2,2,cos(degrees));
    }
    if(zAxis!=0.0f){
    tempMatX.setValue(0,0,cos(degrees));
    tempMatX.setValue(0,1,-sin(degrees));
    tempMatX.setValue(1,0,sin(degrees));
    tempMatX.setValue(1,1,cos(degrees));
    }

    std::vector<std::vector<float>> tempMatVals = (tempMatX*tempMatY*tempMatZ).getMatrix();
    std::vector<float> vals;
    for(this->matIterator1 = 0; this->matIterator1<this->theMatrix.size(); this->matIterator1++)
    {
        for(this->matIterator2 = 0; this->matIterator2<this->theMatrix.size(); this->matIterator2++)
        {
            vals.push_back((this->theMatrix[this->matIterator1][0]*tempMatVals[0][this->matIterator2]+
                                     this->theMatrix[this->matIterator1][1]*tempMatVals[1][this->matIterator2]+
                                     this->theMatrix[this->matIterator1][2]*tempMatVals[2][this->matIterator2]));
        }
    }
    this->theMatrix[0][0] = vals[0];
    this->theMatrix[0][1] = vals[1];
    this->theMatrix[0][2] = vals[2];
    this->theMatrix[1][0] = vals[3];
    this->theMatrix[1][1] = vals[4];
    this->theMatrix[1][2] = vals[5];
    this->theMatrix[2][0] = vals[6];
    this->theMatrix[2][1] = vals[7];
    this->theMatrix[2][2] = vals[8];
}
