//-------------------------------------------------------------
// File to store all implementations of functions of Model class.
//-------------------------------------------------------------

//Copyright Danielius Zurlys (StudentID: 20130611)

// Required header files: iostream(for printing with cout), Model.h(to get function interfaces)

//-------------------------------------------------------------
//-------------------------------------------------------------

#include "../Inc/Model.h"

//Function hexToFloat()
//Function to convert hex color value to float value
// Arguments for getHexValue(): char - hex letter to convert
// return value: a converted float value of color
//note:
// 1) Input hex value has to be in range [0;F]
float hexToFloat(char letter)
{
    switch(letter)
    {
    case 'a':
        return 10;
        break;
    case 'b':
        return 11;
        break;
    case 'c':
        return 12;
        break;
    case 'd':
        return 13;
        break;
    case 'e':
        return 14;
        break;
    case 'f':
        return 15;
        break;
    case 'A':
        return 10;
        break;
    case 'B':
        return 11;
        break;
    case 'C':
        return 12;
        break;
    case 'D':
        return 13;
        break;
    case 'E':
        return 14;
        break;
    case 'F':
        return 15;
        break;
    default:
        return (atoi(&letter));
    }
}


//Function floatToHex()
//Function to convert float color value to hex value
// Arguments for floatToHex(): float - float value to convert
// return value: a converted std::string letter of color
//notes:
// 1) Input float value has to be in range [0;1.0]
std::string floatToHex(float val)
{
    val = val*255;
    int N1 = val/16;
    int N2 = (int)val%16;
    std::string hex;
    switch(N1)
    {
    case 0:
        hex.push_back('0');
        break;
    case 1:
        hex.push_back('1');
        break;
    case 2:
        hex.push_back('2');
        break;
    case 3:
        hex.push_back('3');
        break;
    case 4:
        hex.push_back('4');
        break;
    case 5:
        hex.push_back('5');
        break;
    case 6:
        hex.push_back('6');
        break;
    case 7:
        hex.push_back('7');
        break;
    case 8:
        hex.push_back('8');
        break;
    case 9:
        hex.push_back('9');
        break;
    case 10:
        hex.push_back('A');
        break;
    case 11:
        hex.push_back('B');
        break;
    case 12:
        hex.push_back('C');
        break;
    case 13:
        hex.push_back('D');
        break;
    case 14:
        hex.push_back('E');
        break;
    case 15:
        hex.push_back('F');
        break;
    }

    switch(N2)
    {
    case 0:
        hex.push_back('0');
        break;
    case 1:
        hex.push_back('1');
        break;
    case 2:
        hex.push_back('2');
        break;
    case 3:
        hex.push_back('3');
        break;
    case 4:
        hex.push_back('4');
        break;
    case 5:
        hex.push_back('5');
        break;
    case 6:
        hex.push_back('6');
        break;
    case 7:
        hex.push_back('7');
        break;
    case 8:
        hex.push_back('8');
        break;
    case 9:
        hex.push_back('9');
        break;
    case 10:
        hex.push_back('A');
        break;
    case 11:
        hex.push_back('B');
        break;
    case 12:
        hex.push_back('C');
        break;
    case 13:
        hex.push_back('D');
        break;
    case 14:
        hex.push_back('E');
        break;
    case 15:
        hex.push_back('F');
        break;
    }
    return hex;
}

//Constructor of Model class
//Action:
//      Load a 3D model from specified file.
//Arguments: char - path to a model file.
Model::Model(char* path)
{
    loadModel(path);
    std::cout<<"Model Loaded"<<std::endl;
}

//Destructor for Model class
// Action:
//      Clears vertices, materials and cells arrays.
Model::~Model()
{
    this->vertices.clear();
    this->materials.clear();
    this->cells.clear();
}

//Copy constructor of Model class
//Action:
    //copies vertices, materials, cells arrays and the model center information to a new Model object.
Model::Model(const Model& copied_Model)
{
    vertices = copied_Model.vertices;
    materials = copied_Model.materials;
    cells = copied_Model.cells;
    modelCenter = copied_Model.modelCenter;
}

