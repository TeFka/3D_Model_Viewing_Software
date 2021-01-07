//This is lib for the material class.
//It should be three parts for material ID, color, and density.
#include <string>
#include <iostream>
using namespace std;




class  material{
   
private:// member variables.

    int ID;
    int Density;
    string Name;
    string Color;
  


public:
    material( int id, int density, string name, string colour);//a constructor to initialise member vaiables.
   
//----------provide a function to allow them to be read/and modified.   
   int getID();
 
   int getdensity();

   string getcolor();

   void setID( int id );
   void setcolor( string c );
   void setdensity( int d );

};
//material class is over.
//--------------------------------------------
