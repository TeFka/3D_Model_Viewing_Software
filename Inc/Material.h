//This class is for the material.
//It should be three parts for material ID, color, and density.

class  material{
private:// member variables.
    int ID;
    std::string name;
    double color[3];
    double density;

public:
    material( int id, double c[3], double d );//a constructor to initialise member vaiables.
   ~material();      //a destructor to delete memory in constructor.
//----------provide a function to allow them to be read/and modified.   
   int getID();
   double getcolor();
   double getdensity();

   void setID( int id );
   void setcolor( double c[3]);
   void setdensity( double d );
}