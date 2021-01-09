#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../Inc/Model.h"
using namespace std;

int main()
{
   // Model class test
   char filePath[200];
   std::cout<<"Write full path to model file"<<std::endl;
   cin>>filePath;
   std::cout<<"path: "<<filePath<<std::endl;
   Model theModel(filePath);
   //show material information
   theModel.showMaterials();
   //show vector information
   std::cout<<"Amount of vectors: "<<theModel.getVectorAmount()<<std::endl;
   theModel.showVectors();
   //show cell information
   std::cout<<"Amount of cells"<<theModel.getCellAmount()<<std::endl;
   theModel.showCells();
   //general model information
   std::cout<<"Model center: "<<theModel.getModelCenter().getx()<<"  "<<theModel.getModelCenter().gety()<<"  "<<theModel.getModelCenter().getz()<<std::endl;
   //writing model information to file
   theModel.loadInfoToFile("testFile.txt");
    return 0;
}
