
//-------------------------------------------------------------
// File to store all implementations of functions of cell class.
//-------------------------------------------------------------

//Copyright Michael Michael (StudentID: 20143147)

// Required header files: Cell.h(to get function interfaces)
//                        main.h

//-------------------------------------------------------------
//-------------------------------------------------------------
//#include "main.h"
#include "../Inc/Cell.h"
//-------------------------------------------------------------------------
Cell::Cell()
{
    
}
//constructor
Cell::Cell(int ID,int type,int materialID,std::vector<int> indices)
{
    this->ID = ID;
    this->type = type;
    this->materialID = materialID;
    this->indices = indices;
}
//-----------------------------------------------------------
//COPY constructor function cell
Cell::Cell(const Cell& copied_Cell)
{
    this->ID = copied_Cell.ID;
    this->indices = copied_Cell.indices;
    this->type = copied_Cell.type;
    this->materialID = copied_Cell.materialID;
    this->volume = copied_Cell.volume;
    this->weight = copied_Cell.weight;
    this->centre_of_gravity = copied_Cell.centre_of_gravity;
}
//-------------------------------------------------------------------------
//destructor function cell
//clears indice array
Cell::~Cell()
{
    this->indices.clear();
}
//--------------------------------------------------------------------------------
//getfunctions
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

double Cell::getVolume()
{
    return this->volume;
}

double Cell::getWeight()
{
    return this->weight;
}

Vector3D Cell::getCentreOfGravity()
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
	if(index<this->indices.size()){
    this->indices.insert(this->indices.begin()+index,newIndice);
	}
	else{
		std::cout<<"index out of range"<<std::endl;
	}
}
void Cell::setIndice(int index,int newIndice)
{
	if(index<this->indices.size()){
    this->indices[index] = newIndice;
	}
	else{
		std::cout<<"index out of range"<<std::endl;
	}
}
//-----------------------------------------------------------------------------------------------------
//Function of class Cell, calcCentreOfGravity()
//Function to calculate position of cell center of gravity
// Arguments for calcCentreOfGravity(std::vector<Vector3D> vectors)
// return value: Centre_of_gravity(Vector3)(model center value updated)
//Note:
//Model center of gravity will become {0,0,0} if vector array is empty.
void Cell::calcCentreOfGravity(std::vector<Vector3D> vectors)
{
    double x=0,y=0,z=0;
    //add up positions of all vectors
    for(int i = 0; i<this->indices.size(); i++)
    {
        x+=vectors[this->indices[i]].getx();
        y+=vectors[this->indices[i]].gety();
        z+=vectors[this->indices[i]].getz();
    }
    //return vector with averages of added up positions
    this->centre_of_gravity = Vector3D(x/indices.size(),y/this->indices.size(),z/this->indices.size());
}
//--------------------------------------------------------------------------------------
//Function getWeight()
//Function to calculate the weight of the Cell
// Arguments for calcWeight(std::vector<Material> materials)
// return value: weight (double)
void Cell::calcWeight(std::vector<Material> materials)
{
    this->weight = this->volume*materials[this->materialID].getDensity();
}
//--------------------------------------------------------------------------------
//defining functions for the tetrahedron
//---------------------------------------------------------------------------------
Tetrahedron::Tetrahedron():Cell()
{

}
//constructor
Tetrahedron::Tetrahedron(int ID,int type,int materialID,std::vector<int> indices,std::vector<Vector3D> vertices,std::vector<Material> materials):Cell(ID,type,materialID,indices)//constructor
{
    calculateVolume(vertices);
    calcWeight(materials);
    calcCentreOfGravity(vertices);
}
//--------------------------------------------------------------
//copy constructor
Tetrahedron::Tetrahedron(const Cell& copied_Cell):Cell(copied_Cell)
{

}
//--------------------------------------------------------------------
//tetrahedron function destructor
//destructor function cell
Tetrahedron::~Tetrahedron()
{
    this->indices.clear();
}
//---------------------------------------------------------------
//Function getvolume()
//Function to calculate the volume of the tetrahedron
// Arguments for getvolume(std::vector<Vector3D> vectors) : array of vectors
// return value: volume (double)
void Tetrahedron::calculateVolume(std::vector<Vector3D> vectors)//will overwrite original getvolume function in cell class
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

//aquires indeces from array.
    Vector3D Aval = vectors[this->indices[0]];
    Vector3D Bval = vectors[this->indices[1]];
    Vector3D Cval = vectors[this->indices[2]];
    Vector3D Dval = vectors[this->indices[3]];

//calculates volume of tetrahedron.
    double Vtetra1 = (((Bval-Aval).cross_product((Cval-Aval)))*(Dval-Aval));

//makes value positive
    Vtetra1 = (Vtetra1/(6.0-12.0*(Vtetra1<0)));
    this->volume = Vtetra1;
}

