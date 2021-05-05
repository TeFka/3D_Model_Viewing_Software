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
struct cellInfo
{
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
//      int getMaterialIndex(int);
//      void alignVectors()
//      void alignCells()
//      void alignMaterials()
//      void fixIDValues();
//  public:
//      void loadModel(char*)
//      void calcModelCenter()
//      int getVectorsAmount()
//      int getCellAmount()
//      Vector3D getModelCenter()
//      std::vector<Vector3D> getVectors()
//      std::vector<Material*> getMaterials()
//      std::vector<Cell*> getCells()
//      void showMaterials()
//      void showVectors()
//      void showCells()
//      void loadInfoToFile(char*)
//
//Constructor:
//      Loads 3D model information from specified file
//Destructor:
//      Clears vector, material and cell arrays.
//Copy constructor
//      creates a copy of a specified Model object

class Model
{

private:

// array of all vectors
    std::vector<Vector3D> vectors;

// array of all materials used
    std::vector<Material> materials;

// array of all cells
    std::vector<Cell> cells;

//Vector3D object storing center of the model
    Vector3D modelCenter;

//Vector3D object storing model dimensions
    Vector3D modelDimensions;

//Function of class Model, getVectorIndex()
//Function to get index in vectors array of vector with specified ID.
    int getVectorIndex(int);

//Function of class Model, getMaterialIndex()
//Function to get index in material array of Material with specified ID.
    int getMaterialIndex(int);

//Function with template of class Model, alignVectors()
//Function to sort the array of objects.
//type of objects is specified by template
    template<typename T>
    void alignArrayID(std::vector<T>&);

//Function of class Model, fixIDValues()
//Function to make all ID values of vectors and materials that coresponds to their position in array
    void fixIDValues();

public:

//Default Model class constructor
    Model();

//Model class constructor
    Model(char*);

//Model class destructor
    ~Model();

//Copy constructor
    Model(const Model&);

//Function of class Model, loadModel()
//Function to retrieve 3D model information from a VTK file
    bool loadModel(const char*);

//Function of class Model, calcModelCenter()
//Function to calculate position of model center
    void calcModelCenter();

//Function of class Model, getModelCenter()
//Function to get position of model center
    Vector3D getModelCenter();

//Function of class Model, getModelDimensions()
//Function to get position of model dimensions
    Vector3D getModelDimensions();

//Function of class Model, getVectors()
//Function to get vector array of model
    std::vector<Vector3D> getVectors();

//Function of class Model, getMaterials()
//Function to get materials array of model
    std::vector<Material> getMaterials();

//Function of class Model, getCells()
//Function to get cells array of model
    std::vector<Cell> getCells();

//Function of class Model, setVectors()
//Function to set vector array of model
    void setVectors(std::vector<Vector3D>);

//Function of class Model, setMaterials()
//Function to set materials array of model
    void setMaterials(std::vector<Material>);

//Function of class Model, setCells()
//Function to set cells array of model
    void setCells(std::vector<Cell>);

//Function of class Model, getCells()
//Function to get cells array of model
    Cell getCell(int);

//Function of class Model, getCells()
//Function to get cells array of model
    Vector3D getVector(int);

//Function of class Model, getCells()
//Function to get cells array of model
    Material getMaterial(int);

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
