#ifndef MODELCLASS_H_INCLUDED
#define MODELCLASS_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include<math.h>
#include "../Inc/Vector3D.h"
#include "../Inc/Material.h"
#include "../Inc/Cell.h"

struct cellInfo{
    int ID;
    int materialID;
    int type;
    std::vector<int> indixes;
};

//side functions
float getHexValue(char);

class Model{

private:
std::vector<Vector3D> vertices;
std::vector<Material*> materials;
std::vector<Cell*> cells;

Vector3D modelCenter;

int getVectorIndex(int);
Material getMaterial(int);

void allignVertices();
void allignCells();
void allignMaterials();
void loadModel(char*);

void calcModelCenter();
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
