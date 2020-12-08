
//#include "main.h"
#include "../Inc/Cell.h"

    Cell::Cell(){

    }
    int Cell::getID(){
        return this->ID;
    }
    int Cell::getType(){
        return this->type;
    }
    int Cell::getMaterialID(){
        return this->materialID;
    }
    std::vector<int> Cell::getIndices(){
        return this->indices;
    }
    Vector3D Cell::getCentreOFGravity(){
        return this->centre_of_gravity;
    }

    void Cell::setID(int newID){
        this->ID = newID;
    }
    void Cell::setType(int newType){
        this->type = newType;
    }
    void Cell::setMaterialID(int newID){
        this->materialID = newID;
    }
    void Cell::setIndices(std::vector<int> newIndices){
        this->indices = newIndices;
    }
    void Cell::pushIndice(int newIndice){
        this->indices.push_back(newIndice);
    }
    void Cell::insertIndice(int index,int newIndice){
        this->indices.insert(this->indices.begin()+index,newIndice);
    }

//--------------------------------------------------------------------------------
//defining functions for the tetrahedron
Tetrahedron::Tetrahedron()
{

}
double Tetrahedron::getvolume()//will overwrite original getvolume function in cell class
{
    //code to calculate volume of...
}
//--------------------------------------------------------------------------------------
//defining functions for pyramid
Pyramid::Pyramid()//constructor
{

}

double Pyramid::getvolume()
{
//   ...
}
//---------------------------------------------------------------------------------
//defining functions for hexahedron
Hexahedron::Hexahedron()//constructor
{

}

double Hexahedron::getvolume()
{
    //...
}
//-------------------------------------------------------------------------------








