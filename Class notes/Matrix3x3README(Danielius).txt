A class to create a 3x3 matrix object
Made by Danielius Zurlys

Class structure:

Class 'Matrix3x3'
Creates a virtual Matrix3x3 by storing information.
Class is made to be row major
Stored values:
       int rowDimension;
       int columnDimension;
Available functions:
  public:
      void setValue(int, int, double);
      std::vector<std::vector<double>> getMatrix3x3();
      void setIdentityMatrix3x3();
      void invert();
      void transpose();
      void rotateMatrix3x3(double, double, double, double);
Available operator overloading
      Matrix3x3()
      Matrix3x3+Matrix3x3
      Matrix3x3-Matrix3x3
      Matrix3x3*Matrix3x3
      Matrix3x3*Vector3D
Constructor1:
      Creates empty matrix with all values set to zero
Constructor2:
      Creates matrix with specified diagonal values
Destructor:
      clears array of matrix values
Copy constructor
      creates a copy of a specified object

The class enables to create a matrix, perform inversion, transpose and rotation operation.
Different matrices can be added, substracted and multiplied.