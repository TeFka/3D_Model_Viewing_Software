#include"../Inc/materialClass.h"
//--------------------------------------------
material :: material( int id, double c[3], double d ) : ID(id), color(c), density(d) {}
	//this->ID = id ;
	//this->color = c ;
	//this->density = d ;

//for ID
int material :: getID(){//get(accessor) function to read.
    return this->ID;
}

void material :: setID( int id ){//set(mutator) function to modify.
    this->ID = id;
}

//for color
double material :: getcolor(){
    return this->color;
}

void material :: setcolor( double color[4] ){
    this->color = c;
}

//for density
double material :: getdensity(){
    return this->density;
}

void material :: setdensity(){
    this->density = d;
}