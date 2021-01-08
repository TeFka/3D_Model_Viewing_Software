//-------------------------------------------------------------
// Header File to store all interfaces of functions of Vector3D class.
//-------------------------------------------------------------

// Copyright Woranan Kamonlattana (Student ID: 20310814)

//-------------------------------------------------------------
//-------------------------------------------------------------

#include <vector>
#include <math.h>

#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D
{
private:
    int ID;
    double x, y, z;

public:

	//Constructor
    //default
    Vector3D();

	//giving values to object
    Vector3D(double,double,double);

    //Destructor
    ~Vector3D();

    //Setters
	//Function of class Vector, setID(), setx(), sety(), setz()
	//Function to set the values of vector coordinates
    void setID(int);
    void setx(double);
    void sety(double);
    void setz(double);

    //Getters
	//Function of class Vector, getID(), getx(), gety(), getz()
	//Function to get value vector coordinates
    int getID();
    double getx();
    double gety();
    double getz();


    //Operations
	
	//copy constructor
    Vector3D (const Vector3D & vec);
	
	//Addition
	//action: add 2 vectors together
    Vector3D operator+(const Vector3D &vec);
	
	//Subtraction
	//action: subtract current vector from another vector
    Vector3D operator-(const Vector3D &vec);
	
	//Dot Product
	//action: perform dot product operation
    double dot_product(const Vector3D &vec);
	
	//Cross Product
	//action: perform cross product operation
    Vector3D cross_product(const Vector3D &vec); 

};

#endif // VECTOR3D_H
