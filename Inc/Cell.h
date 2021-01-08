//-------------------------------------------------------------
// Header file to store the interfaces of cell class and all its functions
//-------------------------------------------------------------

//Copyright michael michael (StudentID: 20143147)

// Required header files: iostream(for printing with cout), vector, string, fstream,
//                        Vector3D.h, Material.h, Cell.h****subject to change

//-------------------------------------------------------------
//-------------------------------------------------------------

#include <iostream>
#include <vector>
#include "../Inc/Vector3D.h"

#ifndef CELL_H
#define CELL_H
//------------------------------------------------------------------

class Vector3D;
// class 'Cell'
// cell class describes various parameters of the shape such as how many vertices it has, their positions, and the material it is made out of
//Stored values:
// Cell ID
// ID of materials that the Cell uses
// the type of Cell: 1 - hexahredal, 2 - pyramid, 3 - tetrahedral
// the std::vector array of index values
class Cell
{
protected:
    int ID;
    int type;
    int materialID;
    float weight;
    float volume;
	
    Vector3D centre_of_gravity;

    //array of all indices which each correspond to a vectex and its positions
    //knowledge of the vertices position is requited for volume calculations
    std::vector<int> indices;
public:
//cell class constructor
    Cell();
	// cell class destructor
	~cell();


    //function of cell class,getID
    //function to get ID of cell
    int getID();

    //function of cell class,getType
    //function to get type of cell
    int getType();

    //function of cell class,getMaterialID
    //function to get ID of the material, to gain access of the density of material, needed for weight calculation
    int getMaterialID();

    //function of cell class, getIndices
    //function to get indice array of model
    std::vector<int> getIndices();

    //function of cell class, getCentreOFGravity
    //function to find the centre of gravity of the cell
    Vector3D getCentreOFGravity();

    //function of cell class, getWeight
    //function to find the weight of the cell
    float getWeight();
//---------------------------------------------------------------
//set functions
    void setID(int);
    void setType(int);
    void setMaterialID(int);
    void setIndices(std::vector<int>);
    void pushIndice(int);
    void insertIndice(int,int);
};
//------------------------------------------------------------------
//subclass of class cell, class tetrahedron
class Tetrahedron : public Cell
{
private:

public:
//subclass tetrahedron constructor
    Tetrahedron();
	//destructor
  ~Tetrahedron();
  
    //function of subclass tetrahedron
    //function to get the volume of the tetrahedron cell
    double getvolume();

    //function of subclass tetrahedron
    //function to get the weight of the tetrahedron cell
    double getWeight();

    //function of subclass tetrahedron
    //function to get the contre of gravity of the tetrahedron cell
    Vector3D getCentreOFGravity();
};
//---------------------------------------------------------------
//subclass of class cell, class pyramid
class Pyramid : public Cell
{
private:

public:
//subclass tetrahedron constructor
  Pyramid();
	//destructor
	~Pyramid();

    //function of subclass pyramid
    //function to get the volume of the pyramid cell
    double getvolume();

    //function of subclass pyramid
    //function to get the weight of the pyramid cell
    double getWeight();

    //function of subclass pyramid
    //function to get the contre of gravity of the pyramid cell
    Vector3D getCentreOFGravity();
};
//---------------------------------------------------------------
//subclass of class cell, class hexahedron
class Hexahedron : public Cell
{
private:

public:
//constructor
    Hexahedron();
	
//	destructor
	 ~Hexahedron();
    //function of subclass hexahedron
    //function to get the volume of the hexahedron cell
    double getvolume();

    //function of subclass hexahedron
    //function to get the weight of the hexahedron cell
    double getWeight();

    //function of subclass hexahedron
    //function to get the contre of gravity of the hexahedron cell
    Vector3D getCentreOFGravity();
};
#endif // CELL_H


