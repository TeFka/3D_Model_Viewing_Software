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

    Vector3D vecx(15.0,22.0,69.0);
    vecx = theMat1*vecx;
   theMat1 = theMat1*theMat2;
   //theMat1.rotateMatrix(50,0,1.0,0);
   std::cout<<"vec: "<<vecx.getx()<<"  "<<vecx.gety()<<"  "<<vecx.getz()<<std::endl;
   for(int i = 0;i<3;i++){
    for(int b = 0;b<3;b++){
        std::cout<<rotationMat(i,b)<<" ";
    }
    std::cout<<std::endl;
   }
    return 0;
}
