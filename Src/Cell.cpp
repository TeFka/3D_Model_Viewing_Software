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
//constructor
  Cell::Cell(int ID,int type,int materialID,std::vector<int> indices){
        this->ID = ID;
        this->indices = indices;
        this->type = type;
        this->materialId = materialID;
    }

//COPY constructor function cell
Cell::Cell(const Model& copied_Model)
{
    volume = copied_Cell.volume;
	weight = copied_Cell.weight;
    CenterOfGravity = copied_Cell.cellCenterOfGravity;
}
//destructor function cell
Cell::~Cell()
{
    this->volumes.clear();
    this->weights.clear();
    this->centerOfGravities.clear();//not sure what to destruct here
}
//--------------------------------------------------------------------------------
int Cell::getID()
{
    return this->ID;
}
int Cell::getType()
{
    return this->type;
}
int Cell::getMaterialID()
{
    return this->materialID;
}
std::vector<int> Cell::getIndices()
{
    return this->indices;
}
Vector3D Cell::getCentreOFGravity()
{
    return this->centre_of_gravity;
}

void Cell::setID(int newID)
{
    this->ID = newID;
}
void Cell::setType(int newType)
{
    this->type = newType;
}
void Cell::setMaterialID(int newID)
{
    this->materialID = newID;
}
void Cell::setIndices(std::vector<int> newIndices)
{
    this->indices = newIndices;
}
void Cell::pushIndice(int newIndice)
{
    this->indices.push_back(newIndice);
}
void Cell::insertIndice(int index,int newIndice)
{
    this->indices.insert(this->indices.begin()+index,newIndice);
}

//--------------------------------------------------------------------------------
//defining functions for the tetrahedron
//constructor
Tetrahedron::Tetrahedron(int ID,int type,int materialID,std::vector<int> indices,std::vector<Vector3D> vertices,std::vector<Material> vertices):Cell(ID,type,materialID,indices)//constructor
{
    calculateVolume(vertices);
    calcweight(materials);
    gravity center(vertices);
}
//--------------------------------------------------------------
//copy constructor
Tetrahedron::Tetrahedron()
{
 volume = copied_Tetrahedron.volume;
	weight = copied_Tetrahedron.weight;
    CenterOfGravity = copied_Tetrahedron.cellCenterOfGravity;
}
//--------------------------------------------------------------------
//tetrahedron function destructor
//destructor function cell
Tetrahedron::~Tetrahedron()
{
    this->volumes.clear();
    this->weights.clear();
    this->centerOfGravities.clear();//not sure what to destruct here
}
//---------------------------------------------------------------
//Function getvolume()
//Function to calculate the volume of the tetrahedron
// Arguments for getvolume(std::vector<Vector3D> vectors) : array of vectors
// return value: volume (double)
double Tetrahedron::getvolume(std::vector<Vector3D> vectors,std::vector<int> indices)//will overwrite original getvolume function in cell class
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
//-----------------------------------------------------------------------------------------------------
//Function of subclass Tetrahedron, calcModelCenter()
//Function to calculate position of model center
// Arguments for calcModelCenter(): none.
// return value: none(model center value updated)
//Note:
//Model center of gravity will become {0,0,0} if vector array is empty.
Vector3D Tetrahedron::getCentreOFGravity();
{
    double x=0,y=0,z=0;
    //add up positions of all vectors
    for(int i = 0; i<this->vectors.size(); i++)
    {
        x+=this->vectors[i].getx();
        y+=this->vectors[i].gety();
        z+=this->vectors[i].getz();

        //dan said to change to get vector values same way as done for volume.
        x+=this->vectors[this->indices[i]].getx();
        y+=this->vectors[this->indices[i]].gety();
        z+=this->vectors[this->indices[i]].getz();//like this?
    }
    //return vector with averages of added up positions
    this->modelCenter = Vector3D(x/this->vectors.size(),y/this->vectors.size(),z/this->vectors.size());
}
//--------------------------------------------------------------------------------------

