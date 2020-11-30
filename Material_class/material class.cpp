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

//--------------------------------------------
material :: material( int id, double c[3], double d ) : ID(id), color(c), density(d) {}
	//this->ID = id ;
	//this->color = c ;
	//this->density = d ;

//for ID
int material :: getID(){//get(accessor) function to read.
    return this->ID;
}

void material :: setID( int id ){//set(mutator) function to modify.
    this->ID = id;
}

//for color
double material :: getcolor(){
    return this->color;
}

void material :: setcolor( double color[4] ){
    this->color = c;
}

//for density
double material :: getdensity(){
    return this->density;
}

void material :: setdensity(){
    this->density = d;
}


}