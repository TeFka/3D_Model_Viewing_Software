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
    //checks the letter and gives float value
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

    //checks the letter and updates first hex value
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

    //checks the letter and updates first hex value
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

//Default constructor of Model class
//Action:
//      creates an empty model object
//Arguments: none.
Model::Model()
{

}

//Constructor of Model class
//Action:
//      Load a 3D model from specified file.
//Arguments: char - path to a model file.
Model::Model(char* path)
{
    this->loadModel(path);
}

//Destructor for Model class
// Action:
//      Clears vectors, materials and cells arrays.
Model::~Model()
{
    this->vectors.clear();
    this->materials.clear();
    this->cells.clear();
}

//Copy constructor of Model class
//Action:
//copies vectors, materials, cells arrays and the model center information to a new Model object.
Model::Model(const Model& copied_Model)
{
    vectors = copied_Model.vectors;
    materials = copied_Model.materials;
    cells = copied_Model.cells;
    modelCenter = copied_Model.modelCenter;
}

//Function of class Model, getVectorIndex()
//Function to get index in vector array of vector with specified ID.
// Arguments for getVectorIndex(): int - ID to be searched for.
// return value: int - index of vector with specified ID.
//Notes:
// 1) The function will return -1 if the ID is not found, which will most likely give error in the application.
int Model::getVectorIndex(int ID)
{
    //go though vectors
    for(int i = 0; i<this->vectors.size(); i++)
    {
        //find vector with required ID
        if(this->vectors[i].getID()==ID)
        {
            return i;
        }
    }
    std::cout<<"Vector with ID: "<<ID<<" not found"<<std::endl;
    return -1;
}

//Function of class Model, getMaterialIndex()
//Function to get index in material array of Material with specified ID.
// Arguments for getMaterialIndex(): int - ID to be searched for.
// return value: int - index of Material with specified ID.
//Notes:
// 1) The function will return -1 if the ID is not found, which will most likely give error in the application.
int Model::getMaterialIndex(int ID)
{
    //go though vectors
    for(int i = 0; i<this->materials.size(); i++)
    {
        //find vector with required ID
        if(this->materials[i].getID()==ID)
        {
            return i;
        }
    }
    std::cout<<"Material with ID: "<<ID<<" not found"<<std::endl;
    return -1;
}

//Function with template of class Model, alignVectors()
//Function to sort the array of objects.
//type of objects is specified by template
// Arguments for alignArrayID(): std::vector<T> - array of objects specified by template
// return value: none(passed array sorted)
//Notes:
//1) The sorting is done based on the used object member 'ID', received with function 'getID()'
//   if the used object does not have this member and function, sorting function will not work and might crash
template<typename T>
void Model::alignArrayID(std::vector<T>& theArray)
{
    //perform bubble sort
    for(int i =0; i<theArray.size()-1; i++)
    {
        for(int n = 0; n<theArray.size()-i-1; n++)
        {
            if(theArray[n].getID()>theArray[n+1].getID())
            {
                std::swap(theArray[n],theArray[n+1]);
            }
        }
    }
}

//Function of class Model, fixIDValues()
//Function to make all ID values of cell material, vectors and materials that corespond to their position in array
// Arguments for fixIDValues(): none.
// return value: none(vector are given more convenient ID values)
void Model::fixIDValues()
{

    //gives each cell material new ID based on materials position in array
    for(int i =0; i<this->cells.size(); i++)
    {
        this->cells[i].setMaterialID(getMaterialIndex(this->cells[i].getMaterialID()));
    }

    //gives each material new ID based on its position in array
    for(int i =0; i<this->materials.size(); i++)
    {
        this->materials[i].setID(i);
    }

    //gives each vector new ID based on its position in array
    for(int i =0; i<this->vectors.size(); i++)
    {
        this->vectors[i].setID(i);
    }
}