//Function of class Model, getVectorIndex()
//Function to get index in vertices array of vector with specified ID.
// Arguments for getVectorIndex(): int - ID to be searched for.
// return value: int - index of vector with specified ID.
//Notes:
// 1) The function will return -1 if the ID is not found, which will most likely give error in the application.
int Model::getVectorIndex(int ID)
{
    for(int i = 0; i<this->vertices.size(); i++)
    {
        if(this->vertices[i].getID()==ID)
        {
            return i;
        }
    }
    std::cout<<"Vector with ID: "<<ID<<" not found"<<std::endl;
    return -1;
}

//Function of class Model, getMaterial()
//Function to get material with specified ID.
// Arguments for getMaterial(): int - ID to be searched for.
// return value: Material - material with specified ID.
//Notes:
// 1) The function will return empty Material object if the ID is not found, which will most likely not work or cause errors.
Material Model::getMaterial(int ID)
{
    if(ID<this->materials.size())
    {
        return *this->materials[ID];
    }
    else
    {
        for(int i = this->materials.size(); i--;)
        {
            if(this->materials[i]->getID()==ID)
            {
                return *this->materials[ID];
            }
        }
    }
    std::cout<<"Material with ID: "<<ID<<" not found"<<std::endl;
    return Material{};
}

//Function of class Model, allignVertices()
//Function to sort the vertices array.
// Arguments for allignVertices(): none.
// return value: none(vertices array sorted)
void Model::allignVertices()
{
    for(int i =0; i<this->vertices.size()-1; i++)
    {
        for(int n = 0; n<this->vertices.size()-i-1; n++)
        {
            if(this->vertices[n].getID()>this->vertices[n+1].getID())
            {
                std::swap(this->vertices[n],this->vertices[n+1]);
            }
        }
    }
}

//Function of class Model, allignCells()
//Function to sort the cells array.
// Arguments for allignCells(): none.
// return value: none(cells array sorted)
void Model::allignCells()
{
    for(int i =0; i<this->cells.size()-1; i++)
    {
        for(int n = 0; n<this->cells.size()-i-1; n++)
        {
            if(this->cells[n]->getID()>this->cells[n+1]->getID())
            {
                std::swap(this->cells[n],this->cells[n+1]);
            }
        }
    }
}

//Function of class Model, allignMaterials()
//Function to sort the materials array.
// Arguments for allignMaterials(): none.
// return value: none(materials array sorted)
void Model::allignMaterials()
{
    for(int i =0; i<this->materials.size()-1; i++)
    {
        for(int n = 0; n<this->materials.size()-i-1; n++)
        {
            if(this->materials[n]->getID()>this->materials[n+1]->getID())
            {
                std::swap(this->materials[n],this->materials[n+1]);
            }
        }
    }
}

//Function of class Model, calcModelCenter()
//Function to calculate position of model center
// Arguments for calcModelCenter(): none.
// return value: none(model center value updated)
//Note:
//Model center position will become {0,0,0} if vertices array is empty.
void Model::calcModelCenter()
{
    double x=0,y=0,z=0;
    for(int i = 0; i<this->vertices.size(); i++)
    {
        x+=this->vertices[i].getx();
        y+=this->vertices[i].gety();
        z+=this->vertices[i].getz();
    }
    this->modelCenter = Vector3D(x,y,z);
}

