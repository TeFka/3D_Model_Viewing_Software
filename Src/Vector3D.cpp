//-------------------------------------------------------------
// File to store all implementations of functions of Vector3D class.
//-------------------------------------------------------------

// Copyright Woranan Kamonlattana (Student ID: 20310814)

//-------------------------------------------------------------
//-------------------------------------------------------------

//INCLUDE header file for Vector3D
#include "../Inc/Vector3D.h"

//Constructor
//default settings
Vector3D::Vector3D()
{
    x = 0;
    y = 0;
    z = 0;
}

//giving values to object
Vector3D::Vector3D(double xc, double yc, double zc)
{
    x = xc;
    y = yc;
    z = zc;
}

//Setters
//Function of class Vector, setID(), setx(), sety(), setz()
//Function to set the values of vector coordinates
//Arguments for setID(), setx(), sety(), setz(): none.
//return: value of newID, xc, yc and zc
void Vector3D::setID(int newID)
{
    this->ID = newID;
};
void Vector3D::setx(double xc)
{
    x = xc;
};
void Vector3D::sety(double yc)
{
    y = yc;
};
void Vector3D::setz(double zc)
{
    z = zc;
};

//Getters
//Function of class Vector, getID(), getx(), gety(), getz()
//Function to get value vector coordinates
//Arguments for getID(), getx(), gety(), getz(): none.
//return: value of ID, x, y and z
int Vector3D::getID()
{
    return this->ID;
};
double Vector3D::getx()
{
    return x;
}
double Vector3D::gety()
{
    return y;
}
double Vector3D::getz()
{
    return z;
}

//destructor
Vector3D::~Vector3D()
{
}

//operations-----------------------------------------------------------------------

//copy vector constructor
Vector3D::Vector3D(const Vector3D &vec)
{
    ID = vec.ID;
    x=vec.x;
    y=vec.y;
    z=vec.z;
}

//Addition
//action: add 2 vectors together
//return: added results of the addition operation
Vector3D Vector3D::operator+(const Vector3D &vec)
{
    return Vector3D(this->x + vec.x, this->y + vec.y, this->z + vec.z);
}

//Subtraction
//action: subtract current vector from another vector
//return: results of the subtraction operation
Vector3D Vector3D::operator-(const Vector3D &vec)
{
    return Vector3D(this->x - vec.x, this->y - vec.y, this->z - vec.z);
}

//Dot Product
//action: multiply the value in the coordinate of current vector to the equivelent coordinate of another vector
//return: scalar product obtained from dot operation
double Vector3D::dot_product(const Vector3D &vec)
{
    return (this->x*vec.x, this->y*vec.y + this->z*vec.z);
}

//Cross Product
//action: multiply the current vector to another vector using cross product method, multiply the value in the coordinate to an inequivalent coordinate of another vector
//return: the vector results from the cross product operation
Vector3D Vector3D::cross_product(const Vector3D &vec)
{
    Vector3D ans;
    ans.x = this->y*vec.z - this->z*vec.y;
    ans.y = this->z*vec.x - this->x*vec.z;
    ans.z = this->x*vec.y - this->y*vec.x;

    return ans;
}

//-----------------------------------------------------------------------------------
