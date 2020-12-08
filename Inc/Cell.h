#include <iostream>
#include <vector>
#include "../Inc/Vector3D.h"

#ifndef CELL_H
#define CELL_H
//------------------------------------------------------------------

class Vector3D;

class Cell
{
protected:
    int ID;
    int type;
    int materialID;
    float weight;
    float volume;
    std::vector<int> indices;
    Vector3D centre_of_gravity;
public:
    Cell();
    int getID();
    int getType();
    int getMaterialID();
    std::vector<int> getIndices();
    Vector3D getCentreOFGravity();

    void setID(int);
    void setType(int);
    void setMaterialID(int);
    void setIndices(std::vector<int>);
    void pushIndice(int);
    void insertIndice(int,int);
};
//------------------------------------------------------------------
class Tetrahedron : public Cell
{
private:

public:
    Tetrahedron();
    double getvolume();
};
//---------------------------------------------------------------
class Pyramid : public Cell
{
private:

public:
    Pyramid();
    double getvolume();
};
//---------------------------------------------------------------
class Hexahedron : public Cell
{
private:

public:
    Hexahedron();
    double getvolume();
};
#endif // CELL_H


