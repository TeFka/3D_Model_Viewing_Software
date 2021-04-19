//vector3Dtest.cpp
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../Inc/Vector3D.h"

using namespace std;

int main(int argc, char *argv[])
{
	// Vector3D class test
	std::cout<<"Vector3D Class Test"<<std::endl;
	int errors = 0;
   
	Vector3D vector1(5.0,7.0,11.0);
	Vector3D vector2(13.0,17.0,3.0);
	
/*	
	if(vector1.getID()!=0||vector2.getID()!=0){
			errors++;
	}
	std::cout<<"errors count:"<<errors<<std::endl;
*/
   
	//Addition
	std::cout<<"Addition"<<std::endl;
	Vector3D vectorA = vector1 + vector2;
	if(vectorA.getx()!=18.0||vectorA.gety()!=24.0||vectorA.getz()!=14.0){
			errors++;
	}
	std::cout<<"errors count:"<<errors<<std::endl;
   
	//Subtraction
	std::cout<<"Subtraction"<<std::endl;
	Vector3D vectorB = vector1 - vector2;
	if(vectorB.getx()!=(-8.0)||vectorB.gety()!=(-10.0)||vectorB.getz()!=8.0){
			errors++;
	}
	std::cout<<"errors count:"<<errors<<std::endl;
   
	//Dot product
	std::cout<<"Dot Product"<<std::endl;
	double vectorC = vector1*vector2;
	if(vectorC != 217){
			errors++;
	}
	std::cout<<"errors count:"<<errors<<std::endl;

	//Cross product
	std::cout<<"Cross Product"<<std::endl;
	Vector3D vectorD = vector1.cross_product(vector2);
	
	if(vectorD.getx()!=(-166.0)||vectorD.gety()!=128.0||vectorD.getz()!=(-6.0)){
			errors++;
	}
	std::cout<<"errors count:"<<errors<<std::endl;
	
	return (errors==0)? 0:1;
   
}











