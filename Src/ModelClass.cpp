#include <../Inc/ModelClass.h>

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

void Model::allignVertices()
{
    for(int i =0; i<this->vertices.size()-1; i++)
    {
        for(int n = 0; n<this->vertices.size()-i-1; n++)
        {
            if(this->vertices[n].ID>this->vertices[n+1].ID)
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
            if(this->cells[n]->ID>this->cells[n+1]->ID)
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
            if(this->materials[n]->ID>this->materials[n+1]->ID)
            {
                std::swap(this->materials[n],this->materials[n+1]);
            }
        }
    }
}

vertice Model::calcModelCenter()
{
    for(int i = 0; i<this->cells.size(); i++)
    {

    }
}
void Model::loadModel(char* path)
{
    std::fstream file;
    std::string line;
    file.open(path);
    int valueNum = 1;
    int valueIterator = 0;
    int firstChar = 0;
    while(getline(file,line))
    {
        valueNum=1;
        switch(line[0])
        {
        case 'm':
        {
            material* tempMat = new material();
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
                            tempMat->ID = atoi( &line[i] );
                            firstChar=0;
                        }
                        break;
                    case 2:
                        if(firstChar)
                        {
                            firstChar=0;
                            tempMat->density = atoi( &line[i] );
                        }
                        break;
                    case 3:
                        switch(valueIterator)
                        {
                        case 0:
                            tempMat->color[0] = (getHexValue(line[i])*16/255);
                            tempMat->color[1] = 0;
                            tempMat->color[2] = 0;
                            break;
                        case 1:
                            tempMat->color[0] += (getHexValue(line[i])/255);
                            break;
                        case 2:
                            tempMat->color[1] = (getHexValue(line[i])*16/255);
                            break;
                        case 3:
                            tempMat->color[1] += (getHexValue(line[i])/255);
                            break;
                        case 4:
                            tempMat->color[2] = (getHexValue(line[i])*16/255);
                            break;
                        case 5:
                            tempMat->color[2] += (getHexValue(line[i])/255);
                            break;
                        }
                        valueIterator++;
                        break;
                    case 4:
                        tempMat->name.push_back(line[i]);
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
            vertice tempVert;
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
                                tempVert.ID = atoi( &line[i] );
                                firstChar=0;
                            }
                            break;
                        case 2:
                            charVal = line[i] - '0';
                            if(firstChar)
                            {
                                firstChar=0;
                                tempVert.x = charVal;
                            }
                            else
                            {
                                if(afterDot)
                                {
                                    tempVert.x +=((float)pow(10,(-valueIterator))*charVal);
                                }
                                else
                                {
                                    tempVert.x = (tempVert.x*10+charVal);
                                }
                            }
                            break;
                        case 3:
                            charVal = line[i] - '0';
                            if(firstChar)
                            {
                                firstChar=0;
                                tempVert.y = charVal;
                            }
                            else
                            {
                                if(afterDot)
                                {
                                    tempVert.y +=((float)pow(10,(-valueIterator))*charVal);
                                }
                                else
                                {
                                    tempVert.y = (tempVert.y*10+charVal);
                                }
                            }
                            break;
                        case 4:
                            charVal = line[i] - '0';
                            if(firstChar)
                            {
                                firstChar=0;
                                tempVert.z = charVal;
                            }
                            else
                            {
                                if(afterDot)
                                {
                                    tempVert.z +=((float)pow(10,(-valueIterator))*charVal);
                                }
                                else
                                {
                                    tempVert.z = (tempVert.z*10+charVal);
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
                            tempVert.ID = -(tempVert.ID);
                            break;
                        case 2:
                            tempVert.x = -(tempVert.x);
                            break;
                        case 3:
                            tempVert.y = -(tempVert.y);
                            break;
                        case 4:
                            tempVert.z = -(tempVert.z);
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
                            tempVert.ID = -(tempVert.ID);
                            break;
                        case 2:
                            tempVert.x = -(tempVert.x);
                            break;
                        case 3:
                            tempVert.y = -(tempVert.y);
                            break;
                        case 4:
                            tempVert.z = -(tempVert.z);
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
            cell* tempCell = new cell();
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
                            tempCell->indices.push_back(atoi( &line[i] ));
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
            tempCell->weight = 0;
            tempCell->volume = 0;
            tempCell->gravityCenter = vertice{-1,0,0,0};

            this->cells.push_back(tempCell);
            break;
        }
        }
    }
    file.close();
}

void Model::showMaterials()
{
    std::cout<<"Materials:"<<std::endl;
    for(int i = 0; i<(int)this->materials.size(); i++)
    {
        std::cout<<this->materials[i]->ID<<":  ";
        std::cout<<this->materials[i]->density<<" ";
        std::cout<<this->materials[i]->color[0]<<"|"<<this->materials[i]->color[1]<<"|"<<this->materials[i]->color[2]<<"  ";
        std::cout<<this->materials[i]->name<<"  "<<std::endl;
    }
}

void Model::showVertices()
{
    std::cout<<"Vertices:"<<std::endl;
    for(int i = 0; i<(int)this->vertices.size(); i++)
    {
        std::cout<<this->vertices[i].ID<<":  "<<this->vertices[i].x<<"  "<<this->vertices[i].y<<"  "<<this->vertices[i].z<<std::endl;
    }
}

void Model::showCells()
{
    std::cout<<"Cells:"<<std::endl;
    for(int i = 0; i<(int)this->cells.size(); i++)
    {
        std::cout<<this->cells[i]->ID<<": ";
        switch(this->cells[i]->type)
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
        std::cout<<this->cells[i]->materialID<<std::endl;
        std::cout<<"Indices: ";
        for(int n = 0; n<this->cells[i]->indices.size(); n++)
        {
            std::cout<<this->cells[i]->indices[n]<<"  ";
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
            file<<"v "<<this->vertices[i].ID<<" "<<this->vertices[i].x<<" "<<this->vertices[i].y<<" "<<this->vertices[i].z<<"\n";
        }
        file<<"\n";
        for(int i = 0; i<(int)this->materials.size(); i++)
        {
            file<<"m "<<this->materials[i]->ID<<" "<<this->materials[i]->density<<" ";
            file<<this->materials[i]->color[0]<<" "<<this->materials[i]->color[1]<<" "<<this->materials[i]->color[2]<<" ";
            file<<this->materials[i]->name<<"\n";
        }
        file<<"\n";
        for(int i = 0; i<(int)this->cells.size(); i++)
        {
            file<<"c "<<this->cells[i]->ID<<" ";
            switch(this->cells[i]->type)
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
            file<<this->cells[i]->materialID<<" ";
            for(int n = 0; n<this->cells[i]->indices.size(); n++)
            {
                file<<this->cells[i]->indices[n]<<" ";
            }
            file<<"\n";
        }
    }
    file.close();
}

Model::Model(char* path)
{
    loadModel(path);
    this->allignVertices();
    this->allignMaterials();
    this->allignCells();
    std::cout<<"Model Loaded"<<std::endl;
}