//defining functions for pyramid
//--------------------------------------------------------------------------------------------------------------
Pyramid::Pyramid():Cell()
{

}
//constructor
Pyramid::Pyramid(int ID,int type,int materialID,std::vector<int> indices,std::vector<Vector3D> vertices,std::vector<Material> materials):Cell(ID,type,materialID,indices)//constructor
{
    calculateVolume(vertices);
    calcWeight(materials);
    calcCentreOfGravity(vertices);
}
//-------------------------------------------------------------------------------
//copy constructor
Pyramid::Pyramid(const Cell& copied_Cell):Cell(copied_Cell)
{

}
//---------------------------------------------------------------------------------------------------------------
//destructor function pyramid
Pyramid::~Pyramid()
{
    this->indices.clear();
}
//--------------------------------------------------------------------------------------------------------------
//Function getvolume()
//Function to calculate the volume of the pyramid
// Arguments for getvolume(std::vector<Vector3D> vectors) : array of vectors
// return value: volume (double)
void Pyramid::calculateVolume(std::vector<Vector3D> vectors)
{
    //plan to get volume of pyramid
    //essentially, a pyramid is just 2 tetrahedrons put together, therefore to find the volume of the pyramid, we must repeat the same method
    //of finding the volume of a tetrahedron twice.
    //consider the new 5th vertex is called E.
    //the following calculation would be
    //Vpyramid = Vtetra1+Vtetra2 where...
    //               __   __    __                     __   __    __
    //Vtetra1 = 1/6|(AB x AC) * AD| and Vtetra2 = 1/6|(EB x EC) * ED|

    //aquires indeces from array.
    Vector3D Aval = vectors[this->indices[0]];
    Vector3D Bval = vectors[this->indices[1]];
    Vector3D Cval = vectors[this->indices[2]];
    Vector3D Dval = vectors[this->indices[3]];
    Vector3D Eval = vectors[this->indices[4]];

    //calculates volume of each tetrahedron.
//configuration of vertices were checked using the test code, so there is no overlapping of area between the tetrahedrons
    double Vtetra1 = (((Bval-Aval).cross_product((Cval-Aval)))*(Dval-Aval));
    double Vtetra2 = (((Bval-Eval).cross_product((Cval-Eval)))*(Dval-Eval));

//makes volumes positive
    Vtetra1 = (Vtetra1/(6.0-12.0*(Vtetra1<0)));
    Vtetra2 = (Vtetra2/(6.0-12.0*(Vtetra2<0)));

    //adds all the volume of tetrahedrons to aquire the final volume of the pyramid
    this->volume = (Vtetra1 + Vtetra2);
}
//-------------------------------------------------------------------------------------------
//defining functions for hexahedron
//-------------------------------------------------------------------------------------------
Hexahedron::Hexahedron():Cell()
{

}
//constructor
Hexahedron::Hexahedron(int ID,int type,int materialID,std::vector<int> indices,std::vector<Vector3D> vertices,std::vector<Material> materials):Cell(ID,type,materialID,indices)//constructor
{
    calculateVolume(vertices);
    calcWeight(materials);
    calcCentreOfGravity(vertices);
}
//---------------------------------------------------------------------------
//copy constructor
Hexahedron::Hexahedron(const Cell& copied_Cell):Cell(copied_Cell)
{

}
//----------------------------------------------------------------------------------------
//destructor function cell
Hexahedron::~Hexahedron()
{
    this->indices.clear();
}
//---------------------------------------------------------------------------------------
//Function getvolume()
//Function to calculate the volume of the hexahedron
// Arguments for getvolume(std::vector<Vector3D> vectors) : array of vectors
// return value: volume (double)
void Hexahedron::calculateVolume(std::vector<Vector3D> vectors)
{
    //plan to get volume of hexahedron
    //a hexahedron is 6 tetrahedrons put together
    //use the same method as the one used for finding the volume of tetrahedron but this time repeating it 6 times using the correct vertices

    //aquires indeces from array.
    Vector3D Aval = vectors[this->indices[0]];
    Vector3D Bval = vectors[this->indices[1]];
    Vector3D Cval = vectors[this->indices[2]];
    Vector3D Dval = vectors[this->indices[3]];
    Vector3D Eval = vectors[this->indices[4]];
    Vector3D Fval = vectors[this->indices[5]];
    Vector3D Gval = vectors[this->indices[6]];
    Vector3D Hval = vectors[this->indices[7]];


//calculates volume of each tetrahedron.
//configuration of vertices were checked using the test code, so there is no overlapping of area between the tetrahedrons.
    double Vtetra1 = (((Bval-Aval).cross_product((Dval-Aval)))*(Fval-Aval));
    double Vtetra2 = (((Dval-Cval).cross_product((Bval-Cval)))*(Fval-Cval));
    double Vtetra3 = (((Dval-Cval).cross_product((Gval-Cval)))*(Fval-Cval));
    double Vtetra4 = (((Eval-Aval).cross_product((Fval-Aval)))*(Dval-Aval));
    double Vtetra5 = (((Hval-Fval).cross_product((Eval-Fval)))*(Dval-Fval));
    double Vtetra6 = (((Hval-Fval).cross_product((Dval-Fval)))*(Gval-Fval));

//makes volume positive.
    Vtetra1 = (Vtetra1/(6.0-12.0*(Vtetra1<0)));
    Vtetra2 = (Vtetra2/(6.0-12.0*(Vtetra2<0)));
    Vtetra3 = (Vtetra3/(6.0-12.0*(Vtetra3<0)));
    Vtetra4 = (Vtetra4/(6.0-12.0*(Vtetra4<0)));
    Vtetra5 = (Vtetra5/(6.0-12.0*(Vtetra5<0)));
    Vtetra6 = (Vtetra6/(6.0-12.0*(Vtetra6<0)));

//adds all the volume of tetrahedrons to aquire the final volume of the hexahedron
    this->volume = (Vtetra1 + Vtetra2 + Vtetra3 + Vtetra4 + Vtetra5 + Vtetra6);
}
//-------------------------------------------------------------------------