//Function getWeight(float Vtetra)
//Function to calculate the weight of the tetrahedron
// Arguments for getWeight(float Vtetra) ****
// return value: weight (double)
Tetrahedron::getWeight(float Vtetra,std::vector<Material> vertices)
{
    Wtetra = 9.81*Vtetra*DENSITY****;
}
//-----------------------------------------------------------------------------------------------------
//defining functions for pyramid
//--------------------------------------------------------------------------------------------------------------
//constructor
Pyramid::Pyramid(int ID,int type,int materialID,std::vector<int> indices,std::vector<Vector3D> vertices,std::vector<Material> vertices):Cell(ID,type,materialID,indices)//constructor
{
    calculateVolume(vertices);
    calcweight(materials);
    gravity center(vertices);
}
//-------------------------------------------------------------------------------
//copy constructor
Pyramid::Pyramid(const Pyramid& copied_Pyramid)
{
 volume = copied_Pyramid.volume;
	weight = copied_Pyramid.weight;
    CenterOfGravity = copied_Pyramid.cellCenterOfGravity;
}
//---------------------------------------------------------------------------------------------------------------
//destructor function pyramid
Pyramid::~Pyramid()
{
    this->volumes.clear();
    this->weights.clear();
    this->centerOfGravities.clear();//not sure what to destruct here
}
//--------------------------------------------------------------------------------------------------------------
//Function getvolume()
//Function to calculate the volume of the pyramid
// Arguments for getvolume(std::vector<Vector3D> vectors) : array of vectors
// return value: volume (double)
double Pyramid::getvolume(std::vector<Vector3D> vectors,std::vector<int> indices)
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
//-------------------------------------------------------------------------------------------
//Function of subclass pyramid, calcModelCenter()
//Function to calculate position of model center
// Arguments for calcModelCenter(): none.
// return value: none(model center value updated)
//Note:
//Model center of gravity will become {0,0,0} if vector array is empty.
Vector3D pyramid::getCentreOFGravity();
{

    double x=0,y=0,z=0;
    //add up positions of all vectors
    for(int i = 0; i<this->vectors.size(); i++)
    {
        x+=this->vectors[i].getx();
        y+=this->vectors[i].gety();
        z+=this->vectors[i].getz();

        //dan said to change to get vector values same way as done for volume.
        x+=this->vectors[this->indices[i]].getx();
        y+=this->vectors[this->indices[i]].gety();
        z+=this->vectors[this->indices[i]].getz();//like this?
    }
    //return vector with averages of added up positions
    this->modelCenter = Vector3D(x/this->vectors.size(),y/this->vectors.size(),z/this->vectors.size());
}
//---------------------------------------------------------------------------------------
//Function getWeight(float Vpyramid)
//Function to calculate the weight of the pyramid
// Arguments for getvolume(float Vpyramid) ****
// return value: weight (double)
Tetrahedron::getWeight(float Vpyramid,std::vector<Material> vertices)
{
    Wpyramid = 9.81*Vpyramid*DENSITY****;
}
//---------------------------------------------------------------------------------
//defining functions for hexahedron
//-------------------------------------------------------------------------------
//constructor
Hexahedron::Hexahedron(int ID,int type,int materialID,std::vector<int> indices,std::vector<Vector3D> vertices,std::vector<Material> vertices):Cell(ID,type,materialID,indices)//constructor
{
    calculateVolume(vertices);
    calcweight(materials);
    gravity center(vertices);
}
//---------------------------------------------------------------------------
//copy constructor
Hexahedron::Hexahedron(const Hexahedron& copied_Hexahedron)
{
 volume = copied_Hexahedron.volume;
	weight = copied_Hexahedron.weight;
    CenterOfGravity = copied_Hexahedron.cellCenterOfGravity;
}
//----------------------------------------------------------------------------------------
//destructor function cell
Hexahedron::~Hexahedron()
{
    this->volumes.clear();
    this->weights.clear();
    this->centerOfGravities.clear();//not sure what to destruct here
}
 
//---------------------------------------------------------------------------------------
//Function getvolume()
//Function to calculate the volume of the hexahedron
// Arguments for getvolume(std::vector<Vector3D> vectors) : array of vectors
// return value: volume (double)
double Hexahedron::getvolume(std::vector<Vector3D> vectors,std::vector<int> indices)
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

    double Vhexa = Vtetra1 + Vtetra2 + Vtetra3 + Vtetra4 + Vtetra5 + Vtetra6;
}
//----------------------------------------------------------------------------------------------------
//Function of subclass Hexahedron, calcModelCenter()
//Function to calculate position of model center
// Arguments for calcModelCenter(): none.
// return value: none(model center value updated)
//Note:
//Model center of gravity will become {0,0,0} if vector array is empty.
Vector3D Hexahedron::getCentreOFGravity(std::vector<int> indices);
{

    double x=0,y=0,z=0;
    //add up positions of all vectors
    for(int i = 0; i<this->vectors.size(); i++)
    {
        x+=this->vectors[i].getx();
        y+=this->vectors[i].gety();
        z+=this->vectors[i].getz();

        //dan said to change to get vector values same way as done for volume.
        x+=this->vectors[this->indices[i]].getx();
        y+=this->vectors[this->indices[i]].gety();
        z+=this->vectors[this->indices[i]].getz();//like this?
    }
    //return vector with averages of added up positions
    this->modelCenter = Vector3D(x/this->vectors.size(),y/this->vectors.size(),z/this->vectors.size());
}
//---------------------------------------------------------------------------------------
//Function getWeight(float Vhexa)
//Function to calculate the weight of the pyramid
// Arguments for getvolume(float Vhexa) ****
// return value: weight (double)
Tetrahedron::getWeight(float Vhexa,std::vector<Material> vertices)
{
    Whexa = 9.81*Vhexa*DENSITY****;
}
//-------------------------------------------------------------------------------