//Function of class Model, calcModelCenter()
//Function to calculate position of model center
// Arguments for calcModelCenter(): none.
// return value: none(model center value updated)
//Note:
//Model center position will become {0,0,0} if vector array is empty.
void Model::calcModelCenter()
{
    // create variables that would store maximum and minimum position values
    double xMin=this->vectors[0].getx();
    double yMin=this->vectors[0].gety();
    double zMin=this->vectors[0].getz();
    double xMax=this->vectors[0].getx();
    double yMax=this->vectors[0].gety();
    double zMax=this->vectors[0].getz();
    //go through all vectors and check their positions
    for(int i = 0; i<this->vectors.size(); i++)
    {
        //update maximum and minimum values based on current vector position
        if(this->vectors[i].getx()>xMax)
        {
            xMax = this->vectors[i].getx();
        }
        if(this->vectors[i].getx()<xMin)
        {
            xMin = this->vectors[i].getx();
        }
        if(this->vectors[i].gety()>yMax)
        {
            yMax = this->vectors[i].gety();
        }
        if(this->vectors[i].gety()<yMin)
        {
            yMin = this->vectors[i].gety();
        }
        if(this->vectors[i].getz()>zMax)
        {
            zMax = this->vectors[i].getz();
        }
        if(this->vectors[i].getz()<zMin)
        {
            zMin = this->vectors[i].getz();
        }
    }

    //set model dimensions
    this->modelDimensions.setx(xMax-xMin);
    this->modelDimensions.sety(yMax-yMin);
    this->modelDimensions.setz(zMax-zMin);

    //set model center vector
    this->modelCenter = Vector3D((xMax+xMin)/2,(yMax+yMin)/2,(zMax+zMin)/2);
}

