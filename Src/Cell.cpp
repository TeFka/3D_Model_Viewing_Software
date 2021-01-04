//-------------------------------------------------------------
// File to store all implementations of functions of cell class.
//-------------------------------------------------------------

//Copyright Michael Michael (StudentID: 20143147)

// Required header files: cell.h(to get function interfaces)****subject to change

//-------------------------------------------------------------
//-------------------------------------------------------------
//#include "main.h"
#include "../Inc/Cell.h"
//-------------------------------------------------------------------------
//constructor function cell
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
Tetrahedron::Tetrahedron()//constructor
{

}
//Function getvolume()
//Function to calculate the volume of the tetrahedron
// Arguments for getvolume(std::vector<Vector3D> vectors) : array of vectors
// return value: volume (double)
double Tetrahedron::getvolume(std::vector<Vector3D> vectors)//will overwrite original getvolume function in cell class
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
	
	Vector3D Aval = vectors[this->indices[0]];
	Vector3D Bval = vectors[this->indices[1]];
	Vector3D Cval = vectors[this->indices[2]];
	Vector3D Dval = vectors[this->indices[3]];
	
	double Vtetra = ((((Bval-Aval).cross_product((Cval-Aval))).dot_product((Dval-Aval)))/6.0);
}
   Vector3D Tertahedron::getCentreOFGravity();
   {
	   //plan to get the centre of gravity of tetrahedron
   }
//--------------------------------------------------------------------------------------
//defining functions for pyramid
Pyramid::Pyramid()//constructor
{

}

//Function getvolume()
//Function to calculate the volume of the pyramid
// Arguments for getvolume(std::vector<Vector3D> vectors) : array of vectors
// return value: volume (double)
double Pyramid::getvolume(std::vector<Vector3D> vectors)
{
    //plan to get volume of pyramid
	//essentially, a pyramid is just 2 tetrahedrons put together, therefore to find the volume of the pyramid, we must repeat the same method
	//of finding the volume of a tetrahedron twice.
	//consider the new 5th vertex is called E.
	//the following calculation would be
	//Vpyramid = Vtetra1+Vtetra2 where...
	//               __   __    __                     __   __    __ 
	//Vtetra1 = 1/6|(AB x AC) * AD| and Vtetra2 = 1/6|(EB x EC) * ED|
	Vector3D Aval = vectors[this->indices[0]];
	Vector3D Bval = vectors[this->indices[1]];
	Vector3D Cval = vectors[this->indices[2]];
	Vector3D Dval = vectors[this->indices[3]];
	Vector3D Eval = vectors[this->indices[4]];
		double Vtetra1 = ((((Bval-Aval).cross_product((Cval-Aval))).dot_product((Dval-Aval)))/6.0);
		double Vtetra2 = ((((Bval-Eval).cross_product((Cval-Eval))).dot_product((Dval-Eval)))/6.0);
	    double 	Vpyramid = Vtetra1 + Vtetra2
}
   Vector3D Pyramid::getCentreOFGravity();
   {
	   //plan to get the centre of gravity of PYRAMID
   }
//---------------------------------------------------------------------------------
//defining functions for hexahedron
//-------------------------------------------------------------------------------
Hexahedron::Hexahedron()//constructor
{

}
//---------------------------------------------------------------------------------------
//Function getvolume()
//Function to calculate the volume of the hexahedron
// Arguments for getvolume(std::vector<Vector3D> vectors) : array of vectors
// return value: volume (double)
double Hexahedron::getvolume(std::vector<Vector3D> vectors)
{
    //plan to get volume of hexahedron
	//a hexahedron is 8 tetrahedrons put together
	//use the same method as the one used for finding the volume of tetrahedron but this time repeating it 6 times using the correct vertices
	Vector3D Aval = vectors[this->indices[0]];
	Vector3D Bval = vectors[this->indices[1]];
	Vector3D Cval = vectors[this->indices[2]];
	Vector3D Dval = vectors[this->indices[3]];
	Vector3D Eval = vectors[this->indices[4]];
	Vector3D Fval = vectors[this->indices[5]];
	Vector3D Gval = vectors[this->indices[6]];
	Vector3D Hval = vectors[this->indices[7]];
	double Vtetra1 = ((((Bval-Aval).cross_product((Dval-Aval))).dot_product((Fval-Aval)))/6.0);
	double Vtetra2 = ((((Dval-Cval).cross_product((Bval-Cval))).dot_product((Fval-Cval)))/6.0);
	double Vtetra3 = ((((Dval-Cval).cross_product((Gval-Cval))).dot_product((Fval-Cval)))/6.0);
	double Vtetra4 = ((((Eval-Aval).cross_product((Fval-Aval))).dot_product((Dval-Aval)))/6.0);
	double Vtetra5 = ((((Hval-Fval).cross_product((Eval-Fval))).dot_product((Dval-Fval)))/6.0);
	double Vtetra6 = ((((Hval-Fval).cross_product((Dval-Fval))).dot_product((Gval-Fval)))/6.0);
	
	double Hexahedron = Vtetra1 + Vtetra2 + Vtetra3 + Vtetra4 + Vtetra5 + Vtetra6;
}

   Vector3D Hexahedron::getCentreOFGravity();
   {
	   //plan to get the centre of gravity of hexahedron
   }
   //-------------------------------------------------------------------------------







