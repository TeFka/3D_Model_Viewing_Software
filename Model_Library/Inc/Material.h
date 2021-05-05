// Class 'Material'
//It should be three parts for material ID, color, and density.
//----------------------------------------------
//Copyright  Chen Xu (student ID : 20187733)
//----------------------------------------------
#ifndef MATERIALCLASS_H_INCLUDED
#define MATERIALCLASS_H_INCLUDED


#include <string>
#include <iostream>
#include "Vector3D.h"
using namespace std;


class Material
{

private:

// member variables.

    int ID;
    double Density;
    string Name;
    Vector3D Color;

public:

//Default:
    Material();


//Constructor:
    Material(int, double, std::string, Vector3D);

//Destructor:
    ~Material();

//Available functions:
    int getID();
    std::string getName();
    double getDensity();
    Vector3D getColor();


    void setID(int);
    void setName(std::string);
    void setColor(Vector3D);
	void setColor(double, double, double);
    void setDensity(double);

//Copy constructor:
    Material(const Material & m);


};





//------------------------------------------------------
//material class is over.
//--------------------------------------------
#endif // MATERIALCLASS_H_INCLUDED
