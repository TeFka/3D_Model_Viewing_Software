// Class 'Material'
//It should be three parts for material ID, color, and density.
//----------------------------------------------
//Copyright  Chen Xu (student ID : 20187733)
//----------------------------------------------



#include <string>
#include <iostream>
using namespace std;




class  material{
   
private:

// member variables.

    int ID;
    int Density;
    string Name;
    string Color;
  


public:
   
//Default:
   material();

//Constructor:
   material( int id, int density, string name, string colour);

//Destructor:
   ~material();
   
//Available functions:  
   int getID();
   int getdensity();
   string getcolor();

   void setID( int id );
   void setcolor( string c );
   void setdensity( int d );

//Copy constructor:
   material(const material & m);

};

   
   

   
//------------------------------------------------------
//material class is over.
//--------------------------------------------
