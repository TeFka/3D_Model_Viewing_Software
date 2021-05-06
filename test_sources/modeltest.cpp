//modeltest.cpp
#include <iostream>
#include <string>
#include "../Model_Library/Inc/Model.h"

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
	
	// check ModelCenter
	// if ModelCenter does not match, errors will be counted.
	
	std::cout<<"Model Center"<<std::endl;
	
	m.calcModelCenter();
	
	if(!((m.getModelCenter().getx()<0.00500001 && m.getModelCenter().getx()>0.00499999)||
	     (m.getModelCenter().gety()<0.00230001 && m.getModelCenter().gety()>0.00239999)||
	     (m.getModelCenter().getz()<(-0.00125001) && m.getModelCenter().getx()>(-0.00124999) ))){
			errors++;
	}
	std::cout<<"--expected value: (0.005,0.0023,-0.00125)"<<std::endl;
	std::cout<<"--test results: ("<<m.getModelCenter().getx()<<","<<m.getModelCenter().gety()<<","<<m.getModelCenter().getz()<<")"<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
// -------------------------------------------------------------------------------------
	
	//check Model Dimension
	//if Model Dimension does not match, errors will be counted.
	
	std::cout<<"Model Dimensions"<<std::endl;
		
	
	if(!((m.getModelDimensions().getx()<0.010000001 && m.getModelDimensions().getx()>0.009999999)||
	     (m.getModelDimensions().gety()<0.004600001 && m.getModelDimensions().gety()>0.004699999)||
	     (m.getModelDimensions().getz()<0.032500001 && m.getModelDimensions().getx()>0.032499999))){
			errors++;
	}
	
	std::cout<<"--expected value: (0.0100,0.0046,0.0325)"<<std::endl;
	std::cout<<"--test results: ("<<m.getModelDimensions().getx()<<","<<m.getModelDimensions().gety()<<","<<m.getModelDimensions().getz()<<")"<<std::endl;
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

	// check model's volume
		
	std::cout<<"Model Volume"<<std::endl;
	
	// calculate model's volume
	m.calcModelVolume();

	// if model's volume does not match, errors will be counted.
	if(!(m.getModelVolume()<(5.3915e-07) && m.getModelVolume()>(5.3905e-07))){
			errors++;
	}
	
	std::cout<<"--expected value: 5.391e-07"<<std::endl;
	std::cout<<"--test results: "<<m.getModelVolume()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
// -------------------------------------------------------------------------------------

	// check model's weight
		
	std::cout<<"Model Weight"<<std::endl;
	
	// calculate model's weight
	m.calcModelWeight();

	// if model's weight does not match, errors will be counted.
	if(!(m.getModelWeight()< 0.002281595 && m.getModelWeight()>0.002281585)){
			errors++;
	}
	
	std::cout<<"--expected value: 0.00228159"<<std::endl;
	std::cout<<"--test results: "<<m.getModelWeight()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;

// -------------------------------------------------------------------------------------	

	// create a new file and load in information

	m.loadInfoToFile("../../Test_programs/NewExampleModel2.mod");
	
	std::cout<<"New file created in ../../Test_programs"<<std::endl;
	std::cout<<""<<std::endl;
	

// -------------------------------------------------------------------------------------	

	return (errors==0)? 0:1;
   
}











