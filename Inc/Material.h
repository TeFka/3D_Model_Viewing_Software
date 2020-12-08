#include <iostream>
#include <string>
#include "../Inc/Vector3D.h"
//This class is for the material.
//It should be three parts for material ID, color, and density.

class Vector3D;

class  Material{
private:// member variables.
    int ID;
    std::string name;
    Vector3D color;
    double density;

public:
    Material();
    Material(int, Vector3D, double);//a constructor to initialise member vaiables.
   ~Material();      //a destructor to delete memory in constructor.
//----------provide a function to allow them to be read/and modified.
   int getID();
   std::string getName();
   Vector3D getColor();
   double getDensity();

   void setID(int);
   void setName(std::string);
   void setColor(Vector3D);
   void setDensity(double);
};