//Function of class Model, loadModel()
//Function to retrieve 3D model information from a VTK file
// Arguments for loadModel(): char - path to
// return value: bool - statement whether file could be open
//Note:
// 1) The way function reads each file line and retrieves infromation:
//      Material: m material_ID material_density material_color(#000000 form hex code) material_name
//      Vector: v vector_ID x_position y_position z_position
//      Cell: c cell_ID cell_type(h - hexahedral, p - pyramid, t - tetrahedral) [cell_indices]
// 2) In case of file being written incorrectly, incorrect values might be written, errors may occur or program can crash.
bool Model::loadModel(const char* path)
{
    //refresh storage arrays
    this->vectors.clear();
    this->materials.clear();
    this->cells.clear();
    //temporary cell data storage
    std::vector<cellInfo> temporaryCellInfo;

    //used variables
    std::fstream file;
    std::string line;
    int valueNum = 1;
    int valueIterator = 0;
    int firstChar = 0;
    Vector3D tempCol;
    int vecCount = 0;
    file.open(path);

    if(file.is_open())
    {
        //go through all lines in file
        while(getline(file,line))
        {
            valueNum=1;
            //check the first elemnt in the line
            switch(line[0])
            {

            //material case
            case 'm':
            {
                Material temporaryMaterial = Material();
                firstChar = 1;
                //go though line elements except first two
                for(int i =2; i<(int)line.length(); i++)
                {
                    if(line[i]!=' ')
                    {
                        switch(valueNum)
                        {
                        //Getting material ID
                        case 1:

                            if(firstChar)
                            {
                                temporaryMaterial.setID(atoi( &line[i] ));
                                firstChar=0;
                            }
                            break;
                        //Getting material density
                        case 2:
                            if(firstChar)
                            {
                                firstChar=0;
                                temporaryMaterial.setDensity(atoi( &line[i] ));
                            }
                            break;
                        //Getting material color
                        case 3:
                        {
                            //check which hex code letter is retrieved
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
                                temporaryMaterial.setColor(tempCol);
                                break;
                            }
                            valueIterator++;
                            break;
                        }
                        //Getting material name
                        case 4:
                            if(firstChar)
                            {
                                temporaryMaterial.setName(&line[i]);
                                firstChar = 0;
                            }
                            break;
                        }
                    }
                    //if a space is detected, it is assumed that the specific material information is retrieved
                    //moving on to the next piece of information
                    else
                    {
                        firstChar=1;
                        valueNum++;
                        valueIterator = 0;
                    }
                }

                //add material to array
                this->materials.push_back(temporaryMaterial);
                break;
            }
            case 'v':
            {
                Vector3D temporaryVector;
                int charVal;
                int afterDot = 0;
                int negative = 0;
                valueIterator = 0;
                firstChar = 1;
                int exponential = 0;

                //go though line elements except first two
                for(int i =2; i<(int)line.length(); i++)
                {
                    if(line[i]!=' ')
                    {
                        //check if dot was detected indicating that current value is not an integer
                        if(line[i]=='.')
                        {
                            afterDot = 1;
                        }
                        //check if minus was detected indicating that current value is negative
                        else if(line[i]=='-')
                        {
                            negative = 1;
                        }
                        //check if exponential term was detected
                        else if(line[i]=='e')
                        {
                            exponential = 1;
                        }
                        else
                        {
                            switch(valueNum)
                            {
                            //Getting vector ID
                            case 1:
                                if(firstChar)
                                {
                                    temporaryVector.setID(atoi( &line[i] ));
                                    firstChar=0;
                                }
                                break;
                            //getting vector x value
                            case 2:
                                //get number at current line position
                                charVal = line[i] - '0';
                                if(firstChar)
                                {
                                    firstChar=0;
                                    temporaryVector.setx(charVal);
                                }
                                else
                                {
                                    if(afterDot)
                                    {
                                        temporaryVector.setx(temporaryVector.getx()+((float)pow(10,(-valueIterator))*charVal));
                                    }
                                    else
                                    {
                                        temporaryVector.setx(temporaryVector.getx()*10+charVal);
                                    }
                                }
                                break;
                            //getting vector y value
                            case 3:
                                //get number at current line position
                                charVal = line[i] - '0';
                                if(firstChar)
                                {
                                    firstChar=0;
                                    temporaryVector.sety(charVal);
                                }
                                else
                                {
                                    if(afterDot)
                                    {
                                        temporaryVector.sety(temporaryVector.gety()+(float)pow(10,(-valueIterator))*charVal);
                                    }
                                    else
                                    {
                                        temporaryVector.sety(temporaryVector.gety()*10+charVal);
                                    }
                                }
                                break;
                            //getting vector z value
                            case 4:
                                //get number at current line position
                                charVal = line[i] - '0';
                                if(firstChar)
                                {
                                    firstChar=0;
                                    temporaryVector.setz(charVal);
                                }
                                else
                                {
                                    if(afterDot)
                                    {
                                        temporaryVector.setz(temporaryVector.getz()+(float)pow(10,(-valueIterator))*charVal);
                                    }
                                    else
                                    {
                                        temporaryVector.setz(temporaryVector.getz()*10+charVal);
                                    }
                                }
                                break;
                            }
                            valueIterator++;
                        }
                    }
                    //if a space is detected, it is assumed that the specific vector information is retrieved
                    //moving on to the next piece of information
                    else
                    {
                        //change vector values if it should be negative
                        if(negative)
                        {
                            switch(valueNum)
                            {
                            case 1:
                                temporaryVector.setID(-temporaryVector.getID());
                                break;
                            case 2:
                                temporaryVector.setx(-temporaryVector.getx());
                                break;
                            case 3:
                                temporaryVector.sety(-temporaryVector.gety());
                                break;
                            case 4:
                                temporaryVector.setz(-temporaryVector.getz());
                                break;
                            }
                        }

                        //change vector values if there is an exponential term
                        if(exponential)
                        {
                            switch(valueNum)
                            {
                            case 1:
                                temporaryVector.setID(0);
                                break;
                            case 2:
                                temporaryVector.setx(0);
                                break;
                            case 3:
                                temporaryVector.sety(0);
                                break;
                            case 4:
                                temporaryVector.setz(0);
                                break;
                            }
                        }

                        exponential = 0;
                        negative = 0;
                        afterDot = 0;
                        firstChar=1;
                        valueNum++;
                        valueIterator = 0;
                    }
                    //additional case for last line element
                    if(i==line.length()-1)
                    {
                        if(negative)
                        {
                            switch(valueNum)
                            {
                            case 1:
                                temporaryVector.setID(-temporaryVector.getID());
                                break;
                            case 2:
                                temporaryVector.setx(-temporaryVector.getx());
                                break;
                            case 3:
                                temporaryVector.sety(-temporaryVector.gety());
                                break;
                            case 4:
                                temporaryVector.setz(-temporaryVector.getz());
                                break;
                            }
                        }

                        //change vector values if there is an exponential term
                        if(exponential)
                        {
                            switch(valueNum)
                            {
                            case 1:
                                temporaryVector.setID(0);
                                break;
                            case 2:
                                temporaryVector.setx(0);
                                break;
                            case 3:
                                temporaryVector.sety(0);
                                break;
                            case 4:
                                temporaryVector.setz(0);
                                break;
                            }
                        }

                        exponential = 0;
                        negative = 0;
                        afterDot = 0;
                        firstChar=1;
                        valueNum++;
                        valueIterator = 0;
                    }
                }
                //add vector to array
                this->vectors.push_back(temporaryVector);
                break;
            }
            case 'c':
            {
                //creating storage for cell information
                cellInfo temporaryCell = cellInfo();
                firstChar = 1;

                //go though line elements except first two
                for(int i = 2; i<(int)line.length(); i++)
                {
                    if(line[i]!=' ')
                    {
                        //Getting cell ID
                        if(valueNum==1)
                        {
                            if(firstChar)
                            {
                                temporaryCell.ID = atoi( &line[i] );
                                firstChar=0;
                            }
                        }
                        //Getting cell type
                        else if(valueNum==2)
                        {
                            //check type letter
                            switch(line[i])
                            {
                            case 'h':
                                temporaryCell.type = 1;
                                break;
                            case 'p':
                                temporaryCell.type = 2;
                                break;
                            case 't':
                                temporaryCell.type = 3;
                                break;
                            }
                        }
                        //Getting cell material ID
                        else if(valueNum==3)
                        {
                            if(firstChar)
                            {
                                temporaryCell.materialID = atoi( &line[i] );
                                firstChar=0;
                            }
                        }
                        //Getting cell indices
                        else
                        {
                            if(firstChar)
                            {
                                temporaryCell.indixes.push_back(atoi( &line[i] ));
                                firstChar=0;
                            }
                        }
                    }
                    //if a space is detected, it is assumed that the specific cell information is retrieved
                    //moving on to the next piece of information
                    else
                    {
                        valueNum++;
                        firstChar = 1;
                    }
                }

                //add cell information to array
                temporaryCellInfo.push_back(temporaryCell);
                break;
            }
            }
        }
        file.close();
        //sort vectors and materials based on ID
        this->alignArrayID<Vector3D>(this->vectors);
        this->alignArrayID<Material>(this->materials);

        for(int tC = 0; tC<temporaryCellInfo.size(); tC++)
        {
            //change temporary indices array to have vector positions in array
            for(int n = 0; n<temporaryCellInfo[tC].indixes.size(); n++)
            {
                temporaryCellInfo[tC].indixes[n] = this->getVectorIndex(temporaryCellInfo[tC].indixes[n]);
            }
        }

        //fix any ID values
        this->fixIDValues();

        for(int tC = 0; tC<temporaryCellInfo.size(); tC++)
        {
            //create hexadron
            if(temporaryCellInfo[tC].type==1)
            {
                //create cell based on cell information
                //and add it to array
                this->cells.push_back(Hexahedron(temporaryCellInfo[tC].ID,temporaryCellInfo[tC].type,temporaryCellInfo[tC].materialID,
                                                 temporaryCellInfo[tC].indixes,
                                                 this->vectors,this->materials));
            }
            //create pyramid
            else if(temporaryCellInfo[tC].type==2)
            {

                //create cell based on cell information
                //and add it to array
                this->cells.push_back(Pyramid(temporaryCellInfo[tC].ID,temporaryCellInfo[tC].type,temporaryCellInfo[tC].materialID,
                                              temporaryCellInfo[tC].indixes,
                                              this->vectors,this->materials));
            }
            //create tetrahedron
            else if(temporaryCellInfo[tC].type==3)
            {
                //create cell based on cell information
                //and add it to array
                this->cells.push_back(Tetrahedron(temporaryCellInfo[tC].ID,temporaryCellInfo[tC].type,temporaryCellInfo[tC].materialID,
                                                  temporaryCellInfo[tC].indixes,
                                                  this->vectors,this->materials));
            }
        }
        //sort cells
        this->alignArrayID<Cell>(this->cells);

        //calculate model center
        this->calcModelCenter();

        return true;
    }
    else
    {
        std::cout<<"Could not load model from file: "<<path<<std::endl;
        return false;
    }
}

