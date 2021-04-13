//vector3Dtest.cpp
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../Inc/Vector3D.h"

using namespace std;

int main()
{
	// Vector3D class test
	std::cout<<"Vector3D Class Test"<<std::endl;
	int errors = 0;
   
	Vector3D vector1(5.0,7.0,11.0);
	Vector3D vector2(13.0,17.0,3.0);
	
	if(vector1.getID()!=0||vector2.getID()!=0){
			errors++;
	}
   
   
	std::cout<<"Addition"<<std::endl;
	Vector3D vectorA = vector1 + vector2;
	if(vectorA.getx()!=18.0||vectorA.gety()!=24.0||vectorA.getz()!=14.0){
			errors++;
	}
   
   
	std::cout<<"Subtraction"<<std::endl;
	Vector3D vectorB = vector1 - vector2;
	if(vectorB.getx()!=(-8.0)||vectorB.gety()!=(-7.0)||vectorB.getz()!=8.0){
			errors++;
	}
   
   /*
	std::cout<<"Dot Product"<<std::endl;
	double vectorC = (vector1.xc*vector2.xc) + (vector1.yc*vector2.yc) + (vector1.zc*vector2.zc);
	if(vectorC != 217){
			errors++;
	}

 
	std::cout<<"Cross Product"<<std::endl;
	Vector3D vectorD.x = (vector1.yc*vector2.zc) - (vector1.zc*vector2.yc);
	Vector3D vectorD.y = (vector1.zc*vector2.xc) - (vector1.xc*vector2.zc);
	Vector3D vectorD.z = (vector1.xc*vector2.yc) - (vector1.yc*vector2.xc);
	if(vectorD.getx()!=(-6.0)||vectorD.gety()!=128.0||vectorD.getz()!=(-6.0)){
			errors++;
	}
	*/
	
	return (errors==0)? 1:0;
   
}











