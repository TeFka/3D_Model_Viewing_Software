//materialtest.cpp
#include <iostream>
#include <string>
#include "../Inc/Material.h"

using namespace std;

int main(int argc, char *argv[])
{
	// Material class test
	std::cout<<"Material Class Test"<<std::endl;
	int errors = 0;
	
	Vector3D color(188, 188, 188);
	
	//Material :: Material( int id, double d, string name, Vector3D col )
	Material m1(1, 2700.0, "aluminum", color);
	
/*Test GET functions*/	 
	 
    //check ID
	//if ID does not match, errors will be counted.
	std::cout<<"ID"<<std::endl;
	if(m1.getID()!=1){
			errors++;
	}
	std::cout<<"errors count:"<<errors<<std::endl;

	//Density
	std::cout<<"Density"<<std::endl;
	if(m1.getDensity()!=2700.0){
			errors++;
	}
	std::cout<<"errors count:"<<errors<<std::endl;
	
	//Name
	std::cout<<"Name"<<std::endl;
	if(m1.getName()!="aluminum"){
			errors++;
	}
	std::cout<<"errors count:"<<errors<<std::endl;


	//Color
	std::cout<<"Color"<<std::endl;

	if(m1.getColor().getx()!=188||m1.getColor().gety()!=188||m1.getColor().getz()!=188){
			errors++;
	}
	std::cout<<"errors count:"<<errors<<std::endl;	



/*Test SET functions*/

	m1.setID(0);
	m1.setName("copper");
	m1.setColor(184,73,73);
	m1.setDensity(8960.0);
	
	std::cout<<"ID"<<std::endl;
	if(m1.getID()!=0){
			errors++;
	}
	std::cout<<"errors count:"<<errors<<std::endl;

	//Density
	std::cout<<"Density"<<std::endl;
	if(m1.getDensity()!=8960.0){
			errors++;
	}
	std::cout<<"errors count:"<<errors<<std::endl;
	
	//Name
	std::cout<<"Name"<<std::endl;
	if(m1.getName()!="copper"){
			errors++;
	}
	std::cout<<"errors count:"<<errors<<std::endl;


	//Color
	std::cout<<"Color"<<std::endl;
	if(m1.getColor().getx()!=184||m1.getColor().gety()!=73||m1.getColor().getz()!=73){
			errors++;
	}	
	std::cout<<"errors count:"<<errors<<std::endl;
	

	return (errors==0)? 0:1;
   
}











