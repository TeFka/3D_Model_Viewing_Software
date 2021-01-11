A class to read and store model data.
Made by Danielius Zurlys

Class structure:

Class 'Model'
Stores information about a 3D model retrieved from VTK file.
Stored values:
      An std::vector array of model vectors
      An std::vector array of model materials
      An std::vector array of model cells
      a Vector3D of model center point.
Available functions:
  private:
      int getVectorIndex(int)
      int getMaterialIndex(int);
      void alignVectors()
      void alignCells()      
      void alignMaterials()
      void fixIDValues();
  public:
      void loadModel(char*)
      void calcModelCenter()
      int getVectorsAmount()
      int getCellAmount()
      Vector3D getModelCenter()
      std::vector<Vector3D> getVectors()
      std::vector<Material*> getMaterials()
      std::vector<Cell*> getCells()
      void showMaterials()
      void showVectors()
      void showCells()
      void loadInfoToFile(char*)

Constructor:
      Loads 3D model information from specified file
Destructor:
      Clears vector, material and cell arrays.
Copy constructor
      creates a copy of a specified Model object

Class allows to read and store data of a VTK model file. The model position center is calculated, as well as gravity center volume and weight of each cell of th, it will be model.
It is possible to save model data to a difference file it will be stored in the same format as the VTK files.