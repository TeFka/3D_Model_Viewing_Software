/*! \file   Material.h File Reference 
    \author Copyright Code and Documatation part: Chen Xu (student ID : 20187733)
            
    \brief  Required header files: iostream(for printing with cout), string,Vector3D.h, Material.h
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
     \n Stored values:
     \n    calue of specified ID;
           double Density;
           string Name;
           Vector3D Color;
     \n Available functions:
     \n public:
     \n    int getID();
     \n    std::string getName();
     \n    double getDensity();
     \n    Vector3D getColor();
     \n    void setID(int);
     \n    void setName(std::string);
     \n    void setColor(Vector3D);
	 \n    void setColor(double, double, double);
     \n    void setDensity(double);
     \n private:
     \n    int ID;
     \n    double Density;
     \n    string Name;
     \n    Vector3D Color;
     \n Constructor:
     \n   Gains the required material information from specifed file
     \n Destructor:
     \n   clears ID Density Name and Color values
     \n Copy constructor
     \n   creates a copy of a specified material object
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
    
    /*! Get function
     \n Function of class material, getID(),getName(), getColor(), getDensity()
     \n Function to get value material coordinates
     \arg  getID(), getNamee(),getColor(), getDensity()
     \return value of ID, Name,Color, Density
    */

    int getID();
    std::string getName();
    double getDensity();
    Vector3D getColor();

    /*! Set functions
     \n Function of class material, setID(),setName(); setColor(), setDensity()
     \n Function to set the values of material coordinates
     \arg setID(), setName(); setColor(), setDensity()
     \return: value of id, ,name , col and  d  
    */
    void setID(int);
    void setName(std::string);
    void setColor(Vector3D);
	void setColor(double, double, double);
    void setDensity(double);


    Material(const Material & m);//! Copy constructor.


};


#endif //! MATERIALCLASS_H_INCLUDED.
