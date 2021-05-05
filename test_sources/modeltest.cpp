//modeltest.cpp
#include <iostream>
#include <string>
#include "../Inc/Model.h"

using namespace std;

int main(int argc, char *argv[])
{
	// Model class test
	std::cout<<"Model Class Test"<<std::endl;
	std::cout<<""<<std::endl;
	int errors = 0;
	
// -------------------------------------------------------------------------------------
	
	Model m;
	m.loadModel("../../Resources/ExampleModel2.mod");
	
	std::cout<<"File name: ExampleModel2"<<std::endl;
	std::cout<<""<<std::endl;
	
// -------------------------------------------------------------------------------------
	
	//check ModelCenter
	//if ModelCenter does not match, errors will be counted.
	
	std::cout<<"Model Center"<<std::endl;
	
	m.calcModelCenter();
	
	if(!(m.getModelCenter().getx()<0.00500001 && m.getModelCenter().getx()>0.00499999||
	     m.getModelCenter().gety()<0.00230001 && m.getModelCenter().gety()>0.00239999|
	     m.getModelCenter().getz()<(-0.00125001) && m.getModelCenter().getx()>(-0.00124999))){
			errors++;
	}
	std::cout<<"--expected value: (0.005,0.0023,-0.00125)"<<std::endl;
	std::cout<<"--test results: ("<<m.getModelCenter().getx()<<","<<m.getModelCenter().gety()<<","<<m.getModelCenter().getz()<<")"<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
// -------------------------------------------------------------------------------------

	// check Vector Amount
	// if Vector Amount does not match, errors will be counted.
	
	std::cout<<"Vector Amount"<<std::endl;
		
	if(m.getVectorAmount()!= 301){
			errors++;
	}
	
	std::cout<<"--expected value: 301"<<std::endl;
	std::cout<<"--test results: "<<m.getVectorAmount()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
// -------------------------------------------------------------------------------------

	// check Cell Amount
	// if Cell Amount does not match, errors will be counted.
	
	std::cout<<"Cell Amount"<<std::endl;
		
	if(m.getCellAmount()!= 129){
			errors++;
	}
	
	std::cout<<"--expected value: 129"<<std::endl;
	std::cout<<"--test results: "<<m.getCellAmount()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
// -------------------------------------------------------------------------------------

	// check Material Amount
	// if Material Amount does not match, errors will be counted.
	
	std::cout<<"Material Amount"<<std::endl;
		
	if(m.getMaterialAmount()!= 2){
			errors++;
	}
	
	std::cout<<"--expected value: 2"<<std::endl;
	std::cout<<"--test results: "<<m.getMaterialAmount()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;

// -------------------------------------------------------------------------------------	


	m.loadInfoToFile("../../Test_programs/NewExampleModel2.mod");
	
	std::cout<<"New file created in ../../Test_programs"<<std::endl;
	std::cout<<""<<std::endl;

// -------------------------------------------------------------------------------------	

	return (errors==0)? 0:1;
   
}











