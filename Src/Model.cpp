#include "../Inc/Model.h"

//side functions
float getHexValue(char letter)
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

int Model::getVectorIndex(int ID)
{
    if(ID<this->vertices.size())
    {
        return ID;
    }
    else
    {
        for(int i = this->vertices.size(); i--;)
        {
            if(this->vertices[i].getID()==ID)
            {
                return i;
            }
        }
    }
    return -1;
}

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
    return Material{};
}

void Model::allignVertices()
{
    for(int i =0; i<this->vertices.size()-1; i++)
    {
        for(int n = 0; n<this->vertices.size()-i-1; n++)koijkonj
        {
            if(this->vertices[n].getID()>this->vertices[n+1].getID())
            {
                std::swap(this->vertices[n],this->vertices[n+1]);
            }
        }
    }
}
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
void Model::loadModel(char* path)
{
    //temporary file data storage
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
                    case 3:{
                        switch(valueIterator)
                        {
                        case 0:
                            tempCol.setx(getHexValue(line[i])*16/255);
                            tempCol.sety(0);
                            tempCol.setz(0);
                            break;
                        case 1:
                            tempCol.setx(tempCol.getx()+getHexValue(line[i])/255);
                            break;
                        case 2:
                            tempCol.sety(getHexValue(line[i])*16/255);
                            break;
                        case 3:
                            tempCol.sety(tempCol.gety()+getHexValue(line[i])/255);
                            break;
                        case 4:
                            tempCol.setz(getHexValue(line[i])*16/255);
                            break;
                        case 5:
                            tempCol.setz(tempCol.getz()+getHexValue(line[i])/255);
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

void Model::showMaterials()
{
    std::cout<<"Materials:"<<std::endl;
    for(int i = 0; i<(int)this->materials.size(); i++)
    {
        std::cout<<this->materials[i]->getID()<<":  ";
        std::cout<<this->materials[i]->getDensity()<<" ";
        std::cout<<this->materials[i]->getColor().getx()<<"|"<<this->materials[i]->getColor().gety()<<"|"<<this->materials[i]->getColor().getz()<<"  ";
        std::cout<<this->materials[i]->getName()<<"  "<<std::endl;
    }
}

void Model::showVertices()
{
    std::cout<<"Vertices:"<<std::endl;
    for(int i = 0; i<(int)this->vertices.size(); i++)
    {
        std::cout<<this->vertices[i].getID()<<":  "<<this->vertices[i].getx()<<"  "<<this->vertices[i].gety()<<"  "<<this->vertices[i].getz()<<std::endl;
    }
}

void Model::showCells()
{
    std::cout<<"Cells:"<<std::endl;
    for(int i = 0; i<(int)this->cells.size(); i++)
    {
        std::cout<<this->cells[i]->getID()<<": ";
        switch(this->cells[i]->getType())
        {
        case 1:
            std::cout<<"hexahedral ";
            break;
        case 2:
            std::cout<<"pyramid ";
            break;
        case 3:
            std::cout<<"tetrahedral ";
            break;
        }
        //std::cout<<this->cells[i]->mater<<std::endl;
        std::cout<<"Indices: ";
        for(int n = 0; n<this->cells[i]->getIndices().size(); n++)
        {
            std::cout<<this->cells[i]->getIndices()[n]<<"  ";
        }
        std::cout<<std::endl;
    }
}

int Model::getVerticesAmount()
{
    return this->vertices.size();
}

int Model::getCellAmount()
{
    return this->cells.size();
}

void Model::loadInfoToFile(char* path)
{
    std::ofstream file(path);
    if (file.is_open())
    {
        std::cout<<"FIle ON"<<std::endl;
        file<<"Model data\n";
        for(int i = 0; i<(int)this->vertices.size(); i++)
        {
            file<<"v "<<this->vertices[i].getID()<<" "<<this->vertices[i].getx()<<" "<<this->vertices[i].gety()<<" "<<this->vertices[i].getz()<<"\n";
        }
        file<<"\n";
        for(int i = 0; i<(int)this->materials.size(); i++)
        {
            file<<"m "<<this->materials[i]->getID()<<" "<<this->materials[i]->getDensity()<<" ";
            file<<this->materials[i]->getColor().getx()<<" "<<this->materials[i]->getColor().gety()<<" "<<this->materials[i]->getColor().getz()<<" ";
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

Model::Model(char* path)
{
    loadModel(path);
    std::cout<<"Model Loaded"<<std::endl;
}
