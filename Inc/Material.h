// Class 'Material'
//It should be three parts for material ID, color, and density.
//----------------------------------------------
//Copyright  Chen Xu (student ID : 20187733)
//----------------------------------------------



#include <string>
#include <iostream>
#include "Vector3D.h"
using namespace std;


class  material{
   
private:

// member variables.

    int ID;
    double Density;
    string Name;
    Vector3D Color;
  


public:
   
//Default:
   material();


//Constructor:
   material( int id, double d, std::string name, Vector3D col);

//Destructor:
   ~material();
   
//Available functions:  
   int getID();
   std::string getName();
   double getDensity();
   Vector3D getColor();
  

   void setID( int id );
   void setName( std::string name );
   void setcolor( Vector3D col );
   void setdensity( double d );
 
//Copy constructor:
   material(const material & m);
   

};

   
   

   
//------------------------------------------------------
//material class is over.
//--------------------------------------------
