//material class.cpp file---------
#include "2020_GROUP_19/Inc/Material.h"
#include <stdio.h>



material :: material( int id, int density, string name, string colour )  {
	this->ID = id ;
	this->Color = colour ;
	this->Density = density ;
        this->Name = name ;
}

//for ID
int material:: material::getID(){
    //get(accessor) function to read.
    return this->ID;
}

void material::setID( int id ){
    //set(mutator) function to modify.
    this->ID = id;
}

//for color
string material::getcolor(){
    return this->Color;
}

void material::setcolor( string c ){
    this->Color = c;
}

//for density
int material::getdensity(){
    return this->Density;
}

void material::setdensity( int d ){
    this->Density = d;
}


