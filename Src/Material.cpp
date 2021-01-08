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
    std::string Color = 0 ;
    Density = 0 ;
    std::string Name = 0 ;

}

//set value for the function
material :: material( int id, int density, string name, string colour )  {
	this->ID = id ;
	this->Color = colour ;
	this->Density = density ;
    this->Name = name ;
}

//----------------------------------------------------
//All functions for getfunction() and setfunction()

//Get function
//Function of class material, getID(), getcolor(), getdensity()
//Function to get value material coordinates
//Arguments for getID(), getcolor(), getdensity().
//return: value of id, colour, density
int material:: material::getID(){return this->ID;}
string material::getcolor(){return this->Color;}
int material::getdensity(){return this->Density;}

//Set functions
//Function of class material, setID(), setcolor(), setdensity()
//Function to set the values of material coordinates
//Arguments for setID(), setcolor(), setdensity()
//return: value of id, colour, d and density
void material::setID( int id ){this->ID = id;}
void material::setcolor( string colour ){this->Color = colour;}
void material::setdensity( int density ){this->Density = density;}

//------------------------------------------------------

//destructor
material::~material(){}

//copy constructor
material::material(const material & m){
    ID = m.ID;
    Density = m.Density;
    string Color = m.Color;
    string Name = m.Name;
}