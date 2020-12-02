#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ModelClass.h>
#include <Matrix.h>

using namespace std;

int main()
{
   Matrix theMat1(MAT3x3);
   Matrix theMat2(MAT3x3);

   theMat1.setValue(0,0,0.0f);
   theMat1.setValue(0,1,1.0f);
   theMat1.setValue(0,2,1.0f);
   theMat1.setValue(1,0,2.0f);
   theMat1.setValue(1,1,2.0f);
   theMat1.setValue(1,2,2.0f);
   theMat1.setValue(2,0,2.0f);
   theMat1.setValue(2,1,1.0f);
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

   //theMat1 = theMat1*theMat2;
   theMat1.rotateMatrix(50,0,1.0,0);
   for(int i = 0;i<3;i++){
    for(int b = 0;b<3;b++){
        std::cout<<theMat1(i,b)<<" ";
    }
    std::cout<<std::endl;
   }
    return 0;
}