//Function of class Model, loadModel()
//Function to retrieve 3D model information from a VTK file
// Arguments for loadModel(): char - path to
// return value: none(model center value updated)
//Note:
// 1) The way function reads each file line and retrieves infromation:
//      Material: m material_ID material_density material_color(#000000 form hex code) material_name
//      Vector: v vector_ID x_position y_position z_position
//      Cell: c cell_ID cell_type(h - hexahedral, p - pyramid, t - tetrahedral) [cell_indices]
// 2) In case of file being written incorrectly, incorrect values might be written, errors may occur or program can crash.
void Model::loadModel(char* path)
{
    //temporary file data storagessds
    std::vector<cellInfo*> tempCellInfo;

    //get data
    std::fstream file;
    std::string line;
    file.open(path);
    int valueNum = 1;
    int valueIterator = 0;
    int firstChar = 0;
    Vector3D tempCol;
    while(getline(file,line))
    {
        valueNum=1;
        switch(line[0])
        {
        case 'm':
        {
            Material* tempMat = new Material();
            firstChar = 1;
            for(int i =2; i<(int)line.length(); i++)
            {
                if(line[i]!=' ')
                {
                    switch(valueNum)
                    {
                    case 1:

                        if(firstChar)
                        {
                            tempMat->setID(atoi( &line[i] ));
                            firstChar=0;
                        }
                        break;
                    case 2:
                        if(firstChar)
                        {
                            firstChar=0;
                            tempMat->setDensity(atoi( &line[i] ));
                        }
                        break;
                    case 3:
                    {
                        switch(valueIterator)
                        {
                        case 0:
                            tempCol.setx(hexToFloat(line[i])*16/255);
                            tempCol.sety(0);
                            tempCol.setz(0);
                            break;
                        case 1:
                            tempCol.setx(tempCol.getx()+hexToFloat(line[i])/255);
                            break;
                        case 2:
                            tempCol.sety(hexToFloat(line[i])*16/255);
                            break;
                        case 3:
                            tempCol.sety(tempCol.gety()+hexToFloat(line[i])/255);
                            break;
                        case 4:
                            tempCol.setz(hexToFloat(line[i])*16/255);
                            break;
                        case 5:
                            tempCol.setz(tempCol.getz()+hexToFloat(line[i])/255);
                            tempMat->setColor(tempCol);
                            break;
                        }
                        valueIterator++;
                        break;
                    }
                    case 4:
                        if(firstChar)
                        {
                            tempMat->setName(&line[i]);
                            firstChar = 0;
                        }
                        break;
                    }
                }
                else
                {
                    firstChar=1;
                    valueNum++;
                    valueIterator = 0;
                }
            }
            this->materials.push_back(tempMat);
            break;
        }
        case 'v':
        {
            Vector3D tempVert;
            int charVal;
            int afterDot = 0;
            int negative = 0;
            valueIterator = 0;
            firstChar = 1;
            for(int i =2; i<(int)line.length(); i++)
            {
                if(line[i]!=' ')
                {
                    if(line[i]=='.')
                    {
                        afterDot = 1;
                    }
                    else if(line[i]=='-')
                    {
                        negative = 1;
                    }
                    else
                    {
                        switch(valueNum)
                        {
                        case 1:
                            if(firstChar)
                            {
                                tempVert.setID(atoi( &line[i] ));
                                firstChar=0;
                            }
                            break;
                        case 2:
                            charVal = line[i] - '0';
                            if(firstChar)
                            {
                                firstChar=0;
                                tempVert.setx(charVal);
                            }
                            else
                            {
                                if(afterDot)
                                {
                                    tempVert.setx(tempVert.getx()+((float)pow(10,(-valueIterator))*charVal));
                                }
                                else
                                {
                                    tempVert.setx(tempVert.getx()*10+charVal);
                                }
                            }
                            break;
                        case 3:
                            charVal = line[i] - '0';
                            if(firstChar)
                            {
                                firstChar=0;
                                tempVert.sety(charVal);
                            }
                            else
                            {
                                if(afterDot)
                                {
                                    tempVert.sety(tempVert.gety()+(float)pow(10,(-valueIterator))*charVal);
                                }
                                else
                                {
                                    tempVert.sety(tempVert.gety()*10+charVal);
                                }
                            }
                            break;
                        case 4:
                            charVal = line[i] - '0';
                            if(firstChar)
                            {
                                firstChar=0;
                                tempVert.setz(charVal);
                            }
                            else
                            {
                                if(afterDot)
                                {
                                    tempVert.setz(tempVert.getz()+(float)pow(10,(-valueIterator))*charVal);
                                }
                                else
                                {
                                    tempVert.setz(tempVert.getz()*10+charVal);
                                }
                            }
                            break;
                        }
                        valueIterator++;
                    }
                }
                else
                {
                    if(negative)
                    {
                        switch(valueNum)
                        {
                        case 1:
                            tempVert.setID(-tempVert.getID());
                            break;
                        case 2:
                            tempVert.setx(-tempVert.getx());
                            break;
                        case 3:
                            tempVert.sety(-tempVert.gety());
                            break;
                        case 4:
                            tempVert.setz(-tempVert.getz());
                            break;
                        }
                    }
                    negative = 0;
                    afterDot = 0;
                    firstChar=1;
                    valueNum++;
                    valueIterator = 0;
                }
                if(i==line.length()-1)
                {
                    if(negative)
                    {
                        switch(valueNum)
                        {
                        case 1:
                            tempVert.setID(-tempVert.getID());
                            break;
                        case 2:
                            tempVert.setx(-tempVert.getx());
                            break;
                        case 3:
                            tempVert.sety(-tempVert.gety());
                            break;
                        case 4:
                            tempVert.setz(-tempVert.getz());
                            break;
                        }
                    }
                }
            }
            this->vertices.push_back(tempVert);
            break;
        }
        case 'c':
        {
            cellInfo* tempCell = new cellInfo();
            firstChar = 1;
            for(int i = 2; i<(int)line.length(); i++)
            {
                if(line[i]!=' ')
                {
                    if(valueNum==1)
                    {
                        if(firstChar)
                        {
                            tempCell->ID = atoi( &line[i] );
                            firstChar=0;
                        }
                    }
                    else if(valueNum==2)
                    {
                        switch(line[i])
                        {
                        case 'h':
                            tempCell->type = 1;
                            break;
                        case 'p':
                            tempCell->type = 2;
                            break;
                        case 't':
                            tempCell->type = 3;
                            break;
                        }
                    }
                    else if(valueNum==3)
                    {
                        if(firstChar)
                        {
                            tempCell->materialID = atoi( &line[i] );
                            firstChar=0;
                        }
                    }
                    else
                    {
                        if(firstChar)
                        {
                            tempCell->indixes.push_back(atoi( &line[i] ));
                            firstChar=0;
                        }
                    }
                }
                else
                {
                    valueNum++;
                    firstChar = 1;
                }
            }

            tempCellInfo.push_back(tempCell);
            break;
        }
        }
    }
    file.close();
    //assign and use data
    this->allignVertices();
    this->allignMaterials();
    for(int tC = 0; tC<tempCellInfo.size(); tC++)
    {
        if(tempCellInfo[tC]->type==1)
        {

            Hexahedron* tempCell = new Hexahedron();
            tempCell->setID(tempCellInfo[tC]->ID);
            tempCell->setType(1);
            for(int n = 0; n<tempCellInfo[tC]->indixes.size(); n++)
            {
                //std::cout<<tempCellInfo[tC]->indixes[0]<<std::endl;
                tempCell->pushIndice(this->getVectorIndex(tempCellInfo[tC]->indixes[n]));
            }
            tempCell->setMaterialID(tempCellInfo[tC]->materialID);
            this->cells.push_back(tempCell);
        }
        else if(tempCellInfo[tC]->type==1)
        {
            Pyramid* tempCell = new Pyramid();
            tempCell->setID(tempCellInfo[tC]->ID);
            tempCell->setType(2);
            for(int n = 0; n<tempCellInfo[tC]->indixes.size(); n++)
            {
                //std::cout<<tempCellInfo[tC]->indixes[0]<<std::endl;
                tempCell->pushIndice(this->getVectorIndex(tempCellInfo[tC]->indixes[n]));
            }
            tempCell->setMaterialID(tempCellInfo[tC]->materialID);
            this->cells.push_back(tempCell);
        }
        else if(tempCellInfo[tC]->type==1)
        {
            Tetrahedron* tempCell = new Tetrahedron();
            tempCell->setID(tempCellInfo[tC]->ID);
            tempCell->setType(3);
            for(int n = 0; n<tempCellInfo[tC]->indixes.size(); n++)
            {
                //std::cout<<tempCellInfo[tC]->indixes[0]<<std::endl;
                tempCell->pushIndice(this->getVectorIndex(tempCellInfo[tC]->indixes[n]));
            }
            tempCell->setMaterialID(tempCellInfo[tC]->materialID);
            this->cells.push_back(tempCell);
        }
    }
    this->allignCells();
}

