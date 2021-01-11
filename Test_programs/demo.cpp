#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../Inc/Model.h"
#include "../Inc/Matrix3x3.h"
using namespace std;

int main()
{
   // Matrix class test
   std::cout<<"MATRIX TEST"<<std::endl;

   Matrix3x3 theMat1;
   Matrix3x3 theMat2;
   Matrix3x3 rotationMat(1.0);
   rotationMat = rotationMat.getRotationMatrix3x3(60,1.0,1.0,0.0);

   theMat1.setValue(0,0,0.0f);
   theMat1.setValue(0,1,100.0f);
   theMat1.setValue(0,2,1.0f);
   theMat1.setValue(1,0,213.0f);
   theMat1.setValue(1,1,2.0f);
   theMat1.setValue(1,2,23.0f);
   theMat1.setValue(2,0,2.0f);
   theMat1.setValue(2,1,12.0f);
   theMat1.setValue(2,2,2.0f);

   theMat2.setValue(0,0,4.0f);
   theMat2.setValue(0,1,2.0f);
   theMat2.setValue(0,2,1.0f);
   theMat2.setValue(1,0,2.0f);
   theMat2.setValue(1,1,0.0f);
   theMat2.setValue(1,2,4.0f);
   theMat2.setValue(2,0,9.0f);
   theMat2.setValue(2,1,4.0f);
   theMat2.setValue(2,2,2.0f);
   std::cout<<"First matrix"<<std::endl;
   for(int i = 0;i<3;i++){
    for(int b = 0;b<3;b++){
        std::cout<<theMat1(i,b)<<" ";
    }
    std::cout<<std::endl;
   }

   std::cout<<"Second matrix"<<std::endl;
   for(int i = 0;i<3;i++){
    for(int b = 0;b<3;b++){
        std::cout<<theMat2(i,b)<<" ";
    }
    std::cout<<std::endl;
   }

   Vector3D vecx(15.0,22.0,69.0);

   std::cout<<"Side vector"<<std::endl;
   std::cout<<vecx.getx()<<"  "<<vecx.gety()<<"  "<<vecx.getz()<<std::endl;

   //calculations
   vecx = theMat1*vecx;

   std::cout<<"Multiplication of first matrix and vector"<<std::endl;
   std::cout<<vecx.getx()<<"  "<<vecx.gety()<<"  "<<vecx.getz()<<std::endl;

   theMat1 = theMat1*theMat2;

   std::cout<<"Multiplication of first matrix and second matrix"<<std::endl;
   for(int i = 0;i<3;i++){
    for(int b = 0;b<3;b++){
        std::cout<<theMat1(i,b)<<" ";
    }
    std::cout<<std::endl;
   }
   theMat1 = theMat1.getRotationMatrix3x3(50,0,1.0,0);
   std::cout<<"Multiplied matrix rotated by 50 degrees along y axis"<<std::endl;
   for(int i = 0;i<3;i++){
    for(int b = 0;b<3;b++){
        std::cout<<theMat1(i,b)<<" ";
    }
    std::cout<<std::endl;
   }
   
   std::cout<<std::endl;

   // Model class test
   std::cout<<"MODEL TEST"<<std::endl;

   char filePath[300];
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
