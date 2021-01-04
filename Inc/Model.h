//-------------------------------------------------------------
// Header file to store the interfaces of model class and all their functions
//-------------------------------------------------------------

//Copyright Danielius Zurlys (StudentID: 20130611)

// Required header files: iostream(for printing with cout), vector, string, fstream,
//                        Vector3D.h, Material.h, Cell.h

//-------------------------------------------------------------
//-------------------------------------------------------------

#ifndef MODELCLASS_H_INCLUDED
#define MODELCLASS_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include<math.h>
#include "../Inc/Vector3D.h"
#include "../Inc/Material.h"
#include "../Inc/Cell.h"

// Structure 'cellInfo'
// Temporarily stores cell information before a Cell object is created with it.
//Stored values:
// Cell ID
// ID of materials that the Cell uses
// the type of Cell: 1 - hexahredal, 2 - pyramid, 3 - tetrahedral
// the std::vector array of index values
struct cellInfo{
    int ID;
    int materialID;
    int type;
    std::vector<int> indixes;
};

//Function hexToFloat()
//Function to convert hex color value to float value
float hexToFloat(char);

//Function floatToHex()
//Function to convert float color value to hex value
std::string floatToHex(float val);

// Class 'Model'
// Stores information about a 3D model retrieved from VTK file.
//Stored values:
//      An std::vector array of model vectors
//      An std::vector array of model materials
//      An std::vector array of model cells
//      a Vector3D of model center point.
//Available functions:
//  private:
//      int getVectorIndex(int)
//      Material getMaterial(int)
//      void alignVectors()
//      void alignCells()
//      void alignMaterials()
//      void loadModel(char*)
//      void calcModelCenter()
//  public:
//      int getVectorsAmount()
//      int getCellAmount()
//      void showMaterials()
//      void showVectors()
//      void showCells()
//      void loadInfoToFile(char*)
//
//Constructor:
//      Loads 3D model information from specified file
//Destructor:
//      Makes address value of the next node NULL
//Copy constructor
//      creates a copy of a specified object

class Model{

private:

// array of all vectors
std::vector<Vector3D> vectors;

// array of all materials used
std::vector<Material*> materials;

// array of all cells
std::vector<Cell*> cells;

//Vector3D object storing center of the model
Vector3D modelCenter;

//Function of class Model, getVectorIndex()
//Function to get index in vectors array of vector with specified ID.
int getVectorIndex(int);

//Function of class Model, getMaterial()
//Function to get material with specified ID.
Material getMaterial(int);

//Function of class Model, alignVectors()
//Function to sort the vectors array.
void alignVectors();

//Function of class Model, alignCells()
//Function to sort the cells array.
void alignCells();

//Function of class Model, alignMaterials()
//Function to sort the materials array.
void alignMaterials();

//Function of class Model, loadModel()
//Function to retrieve 3D model information from a VTK file
bool loadModel(char*);

//Function of class Model, calcModelCenter()
//Function to calculate position of model center
void calcModelCenter();

public:

//Model class constructor
Model(char*);

//Model class destructor
~Model();

//Copy constructor
Model(const Model&);

//Function of class Model, getModelCenter()
//Function to get position of model center
Vector3D getModelCenter();

//Function of class Model, getVectors()
//Function to get vector array of model
std::vector<Vector3D> getVectors();

//Function of class Model, getMaterials()
//Function to get materials array of model
std::vector<Material*> getMaterials();

//Function of class Model, getCells()
//Function to get cells array of model
std::vector<Cell*> getCells();

//Function of class Model, getVectorsAmount()
//Function to get amount of vectors
int getVectorAmount();

//Function of class Model, getCellAmount()
//Function to get amount of cells
int getCellAmount();

//Function of class Model, showMaterials()
//Function to show information about all materials
void showMaterials();

//Function of class Model, showVectors()
//Function to show information about all vectors
void showVectors();

//Function of class Model, showCells()
//Function to show information about all cells
void showCells();

//Function of class Model, loadInfoToFile()
//Function to load model information into specified txt file.
void loadInfoToFile(char*);
};

#endif // MODELCLASS_H_INCLUDED