//Function of class Model, showMaterials()
//Function to show information about all materials
// Arguments for showMaterials(): none.
// return value: none(information printed)
void Model::showMaterials()
{
    std::cout<<"Materials:"<<std::endl;
    if(this->materials.size()>0){
    for(int i = 0; i<(int)this->materials.size(); i++)
    {
        std::cout<<this->materials[i]->getID()<<":  ";
        std::cout<<this->materials[i]->getDensity()<<" ";
        std::cout<<this->materials[i]->getColor().getx()<<"|"<<this->materials[i]->getColor().gety()<<"|"<<this->materials[i]->getColor().getz()<<"  ";
        std::cout<<this->materials[i]->getName()<<"  "<<std::endl;
    }
    }
    else{
        std::cout<<"None"<<std::endl;
    }
}

//Function of class Model, showVertices()
//Function to show information about all vertices
// Arguments for showVertices(): none.
// return value: none(information printed)
void Model::showVertices()
{
    std::cout<<"Vertices:"<<std::endl;
    if(this->vertices.size()>0){
    for(int i = 0; i<(int)this->vertices.size(); i++)
    {
        std::cout<<this->vertices[i].getID()<<":  "<<this->vertices[i].getx()<<"  "<<this->vertices[i].gety()<<"  "<<this->vertices[i].getz()<<std::endl;
    }
    }
    else{
        std::cout<<"None"<<std::endl;
    }
}

