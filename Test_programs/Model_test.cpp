#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../Inc/Model.h"
using namespace std;

int main()
{
   // Model class test
   Model theModel("ExampleModel.mod");
   theModel.showMaterials();
   std::cout<<"Amount of vertices: "<<theModel.getVectorAmount()<<std::endl;
   theModel.showVectors();
   std::cout<<"Amount of cells: "<<theModel.getCellAmount()<<std::endl;
   theModel.showCells();
   std::cout<<"Model center: "<<theModel.getModelCenter().getx()<<"  "<<theModel.getModelCenter().gety()<<""<<theModel.getModelCenter().getz()<<std::endl;
   theModel.loadInfoToFile("testFile.txt");
    return 0;
}
