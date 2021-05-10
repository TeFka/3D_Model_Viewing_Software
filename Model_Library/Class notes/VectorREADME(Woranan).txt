A class to create a vector3D object
Made by Woranan Kamonlattana

Class structure

Class 'Vector3D'
Creates a virtual Vector3D by storing information.
Class is made to be row major
Stored values:
      int ID;
      double x, y, z;
Available functions:
  public:
      Vector3D(double,double,double);
  setters:
      void setID(int)
      void setx(double)
      void sety(double)
      void setz(double)
  getters:
      int getID()
      double getx()
      double gety()
      double getz()
Available operator
      Vector3D+Vector3D
      Vector3D-Vector3D
      Vector3D*Vector3D
Function
      Vector3D cross_product
Constructor:
      Creates Vector3D object with specified values
Destructor
Copy constructor
      creates a copy of a specified object

The class enables to create a vector.
Different vectors can be added, substracted, multiplied and creates a vector product.