//Function of class Model, showCells()
//Function to show information about all cells
// Arguments for showCells(): none.
// return value: none(information printed)
void Model::showCells()
{
    std::cout<<"Cells:"<<std::endl;
    if(this->cells.size()>0){
    for(int i = 0; i<(int)this->cells.size(); i++)
    {
        std::cout<<this->cells[i]->getID()<<": ";
        switch(this->cells[i]->getType())
        {
        case 1:
            std::cout<<"hexahredal ";
            break;
        case 2:
            std::cout<<"pyramid ";
            break;
        case 3:
            std::cout<<"tetrahedral ";
            break;
        }

        std::cout<<"Indices: ";
        for(int n = 0; n<this->cells[i]->getIndices().size(); n++)
        {
            std::cout<<this->cells[i]->getIndices()[n]<<"  ";
        }
        std::cout<<std::endl;
    }
    }
    else{
        std::cout<<"None"<<std::endl;
    }
}

//Function of class Model, getVertices()
//Function to get vertices array of model
// Arguments for showCells(): none.
// return value: std::vector<Vector3D> - array of all model vertices
std::vector<Vector3D> Model::getVertices()
{
    return this->vertices;
}

//Function of class Model, getMaterials()
//Function to get materials array of model
// Arguments for showCells(): none.
// return value: std::vector<Material*> - array of all model material pointers
std::vector<Material*> Model::getMaterials()
{
    return this->materials;
}

//Function of class Model, getCells()
//Function to get cells array of model
// Arguments for getCells(): none.
// return value: std::vector<Cell*> - array of all model cell pointers
std::vector<Cell*> Model::getCells()
{
    return this->cells;
}

//Function of class Model, getVerticesAmount()
//Function to get amount of vertices
// Arguments for getVerticesAmount(): none.
// return value: int - amount of vertices
int Model::getVerticesAmount()
{
    return this->vertices.size();
}

//Function of class Model, getCellAmount()
//Function to get amount of cells
// Arguments for getCellAmount(): none.
// return value: int - amount of cells
int Model::getCellAmount()
{
    return this->cells.size();
}

//Function of class Model, loadInfoToFile()
//Function to load model information into specified txt file.
// Arguments for getVerticesAmount(): char - path to specified txt file
// return value: none(information loaded)
void Model::loadInfoToFile(char* path)
{
    std::ofstream file(path);
    if (file.is_open())
    {
        std::cout<<"FIle ON"<<std::endl;
        file<<"Model data\n";
        for(int i = 0; i<(int)this->vertices.size(); i++)
        {
            file<<"v "<<i<<" "<<this->vertices[i].getx()<<" "<<this->vertices[i].gety()<<" "<<this->vertices[i].getz()<<"\n";
        }
        file<<"\n";
        for(int i = 0; i<(int)this->materials.size(); i++)
        {
            file<<"m "<<this->materials[i]->getID()<<" "<<this->materials[i]->getDensity()<<" ";
            file<<floatToHex(this->materials[i]->getColor().getx())<<floatToHex(this->materials[i]->getColor().gety())<<floatToHex(this->materials[i]->getColor().getz())<<" ";
            file<<this->materials[i]->getName()<<"\n";
        }
        file<<"\n";
        for(int i = 0; i<(int)this->cells.size(); i++)
        {
            file<<"c "<<this->cells[i]->getID()<<" ";
            switch(this->cells[i]->getType())
            {
            case 1:
                file<<"h ";
                break;
            case 2:
                file<<"p ";
                break;
            case 3:
                file<<"t ";
                break;
            }
            //file<<this->cells[i]->mater<<" ";
            for(int n = 0; n<this->cells[i]->getIndices().size(); n++)
            {
                file<<this->cells[i]->getIndices()[n]<<" ";
            }
            file<<"\n";
        }
    }
    file.close();
}