//Function of class Model, showMaterials()
//Function to show information about all materials
// Arguments for showMaterials(): none.
// return value: none(information printed)
void Model::showMaterials()
{
    std::cout<<"Materials:"<<std::endl;
    if(this->materials.size()>0)
    {
        for(int i = 0; i<(int)this->materials.size(); i++)
        {
            std::cout<<this->materials[i].getID()<<":  ";
            std::cout<<this->materials[i].getDensity()<<" ";
            std::cout<<this->materials[i].getColor().getx()<<"|"<<this->materials[i].getColor().gety()<<"|"<<this->materials[i].getColor().getz()<<"  ";
            std::cout<<this->materials[i].getName()<<"  "<<std::endl;
        }
    }
    else
    {
        std::cout<<"None"<<std::endl;
    }
}

//Function of class Model, showVectors()
//Function to show information about all vectors
// Arguments for showVectors(): none.
// return value: none(information printed)
void Model::showVectors()
{
    std::cout<<"vectors:"<<std::endl;
    if(this->vectors.size()>0)
    {
        for(int i = 0; i<(int)this->vectors.size(); i++)
        {
            std::cout<<this->vectors[i].getID()<<":  "<<this->vectors[i].getx()<<"  "<<this->vectors[i].gety()<<"  "<<this->vectors[i].getz()<<std::endl;
        }
    }
    else
    {
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
    if(this->cells.size()>0)
    {
        for(int i = 0; i<(int)this->cells.size(); i++)
        {
            std::cout<<this->cells[i].getID()<<": ";
            switch(this->cells[i].getType())
            {
            case 1:
                std::cout<<"hexahredal "<<std::endl;
                break;
            case 2:
                std::cout<<"pyramid "<<std::endl;
                break;
            case 3:
                std::cout<<"tetrahedral "<<std::endl;
                break;
            }

            std::cout<<"Material: "<<this->materials[this->cells[i].getMaterialID()].getName()<<std::endl;

            std::cout<<"Indices: ";
            for(int n = 0; n<this->cells[i].getIndices().size(); n++)
            {
                std::cout<<this->cells[i].getIndices()[n]<<"  ";
            }
            std::cout<<std::endl;
            std::cout<<"Volume: "<<this->cells[i].getVolume()<<std::endl;
            std::cout<<"Weight: "<<this->cells[i].getVolume()<<std::endl;
            std::cout<<"Centre of gravity: "<<this->cells[i].getCentreOfGravity().getx()<<"  "<<this->cells[i].getCentreOfGravity().gety()<<"  "
                     <<this->cells[i].getCentreOfGravity().getz()<<std::endl;
        }
    }
    else
    {
        std::cout<<"None"<<std::endl;
    }
}

//Function of class Model, getModelCenter()
//Function to get position of model center
// Arguments for getModelCenter(): none.
// return value: Vector3D - model center position
Vector3D Model::getModelCenter()
{
    return this->modelCenter;
}

//Function of class Model, getModelDimensions()
//Function to get position of model dimensions
// Arguments for getModelDimensions(): none.
// return value: Vector3D - vector showing model dimensions
Vector3D Model::getModelDimensions()
{
    return this->modelDimensions;
}

//Function of class Model, getVectors()
//Function to get vector array of model
// Arguments for getVectors(): none.
// return value: std::vector<Vector3D> - array of all model vectors
std::vector<Vector3D> Model::getVectors()
{
    return this->vectors;
}

//Function of class Model, getMaterials()
//Function to get materials array of model
// Arguments for getMaterials(): none.
// return value: std::vector<Material*> - array of all model material pointers
std::vector<Material> Model::getMaterials()
{
    return this->materials;
}

//Function of class Model, getCells()
//Function to get cells array of model
// Arguments for getCells(): none.
// return value: std::vector<Cell*> - array of all model cell pointers
std::vector<Cell> Model::getCells()
{
    return this->cells;
}

//Function of class Model, getCells()
//Function to get a specific cell
// Arguments for getCells(): none.
// return value: cell - the retrieved cell
Cell Model::getCell(int index)
{
    return this->cells[index];
}

//Function of class Model, getVector()
//Function to get a specific vector
// Arguments for getVector(): none.
// return value: cell - the retrieved cell
Vector3D Model::getVector(int index)
{
    return this->vectors[index];
}

//Function of class Model, getVector()
//Function to get a specific vector
// Arguments for getVector(): none.
// return value: cell - the retrieved cell
Material Model::getMaterial(int index)
{
    return this->materials[index];
}

//Function of class Model, getVectorAmount()
//Function to get amount of vectors
// Arguments for getVectorAmount(): none.
// return value: int - amount of vectors
int Model::getVectorAmount()
{
    return this->vectors.size();
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
// Arguments for getvectorsAmount(): char - path to specified txt file
// return value: none(information loaded)
void Model::loadInfoToFile(char* path)
{
    std::ofstream file(path);
    if (file.is_open())
    {
        std::cout<<"Writing to file: "<<path<<std::endl;
        file<<"Model data\n";

        //write all vector data
        for(int i = 0; i<(int)this->vectors.size(); i++)
        {
            file<<"v "<<this->vectors[i].getID()<<" "<<this->vectors[i].getx()<<" "<<this->vectors[i].gety()<<" "<<this->vectors[i].getz()<<"\n";
        }
        file<<"\n";

        //write all material data
        for(int i = 0; i<(int)this->materials.size(); i++)
        {
            file<<"m "<<this->materials[i].getID()<<" "<<this->materials[i].getDensity()<<" ";
            file<<floatToHex(this->materials[i].getColor().getx())<<floatToHex(this->materials[i].getColor().gety())<<floatToHex(this->materials[i].getColor().getz())<<" ";
            file<<this->materials[i].getName()<<"\n";
        }
        file<<"\n";

        //write all cell data
        for(int i = 0; i<(int)this->cells.size(); i++)
        {
            file<<"c "<<this->cells[i].getID()<<" ";

            //check type
            switch(this->cells[i].getType())
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
            file<<this->cells[i].getMaterialID()<<" ";
            for(int n = 0; n<this->cells[i].getIndices().size(); n++)
            {
                file<<this->cells[i].getIndices()[n]<<" ";
            }
            file<<"\n";
        }
    }
    file.close();
}
