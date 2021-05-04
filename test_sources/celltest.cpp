//celltest.cpp
#include <iostream>
#include <string>
#include "../Inc/Cell.h"

using namespace std;

int main(int argc, char *argv[])
{
	// Cell class test
	std::cout<<"Cell Class Test"<<std::endl;
	int errors = 0;
	
	
	Vector3D color(188, 188, 188);
	
	//Material :: Material( int id, double d, string name, Vector3D col )
	Material m1(1, 200.0, "aluminum", color);
	Material m2(2, 1200.0, "silver", color);
	Material m3(3, 600.0, "copper", color);
	
	
	
//----------HEXAHEDRON TEST--------------------------------------------------//	

	std::cout<<""<<std::endl;
	std::cout<<"........HEXAHEDRON........"<<std::endl;
	
	// hex_vectors: indicate the coordinates of each vertex
	std::vector<Vector3D> hex_vector;
	hex_vector.push_back(Vector3D(0.0, 0.0, 0.0)); //vertex0
	hex_vector.push_back(Vector3D(2.0, 0.0, 0.0)); //vertex1
	hex_vector.push_back(Vector3D(2.0, 2.0, 0.0)); //vertex2
	hex_vector.push_back(Vector3D(0.0, 2.0, 0.0)); //vertex3
	hex_vector.push_back(Vector3D(0.0, 0.0, 2.0)); //vertex4
	hex_vector.push_back(Vector3D(2.0, 0.0, 2.0)); //vertex5
	hex_vector.push_back(Vector3D(2.0, 2.0, 2.0)); //vertex6
	hex_vector.push_back(Vector3D(0.0, 2.0, 2.0)); //vertex7
	
	// hex_indices: indicate the vertex number of each indices
	// hexahedron have 8 vertices
	std::vector<int> hex_indices = {0,1,2,3,4,5,6,7}; //leave our 6th indice to use function insertIndice
	
	
	
	// hex_materials: indicate the materials of the celltest
	std::vector<Material> hex_materials = {m1};
	
	
	// HEXAHEDRON CELL
		//Hexahedron hex;
	Hexahedron hex(1, 1, 0, hex_indices, hex_vector, hex_materials);
	
	
/*Test SET functions*/

	// Set hexahedron cell properties
	//hex.setID(1);
	//hex.setType(1);
	//hex.setMaterialID(1);
	//hex.setIndices(hex_indices);



/*Test GET functions*/	 
	 
	 
    //check ID
	//if ID does not match, errors will be counted.
	std::cout<<"ID"<<std::endl;
	if(hex.getID()!=1){
			errors++;
	}
	std::cout<<"--expected value: 1"<<std::endl;
	std::cout<<"--test results: "<<hex.getID()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	
	//check type
	//if type does not match, errors will be counted.
	std::cout<<"Type"<<std::endl;
	if(hex.getType()!=1){
			errors++;
	}
	std::cout<<"--expected value: 1"<<std::endl;
	std::cout<<"--test results: "<<hex.getType()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	
	//check materialID
	//if materialID does not match, errors will be counted.
	std::cout<<"MaterialID"<<std::endl;
	if(hex.getMaterialID()!=0){
			errors++;
	}
	std::cout<<"--expected value: 0"<<std::endl;
	std::cout<<"--test results: "<<hex.getMaterialID()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	
	//check Indices
	//if Indiced does not match, errors will be counted.
	std::cout<<"Indices"<<std::endl;
	
	for(int i =0; i<hex_indices.size(); i++){
		if(hex.getIndices()[i]!=hex_indices[i]){
			errors++;
		}
	}
	std::cout<<"--expected value: 01234567"<<std::endl;
	std::cout<<"--test results: ";
	for(int i =0; i<hex_indices.size(); i++){std::cout<<hex.getIndices()[i];}
	std::cout<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	
	
	//check Volume
	//if Volume does not match, errors will be counted.
	std::cout<<"Volume"<<std::endl;
	
	hex.calculateVolume(hex_vector);
	
	if(!(hex.getVolume() < 8.000001 && hex.getVolume() > 7.999999))
	{
			errors++;
	}
	std::cout<<"--expected value: 8"<<std::endl;
	std::cout<<"--test results: "<<hex.getVolume()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	

	//check Centre of Gravity
	//if centre of gravity does not match, errors will be counted.
	std::cout<<"Centre of Gravity"<<std::endl;
	
	hex.calcCentreOfGravity(hex_vector);
	
	if(hex.getCentreOfGravity().getx()!=1.0||
	   hex.getCentreOfGravity().gety()!=1.0||
	   hex.getCentreOfGravity().getz()!=1.0){
			errors++;
	}
	std::cout<<"--expected value: (1.0,1.0,1.0)"<<std::endl;
	std::cout<<"--test results: ("<<hex.getCentreOfGravity().getx()<<","<<hex.getCentreOfGravity().gety()<<","<<hex.getCentreOfGravity().getz()<<")"<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	
	
	//check Weight
	//if weight does not match, errors will be counted.
	std::cout<<"Weight"<<std::endl;
	
	hex.calcWeight(hex_materials);
	
	if(!(hex.getWeight() < 1600.000001 && hex.getWeight() > 1599.999999)){
			errors++;
	}
	std::cout<<"--expected value: 1600"<<std::endl;
	std::cout<<"--test results: "<<hex.getWeight()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;	
	
	
	
	
//----------PYRAMID TEST--------------------------------------------------//	

	std::cout<<".........PYRAMID........."<<std::endl;
	
	// pyr_vectors: indicate the coordinates of each vertex
	std::vector<Vector3D> pyr_vector;
	pyr_vector.push_back(Vector3D(-1.0, -1.0, 1.0)); //vertex0
	pyr_vector.push_back(Vector3D(0.0, 0.0, 0.0)); //vertex1
	pyr_vector.push_back(Vector3D(1.0, -1.0, 1.0)); //vertex2
	pyr_vector.push_back(Vector3D(-1.0, 1.0, 1.0)); //vertex3
	pyr_vector.push_back(Vector3D(1.0, 1.0, 1.0)); //vertex4
	
	
	// pyr_indices: indicate the vertex number of each indices
	// pyramid have 5 vertices
	std::vector<int> pyr_indices = {0,1,2,3,4}; //leave out last indice to use function pushIndice
	
	
	// pyr_materials: indicate the materials of the celltest
	std::vector<Material> pyr_materials = {m1,m2};
	
	
	// PYRAMID CELL
	Pyramid pyr;

/*Test SET functions*/

	// Set pyramid cell properties
	pyr.setID(2);
	pyr.setType(2);
	pyr.setMaterialID(1);
	pyr.setIndices(pyr_indices);
	


/*Test GET functions*/	 
	 
	 
    //check ID
	//if ID does not match, errors will be counted.
	std::cout<<"ID"<<std::endl;
	if(pyr.getID()!=2){
			errors++;
	}
	std::cout<<"--expected value: 2"<<std::endl;
	std::cout<<"--test results: "<<pyr.getID()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	
	//check type
	//if type does not match, errors will be counted.
	std::cout<<"Type"<<std::endl;
	if(pyr.getType()!=2){
			errors++;
	}
	std::cout<<"--expected value: 2"<<std::endl;
	std::cout<<"--test results: "<<pyr.getType()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	
	//check materialID
	//if materialID does not match, errors will be counted.
	std::cout<<"MaterialID"<<std::endl;
	if(pyr.getMaterialID()!=1){
			errors++;
	}
	std::cout<<"--expected value: 1"<<std::endl;
	std::cout<<"--test results: "<<pyr.getMaterialID()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	
	//check Indices
	//if Indiced does not match, errors will be counted.
	std::cout<<"Indices"<<std::endl;
	
	for(int i = 0; i<pyr_indices.size(); i++){
		if(pyr.getIndices()[i]!=pyr_indices[i]){
			errors++;
		}
	}
	std::cout<<"--expected value: 01234"<<std::endl;
	std::cout<<"--test results: ";
	for(int i =0; i<pyr_indices.size(); i++){std::cout<<pyr.getIndices()[i];}
	std::cout<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	
	
	//check Volume
	//if Volume does not match, errors will be counted.
	std::cout<<"Volume"<<std::endl;
	
	pyr.calculateVolume(pyr_vector);
	
	if(!(pyr.getVolume() < 1.33334 && pyr.getVolume() > 1.33332)){
			errors++;
	}
	std::cout<<"--expected value: 1.33333"<<std::endl;
	std::cout<<"--test results: "<<pyr.getVolume()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	

	//check Centre of Gravity
	//if centre of gravity does not match, errors will be counted.
	std::cout<<"Centre of Gravity"<<std::endl;
	
	pyr.calcCentreOfGravity(pyr_vector);
	
	if(pyr.getCentreOfGravity().getx()!=0.0||
	   pyr.getCentreOfGravity().gety()!=0.0||
	   pyr.getCentreOfGravity().getz()!=0.8){
			errors++;
	}
	std::cout<<"--expected value: (0.0,0.0,0.8)"<<std::endl;
	std::cout<<"--test results: ("<<pyr.getCentreOfGravity().getx()<<","<<pyr.getCentreOfGravity().gety()<<","<<pyr.getCentreOfGravity().getz()<<")"<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	
	
	//check Weight
	//if weight does not match, errors will be counted.
	std::cout<<"Weight"<<std::endl;
	
	pyr.calcWeight(pyr_materials);
	
	if(pyr.getWeight()!=1600){
			errors++;
	}
	std::cout<<"--expected value: 1600"<<std::endl;
	std::cout<<"--test results: "<<pyr.getWeight()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	
	
//----------TETRAHEDRON TEST--------------------------------------------------//	

	std::cout<<".......TETRAHEDRON......."<<std::endl;
	
	// tetra_vector: indicate the coordinates of each vertex
	std::vector<Vector3D> tetra_vector;
	tetra_vector.push_back(Vector3D(0.0, 0.0, 0.0)); //vertex0
	tetra_vector.push_back(Vector3D(1.0, 0.0, 0.0)); //vertex1
	tetra_vector.push_back(Vector3D(1.0, 1.0, 0.0)); //vertex2
	tetra_vector.push_back(Vector3D(0.0, 1.0, 1.0)); //vertex3
	
	
	// tetra_indices: indicate the vertex number of each indices
	// tetrahedron have 4 vertices
	std::vector<int> tetra_indices = {0,1,2,3}; 
	
	
	// tetra_materials: indicate the materials of the celltest
	std::vector<Material> tetra_materials = {m1,m2,m3};
	
	
	// PYRAMID CELL
	Tetrahedron tetra;
		

/*Test SET functions*/

	// Set pyramid cell properties
	tetra.setID(3);
	tetra.setType(3);
	tetra.setMaterialID(2);
	//tetra.setIndices(tetra_indices);
	tetra.pushIndice(0);
	tetra.pushIndice(9);
	tetra.insertIndice(1,1);
	tetra.insertIndice(2,2);
	tetra.setIndice(3,3);

/*Test GET functions*/	 
	 
	 
    //check ID
	//if ID does not match, errors will be counted.
	std::cout<<"ID"<<std::endl;
	if(tetra.getID()!=3){
			errors++;
	}
	std::cout<<"--expected value: 3"<<std::endl;
	std::cout<<"--test results: "<<tetra.getID()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	
	//check type
	//if type does not match, errors will be counted.
	std::cout<<"Type"<<std::endl;
	if(tetra.getType()!=3){
			errors++;
	}
	std::cout<<"--expected value: 3"<<std::endl;
	std::cout<<"--test results: "<<tetra.getType()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	
	//check materialID
	//if materialID does not match, errors will be counted.
	std::cout<<"MaterialID"<<std::endl;
	if(tetra.getMaterialID()!=2){
			errors++;
	}
	std::cout<<"--expected value: 2"<<std::endl;
	std::cout<<"--test results: "<<tetra.getMaterialID()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	
	//check Indices
	//if Indiced does not match, errors will be counted.
	std::cout<<"Indices"<<std::endl;
	
	for(int i =0; i<tetra_indices.size(); i++){
		if(tetra.getIndices()[i]!=tetra_indices[i]){
			errors++;
		}
	}
	
	std::cout<<"--expected value: 0123"<<std::endl;
	std::cout<<"--test results: ";
	for(int i =0; i<tetra_indices.size(); i++){std::cout<<tetra.getIndices()[i];}
	std::cout<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	
	//check Volume
	//if Volume does not match, errors will be counted.
	std::cout<<"Volume"<<std::endl;
	
	tetra.calculateVolume(tetra_vector);
	
	if(!(tetra.getVolume() < 0.166668 && tetra.getVolume() > 0.166665)){
			errors++;
	}
	std::cout<<"--expected value: 0.166667"<<std::endl;
	std::cout<<"--test results: "<<tetra.getVolume()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	

	//check Centre of Gravity
	//if centre of gravity does not match, errors will be counted.
	std::cout<<"Centre of Gravity"<<std::endl;
	
	tetra.calcCentreOfGravity(tetra_vector);
	
	if(tetra.getCentreOfGravity().getx()!=0.5||
	   tetra.getCentreOfGravity().gety()!=0.5||
	   tetra.getCentreOfGravity().getz()!=0.25){
			errors++;
	}
	std::cout<<"--expected value: (0.5,0.5,0.25)"<<std::endl;
	std::cout<<"--test results: ("<<tetra.getCentreOfGravity().getx()<<","<<tetra.getCentreOfGravity().gety()<<","<<tetra.getCentreOfGravity().getz()<<")"<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	
	
	
	//check Weight
	//if weight does not match, errors will be counted.
	std::cout<<"Weight"<<std::endl;
	
	tetra.calcWeight(tetra_materials);
	
	if(tetra.getWeight()!=100){
			errors++;
	}
	std::cout<<"--expected value: 100"<<std::endl;
	std::cout<<"--test results: "<<tetra.getWeight()<<std::endl;
	std::cout<<"--errors count: "<<errors<<std::endl;
	std::cout<<""<<std::endl;
	

	return (errors==0)? 0:1;
   
}













