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
     \n  Argument:   getID(), getNamee(),getColor(), getDensity()
     \return value of ID, Name,Color, Density
    */

    int getID();
    std::string getName();
    double getDensity();
    Vector3D getColor();

    /*! Set functions
     \n Function of class material, setID(),setName(); setColor(), setDensity()
     \n Function to set the values of material coordinates
     \n  Argument:  setID(), setName(); setColor(), setDensity()
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
