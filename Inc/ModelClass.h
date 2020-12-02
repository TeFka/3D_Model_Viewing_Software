#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include<math.h>
#ifndef MODELCLASS_H_INCLUDED
#define MODELCLASS_H_INCLUDED

struct vertice{
    int ID;
    float x;
    float y;
    float z;
};

struct cell{
    int ID;
    int type;
    int materialID;
    std::vector<int> indices;
    float volume;
    float weight;
    vertice gravityCenter;

};

struct material{
    int ID;
    std::string name;
    float color[3];
    float density;
};

//side functions
float getHexValue(char);

class Model{

private:
std::vector<vertice> vertices;
std::vector<material*> materials;
std::vector<cell*> cells;

vertice modelGravityCenter;

void allignVertices();
void allignCells();
void allignMaterials();
void loadModel(char*);

vertice calcModelCenter();
public:
Model(char*);
int getVerticesAmount();
int getCellAmount();
void showMaterials();
void showVertices();
void showCells();
void loadInfoToFile(char*);
};

#endif // MODELCLASS_H_INCLUDED
