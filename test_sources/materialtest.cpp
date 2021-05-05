//materialtest.cpp
#include <iostream>
#include <string>
#include "../Inc/Material.h"

using namespace std;

int main(int argc, char *argv[])
{
	// Material class test
	std::cout<<"Material Class Test"<<std::endl;
	std::cout<<""<<std::endl;
	
	int errors = 0;
	
	// set up color
	Vector3D color1(188, 188, 188);
	Vector3D color2(184,73,73);
	
	//Material :: Material( int id, double d, string name, Vector3D col )
	Material m1(1, 2700.0, "aluminum", color1);

// -------------------------------------------------------------------------------------	
	
	/*Test GET functions*/	 

// -------------------------------------------------------------------------------------	

	
    //check ID
		
	std::cout<<"ID"<<std::endl;
	
	// if ID does not match, errors will be counted.
	if(m1.getID()!=1){
			errors++;
	}
	
	std::cout<<"--expected value: 1"<<std::endl;
	std::cout<<"--test results: "<<m1.getID()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;


// -------------------------------------------------------------------------------------	


	// check Density
	
	std::cout<<"Density"<<std::endl;
	
	// if density does not match, errors will be counted.
	if(m1.getDensity()!=2700.0){
			errors++;
	}
	
	std::cout<<"--expected value: 2700"<<std::endl;
	std::cout<<"--test results: "<<m1.getDensity()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;


// -------------------------------------------------------------------------------------	

	
	// check Name
	
	std::cout<<"Name"<<std::endl;
	
	// if name does not match, errors will be counted.
	if(m1.getName()!="aluminum"){
			errors++;
	}
	
	std::cout<<"--expected value: aluminum"<<std::endl;
	std::cout<<"--test results: "<<m1.getName()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;


// -------------------------------------------------------------------------------------	


	// check Color
	
	std::cout<<"Color"<<std::endl;

	// if name does not match, errors will be counted.
	if(m1.getColor().getx()!=188||m1.getColor().gety()!=188||m1.getColor().getz()!=188){
			errors++;
	}
	
	std::cout<<"--expected value: colorcode(188,188,188)"<<std::endl;
	std::cout<<"--test results: colorcode("<<m1.getColor().getx()<<","<<m1.getColor().gety()<<","<<m1.getColor().getz()<<")"<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;	


// -------------------------------------------------------------------------------------	

	/*Test SET functions*/

	m1.setID(0);
	m1.setName("copper");
	m1.setColor(color2);
	m1.setDensity(8960.0);
	
	std::cout<<"......NEW VARIABLES SET......"<<std::endl;
	std::cout<<""<<std::endl;


// -------------------------------------------------------------------------------------	

	// ID

	std::cout<<"ID"<<std::endl;
	
	if(m1.getID()!=0){
			errors++;
	}
	
	std::cout<<"--expected value: 0"<<std::endl;
	std::cout<<"--test results: "<<m1.getID()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;


// -------------------------------------------------------------------------------------	


	// Density
	
	std::cout<<"Density"<<std::endl;
	
	if(m1.getDensity()!=8960.0){
			errors++;
	}
	
	std::cout<<"--expected value: 8960"<<std::endl;
	std::cout<<"--test results: "<<m1.getDensity()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;


// -------------------------------------------------------------------------------------	

	
	// Name
	
	std::cout<<"Name"<<std::endl;
	
	if(m1.getName()!="copper"){
			errors++;
	}
	
	std::cout<<"--expected value: copper"<<std::endl;
	std::cout<<"--test results: "<<m1.getName()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;


// -------------------------------------------------------------------------------------	


	// Color
	
	std::cout<<"Color"<<std::endl;
	
	if(m1.getColor().getx()!=184||m1.getColor().gety()!=73||m1.getColor().getz()!=73){
			errors++;
	}	
	
	std::cout<<"--expected value: colorcode(184,73,73)"<<std::endl;
	std::cout<<"--test results: colorcode("<<m1.getColor().getx()<<","<<m1.getColor().gety()<<","<<m1.getColor().getz()<<")"<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;	


// -------------------------------------------------------------------------------------		

	return (errors==0)? 0:1;
   
}











