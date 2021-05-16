/*! \file Model.h File Reference
    \author   Copyright: \n Code part: Danielius Zurlys (StudentID: 20130611)
                         \n Documentation part: Chen xu  (StudentID: 20187733)
    \brief    Required header files: iostream(for printing with cout), vector, string, fstream,
                          Vector3D.h, Material.h, Cell.h
*/

#ifndef MODELCLASS_H_INCLUDED
#define MODELCLASS_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>
#include "Vector3D.h"
#include "Material.h"
#include "Cell.h"

/*! Struct 'cellInfo'
    \brief Temporarily stores cell information before a Cell object is created with it.
*/
struct cellInfo
{
    int ID;
    int materialID;
    int type;
    std::vector<int> indixes;
};

/*! Function hexToFloat() \n
    Function to convert hex color value to float value 
    \arg    getHexValue(): char - hex letter to convert
    \return value: a converted float value of color
    \note:
     1) Input hex value has to be in range [0;F]
*/
float hexToFloat(char);

/*! Function floatToHex() \n
    Function to convert float color value to hex value 
    \arg floatToHex(): float - float value to convert
    \return  a converted std::string letter of color
    \note 
     1) Input float value has to be in range [0;1.0]
*/
std::string floatToHex(float val);

/*! \class Model
    \brief Stores information about a 3D model retrieved from VTK file.
*/
class Model
{

private:

//! array of all vectors
    std::vector<Vector3D> vectors;

//! array of all materials used
    std::vector<Material> materials;

//! array of all cells
    std::vector<Cell> cells;

//! Vector3D object storing center of the model
    Vector3D modelCenter;

//! Vector3D object storing model dimensions
    Vector3D modelDimensions;

//! double storing model volume
    double modelVolume = 0;

//! double storing model weight
    double modelWeight = 0;

/*! Function of class Model, getVectorIndex() \n
    Function to get index in vectors array of vector with specified ID. 
    \arg  getVectorIndex(): int - ID to be searched for.
    \return  int - index of vector with specified ID.
    \note
     1) The function will return -1 if the ID is not found, which will most likely give error in the application.
*/
    int getVectorIndex(int);

/*! Function of class Model, getMaterialIndex() \n
    Function to get index in material array of Material with specified ID. 
    \arg  getMaterialIndex(): int - ID to be searched for.
    \return  int - index of Material with specified ID.
    \note 
     1) The function will return -1 if the ID is not found, which will most likely give error in the application.
*/
    int getMaterialIndex(int);

/*! Function with template of class Model, alignVectors() \n
    Function to sort the array of objects. \n
    type of objects is specified by template 
    \arg alignArrayID(): std::vector<T> - array of objects specified by template
    \return none(passed array sorted)
    \note
    1) The sorting is done based on the used object member 'ID', received with function 'getID()'
    \n   if the used object does not have this member and function, sorting function will not work and might crash
*/
    template<typename T>
    void alignArrayID(std::vector<T>&);

/*! Function of class Model, fixIDValues() \n
    Function to make all ID values of vectors and materials that coresponds to their position in array 
    \arg fixIDValues(): none.
    \return none(vector are given more convenient ID values)
*/
    void fixIDValues();

public:

/*! Default Model class constructor
      \note Action:
        \n  creates an empty model object
        \arg   none.
*/
    Model();

/*! Model class constructor
      \note  Action:
       \n     Load a 3D model from specified file.
       \arg   char - path to a model file.
*/
    Model(char*);

/*! Model class destructor
    \note Action:
    \n Clears vectors, materials and cells arrays.
*/
    ~Model();

/*! Copy constructor
    \note Action:
    \n copies vectors, materials, cells arrays and the model center information to a new Model object.
*/
    Model(const Model&);

/*! Function of class Model, loadModel()  \n
    Function to retrieve 3D model information from a VTK file 
    \arg  loadModel(): char - path to
    \return  bool - statement whether file could be open
    \note
    \n 1) The way function reads each file line and retrieves infromation:
    \n  Material: m material_ID material_density material_color(#000000 form hex code) material_name
    \n  Vector: v vector_ID x_position y_position z_position
    \n  Cell: c cell_ID cell_type(h - hexahedral, p - pyramid, t - tetrahedral) [cell_indices]
    \n 2) In case of file being written incorrectly, incorrect values might be written, errors may occur or program can crash.*/
    bool loadModel(const char*);

/*! Function of class Model, calcModelCenter() \n
    Function to calculate position of model center 
    \arg calcModelCenter(): none.
    \return  none(model center value updated)
    \note
     Model center position will become {0,0,0} if vector array is empty.
*/
    void calcModelCenter();

/*! Function of class Model, calcModelVolume() \n
    Function to calculate volume of model 
    \arg calcModelVolume(): none.
    \return  none(model volume value updated)
*/
    void calcModelVolume();

/*! Function of class Model, calcModelWeight() \n
    Function to calculate weight of model 
    \arg calcModelWeight(): none.
    \return value: none(model weight value updated)
*/
    void calcModelWeight();

/*! Function of class Model, getModelCenter()  \n
    Function to get position of model center 
    \arg getModelCenter(): none.
    \return  Vector3D - model center position
*/
    Vector3D getModelCenter();

/*! Function of class Model, getModelDimensions()  \n
    Function to get position of model dimensions 
    \arg getModelDimensions(): none.
    \return  Vector3D - vector showing model dimensions
*/
    Vector3D getModelDimensions();

/*! Function of class Model, getModelVolume()  \n
    Function to get volume of model 
    \arg getModelVolume(): none.
    \return  double - double showing model volume
*/
    double getModelVolume();

/*! Function of class Model, getModelWeight()  \n
    Function to set cells array of model 
    \arg getModelWeight(): none.
    \return  double - double showing model weight
*/
    double getModelWeight();

/*! Function of class Model, getVectors()   \n
    Function to set cells array of model 
    \arg getVectors(): none.
    \return  std::vector<Vector3D> - array of all model vectors
*/
    std::vector<Vector3D> getVectors();

/*! Function of class Model, getMaterials()  \n
    Function to set cells array of model 
    \arg getMaterials(): none.
    \return std::vector<Material*> - array of all model material pointers
*/
    std::vector<Material> getMaterials();

/*! Function of class Model, getCells()  \n
    Function to set cells array of model 
    \arg getCells(): none.
    \return std::vector<Cell*> - array of all model cell pointers
*/
    std::vector<Cell> getCells();

/*! Function of class Model, setVectors()   \n
    Function to set cells array of model 
    \arg setVectors(): std::vector<Vector3D> - new array to be set.
    \return none
*/
    void setVectors(std::vector<Vector3D>);

/*! Function of class Model, setMaterials()   \n
    Function to set cells array of model 
    \arg setMaterials(): std::vector<Material> - new array to be set.
    \return  none
*/
    void setMaterials(std::vector<Material>);

/*! Function of class Model, setCells()    \n
    Function to set cells array of model 
    \arg setCells(): std::vector<Cell> - new array to be set.
    \return none
*/
    void setCells(std::vector<Cell>);

/*! Function of class Model, getCells()  \n
    Function to get cells array of model 
    \arg getCells(): none.
    \return  cell - the retrieved cell
*/
    Cell getCell(int);

/*! Function of class Model, getVector()
    Function to get a specific vector   \n
    \arg getVector(): none.
    \return  cell - the retrieved cell  
*/
    Vector3D getVector(int);

/*! Function of class Model, getMaterial()   \n
    Function to get material array of model 
    \arg getMaterial(): none.
    \return  int - amount of vectors
*/
    Material getMaterial(int);

/*! Function of class Model, getVectorsAmount()  \n
    Function to get amount of vectors 
    \arg getVectorAmount(): none.
    \return  int - amount of vectors
*/
    int getVectorAmount();

/*! Function of class Model, getCellAmount()   \n
    Function to get amount of cells  
    \arg getCellAmount(): none.
    \return  int - amount of cells
*/
    int getCellAmount();

/*! Function of class Model, getMaterialAmount()   \n
    Function to get amount of materials 
    \arg getMaterialAmount(): none.
    \return int - amount of Material
*/
    int getMaterialAmount();

/*! Function of class Model, showMaterials()   \n
    Function to show information about all materials 
    \arg showMaterials(): none.
    \return none(information printed)
*/
    void showMaterials();

/*! Function of class Model, showVectors()   \n
    Function to show information about all vectors 
    \arg showVectors(): none.
    \return none(information printed)
*/
    void showVectors();

/*! Function of class Model, showCells()  \n
    Function to show information about all cells 
    \arg showCells(): none.
    \return  none(information printed)
*/
    void showCells();

/*! Function of class Model, loadInfoToFile()  \n
    Function to load model information into specified txt file. 
    \arg getvectorsAmount(): char - path to specified txt file
    \return none(information loaded)
*/
    void loadInfoToFile(char*);
};

#endif //! MODELCLASS_H_INCLUDED
