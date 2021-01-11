//-------------------------------------------------------------
// Header file to store the interfaces of cell class and all its functions
//-------------------------------------------------------------

//Copyright michael michael (StudentID: 20143147)

// Required header files: iostream(for printing with cout), vector, string, fstream,
//                        Vector3D.h, Material.h, Cell.h

//--------------------------------------------------------------------
//--------------------------------------------------------------------
#include <iostream>
#include <vector>
#include "../Inc/Vector3D.h"
#include "../Inc/Material.h"

#ifndef CELL_H
#define CELL_H
//------------------------------------------------------------------
// class 'Cell'
// cell class describes various parameters of the shape such as how many vertices it has, their positions, and the material it is made out of
//Stored values:
// Cell ID
// ID of materials that the Cell uses
// the type of Cell: 1 - hexahedral, 2 - pyramid, 3 - tetrahedral
// the std::vector array of index values
class Cell
{
protected:
    int ID;
    int type;
    int materialID;
    double weight;
    double volume;

    Vector3D centre_of_gravity;

    //array of all indices which each correspond to a vertex and its positions
    //knowledge of the vertices position is requited for volume calculations
    std::vector<int> indices;
public:
    //cell class constructor
    Cell(int,int,int,std::vector<int>);

    //cell class copy constructor
    Cell(const Cell&);

    // cell class destructor
    ~Cell();

//-----------------------------------------------------------
//get functions

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
    Vector3D getCentreOfGravity();

    //function of cell class, getWeight
    //function to find the weight of the cell
   double getWeight();
   double getVolume();
//---------------------------------------------------------------
//set functions
    void setID(int);
    void setType(int);
    void setMaterialID(int);
    void setIndices(std::vector<int>);
    void pushIndice(int);
    void insertIndice(int,int);
    void setIndice(int,int);

//calculation functions

    //function of class Cell calcWeight()
    //function to calculate weight of the cell
    void calcWeight(std::vector<Material>);

    //function of class Cell calcCenterOfGravity()
    //function to calculate center of gravity position of the cell
    void calcCentreOfGravity(std::vector<Vector3D>);
};
//------------------------------------------------------------------
//subclass of class cell, class tetrahedron
class Tetrahedron : public Cell
{
private:

public:
//subclass tetrahedron constructor
    Tetrahedron(int,int,int,std::vector<int>,std::vector<Vector3D>,std::vector<Material>);

    //copy contructor
    Tetrahedron(const Cell&);
    //destructor
    ~Tetrahedron();

    //function of subclass tetrahedron
    //function to get the volume of the tetrahedron cell
    void calculateVolume(std::vector<Vector3D>);

};
//---------------------------------------------------------------
//subclass of class cell, class pyramid
class Pyramid : public Cell
{
private:

public:
//subclass pyramid constructor
    Pyramid(int,int,int,std::vector<int>,std::vector<Vector3D>,std::vector<Material>);

    //copy contructor
    Pyramid(const Cell&);

    //destructor
    ~Pyramid();

    //function of subclass pyramid
    //function to get the volume of the pyramid cell
    void calculateVolume(std::vector<Vector3D>);

};
//---------------------------------------------------------------
//subclass of class cell, class hexahedron
class Hexahedron : public Cell
{
private:

public:
//constructor
    Hexahedron(int,int,int,std::vector<int>,std::vector<Vector3D>,std::vector<Material>);

    //copy contructor
    Hexahedron(const Cell&);

    //destructor
    ~Hexahedron();
    //function of subclass hexahedron
    //function to get the volume of the hexahedron cell
    void calculateVolume(std::vector<Vector3D>);

};
#endif // CELL_H


