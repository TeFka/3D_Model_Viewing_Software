/*! \file   Material.h File Reference 
    \brief  It should be three parts for material ID, color, and density.
 
            Copyright  Chen Xu (student ID : 20187733)
            
            Required header files: iostream(for printing with cout), string,Vector3D.h, Material.h
*/

#ifndef MATERIALCLASS_H_INCLUDED
#define MATERIALCLASS_H_INCLUDED


#include <string>
#include <iostream>
#include "Vector3D.h"
using namespace std;

/*! 
    \class 'Material'
    \brief Material class describes the functions that get the ID, Density Name and Color.And store it for the other parts to use.
  Stored values:
         int rowDimension;
         int columnDimension;
  Available functions:
    public:
         int getID();
         std::string getName();
         double getDensity();
         Vector3D getColor();
         void setID(int);
         void setName(std::string);
         void setColor(Vector3D);
	     void setColor(double, double, double);
         void setDensity(double);
    private:
         int ID;
         double Density;
         string Name;
         Vector3D Color;
  Constructor:
        Creates empty matrix with all values set to zero
  Destructor:
        clears array of matrix values
  Copy constructor
        creates a copy of a specified object
*/

class Material
{

private:

//! member variables.

    int ID;
    double Density;
    string Name;
    Vector3D Color;

public:


    Material();//! Default.



    Material(int, double, std::string, Vector3D);//! Constructor.


    ~Material();//! Destructor.


    int getID();
    std::string getName();
    double getDensity();
    Vector3D getColor();


    void setID(int);
    void setName(std::string);
    void setColor(Vector3D);
	void setColor(double, double, double);
    void setDensity(double);


    Material(const Material & m);//! Copy constructor.


};


#endif //! MATERIALCLASS_H_INCLUDED.
