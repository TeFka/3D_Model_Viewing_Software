//material class.cpp file---------
//---------------------------------
//Copyright Chen Xu (student ID : 20187733)
//---------------------------------


#include "C:\Users\25358\Desktop\new_software\2020_GROUP_19/Inc/Material.h"
#include <stdio.h>

//constructor 
//default
material::material()
{
    ID = 0 ;
    Color = 0 ;
    Density = 0 ;
    Name = 0 ;

}

//set value for the function
material :: material( int id, double d, string name, Vector3D col )  {
	this->ID = id ;
	this->Color = col ;
	this->Density = d ;
    this->Name = name ;
}
//----------------------------------------------------
//All functions for getfunction() and setfunction()

//Get function
//Function of class material, getID(),getName(), getColor(), getDensity()
//Function to get value material coordinates
//Arguments for getID(), getNamee(),getColor(), getDensity() 
//return: value of ID, Name,Color, Density


int material:: material::getID(){return this->ID;}
std::string getName(){return this->Name;}
Vecror3D material::getColor(){return this->Color;}
double material::getDensity(){return this->Density;}




//Set functions
//Function of class material, setID(),setName(); setColor(), setDensity() 
//Function to set the values of material coordinates
//Arguments for setID(), setName(); setColor(), setDensity() 
//return: value of id, ,name , col and  d 
void material::setID( int id ){this->ID = id;}
void setName( std::string name );{this->Name = name;}
void material::setColor( Vector3D col ){this->Color = col;}
void material::setDensity( double density ){this->Density = d;}


//------------------------------------------------------

//destructor
material::~material(){}

//copy constructor
material::material(const material & m){
    ID = m.ID;
    Density = m.Density;
    Color = m.Color;
    Name = m.Name;
}


//End for this code
//--------------------------------------------------------