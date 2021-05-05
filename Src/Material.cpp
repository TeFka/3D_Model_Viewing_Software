//Material class.cpp file---------
//---------------------------------
//Copyright Chen Xu (student ID : 20187733)
//---------------------------------

#include "../Inc/Material.h"

//constructor
//default
Material::Material()
{
    ID = 0;
	Density = 0;
    Color = Vector3D(0.0,0.0,0.0);
    Name = "";

}

//set value for the function
Material :: Material( int id, double d, std::string name, Vector3D col)
{
    this->ID = id ;
	this->Density = d ;
    this->Color = col ;
    this->Name = name ;
}
//----------------------------------------------------
//All functions for getfunction() and setfunction()

//Get function
//Function of class material, getID(),getName(), getColor(), getDensity()
//Function to get value material coordinates
//Arguments for getID(), getNamee(),getColor(), getDensity()
//return: value of ID, Name,Color, Density


int Material::getID()
{
    return ID;
}
std::string Material::getName()
{
    return Name;
}
Vector3D Material::getColor()
{
    return Color;
}
double Material::getDensity()
{
    return Density;
}




//Set functions
//Function of class material, setID(),setName(); setColor(), setDensity()
//Function to set the values of material coordinates
//Arguments for setID(), setName(); setColor(), setDensity()
//return: value of id, ,name , col and  d
void Material::setID( int id )
{
    this->ID = id;
}
void Material::setName( std::string name )
{
    this->Name = name;
}
void Material::setColor( Vector3D col )
{
    this->Color = col;
}
void Material::setColor( double redVal, double greenVal, double blueVal)
{
    this->Color.setx(redVal);
	this->Color.sety(greenVal);
	this->Color.setz(blueVal);
}
void Material::setDensity( double density )
{
    this->Density = density;
}


//------------------------------------------------------

//destructor
Material::~Material() {}

//copy constructor
Material::Material(const Material & m)
{
    ID = m.ID;
    Density = m.Density;
    Color = m.Color;
    Name = m.Name;
}


//End for this code
//--------------------------------------------------------
