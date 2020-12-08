#include"../Inc/Material.h"
//--------------------------------------------
Material::Material(){

}
Material :: Material( int id, Vector3D col, double d ) : ID(id), color(col), density(d) {}
	//this->ID = id ;
	//this->color = c ;
	//this->density = d ;

//for ID
int Material :: getID(){//get(accessor) function to read.
    return this->ID;
}

void Material :: setID( int id ){//set(mutator) function to modify.
    this->ID = id;
}
//for name
std::string Material :: getName(){
    return this->name;
}

void Material :: setName(std::string newName){
    this->name = newName;
}
//for color
Vector3D Material :: getColor(){
    return this->color;
}

void Material :: setColor(Vector3D newCol){
    this->color = newCol;
}

//for density
double Material :: getDensity(){
    return this->density;
}

void Material :: setDensity(double newDensity){
    this->density = newDensity;
}
