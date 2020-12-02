#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ModelClass.h>

using namespace std;

int main()
{
   Model theModel("models/ExampleModel2.mod");
   theModel.showMaterials();
   std::cout<<"Amount of vertices: "<<theModel.getVerticesAmount()<<std::endl;
   theModel.showVertices();
   std::cout<<"Amount of cells: "<<theModel.getCellAmount()<<std::endl;
   theModel.showCells();
   theModel.loadInfoToFile("myFile.txt");
    return 0;
}
