//-------------------------------------------------------------
// Header File to store all interfaces of functions of Vector3D class.
//-------------------------------------------------------------

// Copyright Woranan Kamonlattana (Student ID: 20310814)

//-------------------------------------------------------------
//-------------------------------------------------------------

//#include <iostream>
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
    //default
    Vector3D();

    //constructor
    Vector3D(double,double,double);

    //destructor
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
	
	//addition of vectors
    Vector3D operator+(const Vector3D &vec);
	
	//subtraction of vectors
    Vector3D operator-(const Vector3D &vec);
	
	//scalar product between vectors
    double dot_product(const Vector3D &vec);
	
	//vector product between vectors
    Vector3D cross_product(const Vector3D &vec); 

};

#endif // VECTOR3D_H
