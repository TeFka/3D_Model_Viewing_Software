#include <iostream>
#include <vector>

#ifndef CELL_H
#define CELL_H
//------------------------------------------------------------------
class Cell
{
protected:
    colour col;
    int ID;
    int materialID;
    float weight;
    float density;
    float volume;
    std::vector<int> indices;
    vector centre_of_gravity;
public:
    virtual double getvolume();
    void setcolour( colour c);
};
//------------------------------------------------------------------
class Tetrahedron : public cell
{
private:
    vector3d p1, p2, p3, p4;
public:
    Tetrahedron(vector3d p1, p2, p3, p4);
    double getvolume();
};
//---------------------------------------------------------------
class Pyramid : public cell
{
private:
    vector3d p1, p2, p3, p4, p5;
public:
    Pyramid(vector3d p1, p2, p3, p4, p5);
    double getvolume();
};
//---------------------------------------------------------------
class Hexahedron : public cell
{
private:
    vector3d p1, p2, p3, p4, p5, p6, p7, p8;
public:
    Hexahedron(vector3d p1, p2, p3, p4, p5, p6, p7, p8);
    double getvolume();
};
#endif // CELL_H


