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
	std::cout<<""<<std::endl;
	
	int errors = 0;
   
    // define vector coordinates
	Vector3D vector1(5.0,7.0,11.0);
	Vector3D vector2(13.0,17.0,3.0);
	
	// set vector ID
	vector1.setID(1);
	vector2.setID(2);

// -------------------------------------------------------------------------------------	
	
	//check ID
	//if ID does not match, errors will be counted.
	
	std::cout<<"ID"<<std::endl;
	
	if(vector1.getID()!=1||vector2.getID()!=2){
			errors++;
	}
	std::cout<<"--expected value: vector1 = 1, vector2 = 2"<<std::endl;
	std::cout<<"--test results: vector1 = "<<vector1.getID()<<", vector2 = "<<vector2.getID()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;

// -------------------------------------------------------------------------------------	

	/*Test GET functions*/
	
// -------------------------------------------------------------------------------------	

   
	// Addition
	
	std::cout<<"Addition"<<std::endl;
	
	// perform addition operation
	Vector3D vectorA = vector1 + vector2;
	
	// check if value of x, y, z is correct. If not, error will be counted.
	if(vectorA.getx()!=18.0||vectorA.gety()!=24.0||vectorA.getz()!=14.0){
			errors++;
	}
	
	std::cout<<"--expected value: (18.0,24.0,14.0)"<<std::endl;
	std::cout<<"--test results: ("<<vectorA.getx()<<","<<vectorA.gety()<<","<<vectorA.getz()<<")"<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;


// -------------------------------------------------------------------------------------	


	// Subtraction
	
	std::cout<<"Subtraction"<<std::endl;
	
	// perform subtraction operation
	Vector3D vectorB = vector1 - vector2;
	
	// check if value of x, y, z is correct. If not, error will be counted. 
	if(vectorB.getx()!=(-8.0)||vectorB.gety()!=(-10.0)||vectorB.getz()!=8.0){
			errors++;
	}
	
	std::cout<<"--expected value: (-8.0,-10.0,8.0)"<<std::endl;
	std::cout<<"--test results: ("<<vectorB.getx()<<","<<vectorB.gety()<<","<<vectorB.getz()<<")"<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;


// -------------------------------------------------------------------------------------	
   
   
	// Dot product
	
	std::cout<<"Dot Product"<<std::endl;
	
	// perform dot product operation
	double vectorC = vector1*vector2;
	
	// check if the dot product is correct. If not, error will be counted.
	if(vectorC != 217){
			errors++;
	}
	
	std::cout<<"--expected value: 217"<<std::endl;
	std::cout<<"--test results: "<<vectorC<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;


// -------------------------------------------------------------------------------------	


	// Cross product
	
	std::cout<<"Cross Product"<<std::endl;
	
	// perform cross product operation
	Vector3D vectorD = vector1.cross_product(vector2);
	
	// check if value of x, y, z is correct. If not, error will be counted. 
	if(vectorD.getx()!=(-166.0)||vectorD.gety()!=128.0||vectorD.getz()!=(-6.0)){
			errors++;
	}
	
	std::cout<<"--expected value: (-166.0,128.0,-6.0)"<<std::endl;
	std::cout<<"--test results: ("<<vectorD.getx()<<","<<vectorD.gety()<<","<<vectorD.getz()<<")"<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;


// -------------------------------------------------------------------------------------	
	
	/*Test SET functions*/

	vector1.setx(1);
	vector1.sety(1);
	vector1.setz(1);
	vector2.setx(2);
	vector2.sety(2);
	vector2.setz(2);
	
	std::cout<<"......NEW COORDINATES SET......"<<std::endl;
	std::cout<<""<<std::endl;
	
// -------------------------------------------------------------------------------------	


	//Addition
	std::cout<<"Addition"<<std::endl;
	vectorA = vector1 + vector2;
	if(vectorA.getx()!=3.0||vectorA.gety()!=3.0||vectorA.getz()!=3.0){
			errors++;
	}
	std::cout<<"--expected value: (3.0,3.0,3.0)"<<std::endl;
	std::cout<<"--test results: ("<<vectorA.getx()<<","<<vectorA.gety()<<","<<vectorA.getz()<<")"<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
 
 
// -------------------------------------------------------------------------------------	
 
 
	//Subtraction
	std::cout<<"Subtraction"<<std::endl;
	vectorB = vector1 - vector2;
	if(vectorB.getx()!=(-1.0)||vectorB.gety()!=(-1.0)||vectorB.getz()!=(-1.0)){
			errors++;
	}
	std::cout<<"--expected value: (-1.0,-1.0,-1.0)"<<std::endl;
	std::cout<<"--test results: ("<<vectorB.getx()<<","<<vectorB.gety()<<","<<vectorB.getz()<<")"<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
 
 
// -------------------------------------------------------------------------------------	
 
 
	//Dot product
	std::cout<<"Dot Product"<<std::endl;
	vectorC = vector1*vector2;
	if(vectorC != 6){
			errors++;
	}
	std::cout<<"--expected value: 6"<<std::endl;
	std::cout<<"--test results: "<<vectorC<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;


// -------------------------------------------------------------------------------------	


	//Cross product
	std::cout<<"Cross Product"<<std::endl;
	vectorD = vector1.cross_product(vector2);
	
	if(vectorD.getx()!=0.0||vectorD.gety()!=0.0||vectorD.getz()!=0.0){
			errors++;
	}
	std::cout<<"--expected value: (0.0,0.0,0.0)"<<std::endl;
	std::cout<<"--test results: ("<<vectorD.getx()<<","<<vectorD.gety()<<","<<vectorD.getz()<<")"<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;


// -------------------------------------------------------------------------------------	
	
	return (errors==0)? 0:1;
   
}











