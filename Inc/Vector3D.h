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

// Class 'Vector3D'
// Creates a virtual Vector3D by storing information.
// Class is made to be row major
// Stored values:
//      int ID;
//      double x, y, z;
// Available functions:
//  public:
//      Vector3D(double,double,double);
//  setters:
//      void setID(int)
//      void setx(double)
//      void sety(double)
//      void setz(double)
//  getters:
//      int getID()
//      double getx()
//      double gety()
//      double getz()
//Available operator
//      Vector3D+Vector3D
//      Vector3D-Vector3D
//      Vector3D*Vector3D
//Function
//      Vector3D cross_product
//Constructor1:
//      Creates empty matrix with all values set to zero
//Constructor2:
//      Creates matrix with specified diagonal values
//Destructor
//Copy constructor
//      creates a copy of a specified object

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


<<<<<<< HEAD
//Operations
	
	//copy constructor
=======
    //Operations

    //copy constructor
>>>>>>> e08b29f5be3b7db2a73522ea432f1b01f8a4af5d
    Vector3D (const Vector3D & vec);

    //Addition
    //action: add 2 vectors together
    Vector3D operator+(const Vector3D &vec);

    //Subtraction
    //action: subtract current vector from another vector
    Vector3D operator-(const Vector3D &vec);
<<<<<<< HEAD
	
	//Dot Product
	//action: perform dot product operation
    double operator*(const Vector3D &vec);

//Function
	//Cross Product
	//action: perform cross product operation
    Vector3D cross_product(const Vector3D &vec); 
=======

    //Dot Product
    //action: perform dot product operation
    double dot_product(const Vector3D &vec);

    //Cross Product
    //action: perform cross product operation
    Vector3D cross_product(const Vector3D &vec);
>>>>>>> e08b29f5be3b7db2a73522ea432f1b01f8a4af5d

};

#endif // VECTOR3D_H
