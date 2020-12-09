
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
    //plan to get volume of tetrahedron
	//              _   _    _
	//Vtetra = 1/6|(a x b) * c|
	
	//              __   __    __
	//Vtetra = 1/6|(AB x AC) * AD|
	
	//       __
	//to get AB for example, the subtraction function should be used to subtract vector A with Vector B
	//eg: A(2,3,4) B(5,4,3) AB = (5-2, 4-3,3-4) = (3, 1, -1)
	
    //     __  __     __                                                                             __   __
    //once AB, AC and AD have been aquired, use cross product function to achieve the calculation of AB x AC
	//The next step is to do the dot product of (AB x AC) and AD, using the dot product function in the vector class
	//find modulus of this value, using fabs(a) where a is the value we have at this point in the calculation
	//finally, divide by 6 and the volume will be given
}
//--------------------------------------------------------------------------------------
//defining functions for pyramid
Pyramid::Pyramid()//constructor
{

}

double Pyramid::getvolume()
{
    //plan to get volume of pyramid
	//               _   _    _
	//Vpyramid =1/3|(a x b) * c|
	//same method as tetrahedron (see line ***), only difference being that you dont divide by 3 INSTEAD OF 6 at the end
}
//---------------------------------------------------------------------------------
//defining functions for hexahedron
Hexahedron::Hexahedron()//constructor
{

}

double Hexahedron::getvolume()
{
    //plan to get volume of hexahedron
	//         _   _    _
	//Vhexa =|(a x b) * c|
	//same method as tetrahedron (see line ***), only difference being that you dont divide by 6 at the end
}
//-------------------------------------------------------------------------------








