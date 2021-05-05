
#include "../Inc/VTKObjectHandler.h"


VTKObjectHandler::VTKObjectHandler()
{

}


void VTKObjectHandler::refresh()
{
    this->activeCells->Reset();
    this->activeCells->Squeeze();
    this->materials.clear();
}

vtkAlgorithmOutput* VTKObjectHandler::getSource()
{
    return this->finalSourceAlgorithm;
}
vtkSmartPointer<vtkUnstructuredGrid> VTKObjectHandler::getGrid()
{
    return this->activeGrid;
}
vtkSmartPointer<vtkPoints> VTKObjectHandler::getPoints()
{
    return this->activePoints;
}
vtkSmartPointer<vtkCellArray> VTKObjectHandler::getCells()
{
    return this->activeCells;
}

QColor VTKObjectHandler::getColor()
{
    return this->activeColor;
}

std::array<double,3> VTKObjectHandler::getCellColor(int index)
{
    this->separateCellColors[index];
}

int VTKObjectHandler::getObjectType()
{
    return this->objectType;
}
double VTKObjectHandler::getVolume()
{
    return this->objectVolume;
}
double VTKObjectHandler::getWeight()
{
    return this->objectWeight;
}

int VTKObjectHandler::getCellAmount()
{
    return this->cellAmount;
}

int VTKObjectHandler::getMinActiveCell()
{
    return this->minActiveCell;
}
int VTKObjectHandler::getMaxActiveCell()
{
    return this->maxActiveCell;
}

Vector3D VTKObjectHandler::getPosition()
{
    return this->objectPosition;
}
Vector3D VTKObjectHandler::getDimensions()
{
    return this->objectDimensions;
}
double VTKObjectHandler::getDimensionAverage()
{
    return this->dimensionAverage;
}

void VTKObjectHandler::setColor(QColor color)
{
    this->activeColor = color;
}
void VTKObjectHandler::setCellColor(int index,double redVal,double greenVal,double blueVal)
{
    this->separateCellColors[index][0] = redVal;
    this->separateCellColors[index][1] = greenVal;
    this->separateCellColors[index][2] = blueVal;
}

void VTKObjectHandler::setMinActiveCell(int newVal)
{
    this->minActiveCell = newVal;
}

void VTKObjectHandler::setMaxActiveCell(int newVal)
{
    this->maxActiveCell = newVal;
}

void VTKObjectHandler::makeMeasurements()
{
    if(objectType==2||objectType==0)
    {
        this->objectDimensions.setx(1.0);
        this->objectDimensions.sety(1.0);
        this->objectDimensions.setz(1.0);

        this->objectPosition.setx(0.0);
        this->objectPosition.setx(0.0);
        this->objectPosition.setx(0.0);

        this->dimensionAverage = 1.0;
    }
    else if(objectType==1)
    {
        this->activePoints = this->activeReader->GetOutput()->GetPoints();
        double xMin=0;
        double yMin=0;
        double zMin=0;
        double xMax=0;
        double yMax=0;
        double zMax=0;
        //go through all vectors and check their positions
        for(int i = 0; i<this->activePoints->GetNumberOfPoints(); i++)
        {
            double STLpoint[3];
            this->activePoints->GetPoint(i,STLpoint);
            //update maximum and minimum values based on current vector position
            if(STLpoint[0]>xMax)
            {
                xMax = STLpoint[0];
            }
            if(STLpoint[0]<xMin)
            {
                xMin = STLpoint[0];
            }
            if(STLpoint[1]>yMax)
            {
                yMax = STLpoint[1];
            }
            if(STLpoint[1]<yMin)
            {
                yMin = STLpoint[1];
            }
            if(STLpoint[2]>zMax)
            {
                zMax = STLpoint[2];
            }
            if(STLpoint[2]<zMin)
            {
                zMin = STLpoint[2];
            }
        }

        //set model dimensions
        this->objectDimensions.setx(xMax-xMin);
        this->objectDimensions.sety(yMax-yMin);
        this->objectDimensions.setz(zMax-zMin);

        this->objectPosition.setx((xMax+xMin)/2);
        this->objectPosition.setx((yMax+yMin)/2);
        this->objectPosition.setx((zMax+zMin)/2);

        this->dimensionAverage = ((this->objectDimensions.getx()+this->objectDimensions.gety()+this->objectDimensions.getz())/3);
    }
    else
    {
        this->objectDimensions.setx(this->activeVTKModel.getModelDimensions().getx());
        this->objectDimensions.sety(this->activeVTKModel.getModelDimensions().gety());
        this->objectDimensions.setz(this->activeVTKModel.getModelDimensions().getz());

        this->objectPosition.setx(this->activeVTKModel.getModelCenter().getx());
        this->objectPosition.setx(this->activeVTKModel.getModelCenter().gety());
        this->objectPosition.setx(this->activeVTKModel.getModelCenter().getz());

        this->dimensionAverage = ((this->objectDimensions.getx()+this->objectDimensions.gety()+this->objectDimensions.getz())/3);
    }

    if(this->objectType<3)
    {
        this->objectParameters->SetInputConnection(this->finalSourceAlgorithm);
        this->objectVolume = this->objectParameters->GetVolume();
    }
}

void VTKObjectHandler::updateVTKModel()
{
    if(this->objectType==3)
    {
        this->activeCells->Reset();
        this->activeCells->Squeeze();

        this->activeGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
        this->cellColorData = vtkSmartPointer<vtkUnsignedCharArray>::New();

        this->activeGrid->SetPoints(this->activePoints);

        cellColorData->SetNumberOfComponents(3);

        this->objectVolume = 0.0;
        this->objectWeight = 0.0;

        //set values
        for(int i = 0; i<this->activeVTKModel.getCellAmount(); i++)
        {
            if(i>=(minActiveCell-1)&&i<maxActiveCell)
            {
                Cell tempCell = this->activeVTKModel.getCell(i);
                if(tempCell.getType()==1)
                {
                    this->drawHexahedron(&tempCell);
                }
                if(tempCell.getType()==2)
                {
                    this->drawPyramid(&tempCell);
                }
                if(tempCell.getType()==3)
                {
                    this->drawTetrahedron(&tempCell);
                }

                this->objectVolume += tempCell.getVolume();
                this->objectWeight += tempCell.getWeight();

                float rgb[3];
                rgb[0] = 255*this->separateCellColors[i][0];
                rgb[1] = 255*this->separateCellColors[i][1];
                rgb[2] = 255*this->separateCellColors[i][2];
                cellColorData->InsertNextTuple(rgb);
            }
        }
        this->activeGrid->GetCellData()->SetScalars(this->cellColorData);

        this->objectType = 3;


        this->geometryFilter->SetInputData(this->activeGrid);
        this->finalSourceAlgorithm = this->geometryFilter->GetOutputPort();

        this->makeMeasurements();
    }
}

void VTKObjectHandler::drawHexahedron(Cell *cell)
{
    std::vector<int> indx = cell->getIndices();
    vtkSmartPointer<vtkHexahedron> hex = vtkSmartPointer<vtkHexahedron>::New();

    for(auto n = 0; n<8; n++)
    {
        hex->GetPointIds()->SetId(n,indx[n]);
    }

    this->activeCells->InsertNextCell(hex);
    this->activeGrid->InsertNextCell(hex->GetCellType(), hex->GetPointIds());
}

void VTKObjectHandler::drawTetrahedron(Cell *cell)
{
    std::vector<int> indx = cell->getIndices();
    vtkSmartPointer<vtkTetra> tetr = vtkSmartPointer<vtkTetra>::New();

    for(auto n = 0; n<4; n++)
    {
        tetr->GetPointIds()->SetId(n,indx[n]);
    }

    this->activeCells->InsertNextCell(tetr);
    this->activeGrid->InsertNextCell(tetr->GetCellType(), tetr->GetPointIds());
}

void VTKObjectHandler::drawPyramid(Cell *cell)
{
    std::vector<int> indx = cell->getIndices();
    vtkSmartPointer<vtkPyramid> pyr = vtkSmartPointer<vtkPyramid>::New();

    for(auto n = 0; n<5; n++)
    {
        pyr->GetPointIds()->SetId(n,indx[n]);
    }

    this->activeCells->InsertNextCell(pyr);
    this->activeGrid->InsertNextCell(pyr->GetCellType(), pyr->GetPointIds());
}

void VTKObjectHandler::displayHexahedron()
{

    this->refresh();
    this->activeGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();

    this->activePoints = vtkSmartPointer<vtkPoints>::New();

    this->activeCells->Reset();
    this->activeCells->Squeeze();
    //draw
    this->activePoints->InsertNextPoint(0.0, 0.0, 0.0); // Face 1
    this->activePoints->InsertNextPoint(1.0, 0.0, 0.0);
    this->activePoints->InsertNextPoint(1.0, 1.0, 0.0);
    this->activePoints->InsertNextPoint(0.0, 1.0, 0.0);
    this->activePoints->InsertNextPoint(0.0, 0.0, 1.0); // Face 2
    this->activePoints->InsertNextPoint(1.0, 0.0, 1.0);
    this->activePoints->InsertNextPoint(1.0, 1.0, 1.0);
    this->activePoints->InsertNextPoint(0.0, 1.0, 1.0);

    // Create a hexahedron from the this->activePoints.
    vtkSmartPointer<vtkHexahedron> hex = vtkSmartPointer<vtkHexahedron>::New();

    for (auto i = 0; i < 8; ++i)
    {
        hex->GetPointIds()->SetId(i, i);
    }

    this->activeCells->InsertNextCell(hex);
    this->activeGrid->SetPoints(this->activePoints);
    this->activeGrid->InsertNextCell(hex->GetCellType(), hex->GetPointIds());

    this->objectType = 2;

    this->geometryFilter->SetInputData(this->activeGrid);
    this->finalSourceAlgorithm = this->geometryFilter->GetOutputPort();

    this->cellAmount = 1;

    this->makeMeasurements();

    this->minActiveCell = 1;
    this->maxActiveCell = 1;
}

void VTKObjectHandler::displayTetrahedron()
{

    this->refresh();
    this->activeGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();

    this->activePoints = vtkSmartPointer<vtkPoints>::New();
    this->activeCells->Reset();
    this->activeCells->Squeeze();

    //draw
    this->activePoints->InsertNextPoint(0.0, 0.0, 0.0); // Face 1
    this->activePoints->InsertNextPoint(1.0, 0.0, 0.0);
    this->activePoints->InsertNextPoint(1.0, 1.0, 0.0);
    this->activePoints->InsertNextPoint(0.0, 1.0, 1.0);

    // Create a hexahedron from the this->activePoints.
    vtkSmartPointer<vtkTetra> tetr = vtkSmartPointer<vtkTetra>::New();

    for (auto i = 0; i < 4; ++i)
    {
        tetr->GetPointIds()->SetId(i, i);
    }
    this->activeCells->InsertNextCell(tetr);
    this->activeGrid->SetPoints(this->activePoints);
    this->activeGrid->InsertNextCell(tetr->GetCellType(), tetr->GetPointIds());

    this->objectType = 2;

    this->geometryFilter->SetInputData(this->activeGrid);
    this->finalSourceAlgorithm = this->geometryFilter->GetOutputPort();

    this->cellAmount = 1;

    this->makeMeasurements();

    this->minActiveCell = 1;
    this->maxActiveCell = 1;
}

void VTKObjectHandler::displayPyramid()
{

    this->refresh();
    this->activeGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    this->activePoints = vtkSmartPointer<vtkPoints>::New();

    //draw
    this->activePoints->InsertNextPoint(1.0, 1.0, 1.0); // Face 1
    this->activePoints->InsertNextPoint(-1.0, 1.0, 1.0);
    this->activePoints->InsertNextPoint(-1.0, -1.0, 1.0);
    this->activePoints->InsertNextPoint(1.0, -1.0, 1.0);
    this->activePoints->InsertNextPoint(0.0, 0.0, 0.0); // Face 2

    // Create a hexahedron from the this->activePoints.
    vtkSmartPointer<vtkPyramid> pyr = vtkSmartPointer<vtkPyramid>::New();

    for (auto i = 0; i < 5; ++i)
    {
        pyr->GetPointIds()->SetId(i, i);
    }
    this->activeCells->InsertNextCell(pyr);
    this->activeGrid->SetPoints(this->activePoints);
    this->activeGrid->InsertNextCell(pyr->GetCellType(), pyr->GetPointIds());

    this->objectType = 2;

    this->geometryFilter->SetInputData(this->activeGrid);
    this->finalSourceAlgorithm = this->geometryFilter->GetOutputPort();

    this->cellAmount = 1;

    this->makeMeasurements();

    this->minActiveCell = 1;
    this->maxActiveCell = 1;
}

void VTKObjectHandler::displaySphere()
{

    this->refresh();
    vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();


    sphere->SetPhiResolution(21);
    sphere->SetThetaResolution(21);

    this->objectType = 0;

    this->finalSourceAlgorithm = sphere->GetOutputPort();

    this->cellAmount = 1;

    this->makeMeasurements();

    this->minActiveCell = 1;
    this->maxActiveCell = 1;
}
void VTKObjectHandler::displayDisk()
{

    this->refresh();
    vtkSmartPointer<vtkDiskSource> disk = vtkSmartPointer<vtkDiskSource>::New();


    disk->SetCircumferentialResolution(51);

    this->objectType = 0;

    this->finalSourceAlgorithm = disk->GetOutputPort();

    this->cellAmount = 1;

    this->makeMeasurements();

    this->minActiveCell = 1;
    this->maxActiveCell = 1;
}
void VTKObjectHandler::displayCone()
{

    this->refresh();
    vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();

    cone->SetResolution(51);

    this->objectType = 0;

    this->finalSourceAlgorithm = cone->GetOutputPort();

    this->cellAmount = 1;

    this->makeMeasurements();

    this->minActiveCell = 1;
    this->maxActiveCell = 1;
}
void VTKObjectHandler::displayPlane()
{
    this->refresh();
    vtkSmartPointer<vtkPlaneSource> plane = vtkSmartPointer<vtkPlaneSource>::New();

    this->objectType = 0;

    this->finalSourceAlgorithm = plane->GetOutputPort();

    this->cellAmount = 1;

    this->makeMeasurements();

    this->minActiveCell = 1;
    this->maxActiveCell = 1;
}
void VTKObjectHandler::displayPointCluster(int numberOfPoints)
{

    this->refresh();
    vtkSmartPointer<vtkPointSource> cluster = vtkSmartPointer<vtkPointSource>::New();


    cluster->SetNumberOfPoints(numberOfPoints);

    this->objectType = 0;

    this->finalSourceAlgorithm = cluster->GetOutputPort();

    this->cellAmount = 1;

    this->makeMeasurements();

    this->minActiveCell = 1;
    this->maxActiveCell = 1;
}
void VTKObjectHandler::displayLine()
{

    this->refresh();
    vtkSmartPointer<vtkLineSource> line = vtkSmartPointer<vtkLineSource>::New();

    this->objectType = 0;

    this->finalSourceAlgorithm = line->GetOutputPort();

    this->cellAmount = 1;

    this->makeMeasurements();

    this->minActiveCell = 1;
    this->maxActiveCell = 1;
}

void VTKObjectHandler::displayCylinder()
{

    this->refresh();
    vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();

    cylinder->SetResolution(51);

    this->objectType = 0;

    this->finalSourceAlgorithm = cylinder->GetOutputPort();

    this->cellAmount = 1;

    this->makeMeasurements();

    this->minActiveCell = 1;
    this->maxActiveCell = 1;
}

void VTKObjectHandler::getModelFromFile(QString fileName)
{

    QFileInfo fi(fileName);
    if(fi.suffix()=="stl")
    {
        this->refresh();

        this->activeReader->SetFileName(fileName.toLatin1().data());
        this->activeReader->Update();
        this->objectType = 1;

        this->objectParameters->SetInputConnection(this->activeReader->GetOutputPort());

        this->finalSourceAlgorithm = this->activeReader->GetOutputPort();

        this->cellAmount = 1;

        this->makeMeasurements();

        this->minActiveCell = 1;
        this->maxActiveCell = 1;
    }
    else if(fi.suffix()=="mod")
    {
        this->refresh();
        this->separateCellColors.clear();

        this->activeGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();

        this->activePoints = vtkSmartPointer<vtkPoints>::New();
        vtkSmartPointer<vtkUnsignedCharArray> cellColorData = vtkSmartPointer<vtkUnsignedCharArray>::New();

        // init model
        this->activeVTKModel.loadModel(fileName.toStdString().c_str());

        std::vector<Vector3D> vectors = this->activeVTKModel.getVectors();

        for(int i =0; i<vectors.size(); i++)
        {
            this->activePoints->InsertNextPoint(vectors[i].getx(),vectors[i].gety(),vectors[i].getz());
        }

        this->activeGrid->SetPoints(this->activePoints);

        cellColorData->SetNumberOfComponents(3);

        this->objectVolume = 0.0;
        this->objectWeight = 0.0;

        //set values
        for(int i = 0; i<this->activeVTKModel.getCellAmount(); i++)
        {
            Cell tempCell = this->activeVTKModel.getCell(i);
            if(tempCell.getType()==1)
            {
                this->drawHexahedron(&tempCell);
            }
            if(tempCell.getType()==2)
            {
                this->drawPyramid(&tempCell);
            }
            if(tempCell.getType()==3)
            {
                this->drawTetrahedron(&tempCell);
            }

            Vector3D color = this->activeVTKModel.getMaterial(tempCell.getMaterialID()).getColor();
            this->separateCellColors.push_back({color.getx(),color.gety(),color.getz()});

            float rgb[3];
            rgb[0] = 255*color.getx();
            rgb[1] = 255*color.gety();
            rgb[2] = 255*color.getz();
            cellColorData->InsertNextTuple(rgb);

            this->objectVolume += tempCell.getVolume();
            this->objectWeight += tempCell.getWeight();
        }

        this->activeGrid->GetCellData()->SetScalars(cellColorData);

        this->objectType = 3;

        this->cellAmount = this->activeVTKModel.getCellAmount();

        this->geometryFilter->SetInputData(this->activeGrid);
        this->finalSourceAlgorithm = this->geometryFilter->GetOutputPort();

        this->makeMeasurements();

        this->minActiveCell = 1;
        this->maxActiveCell = this->cellAmount;
    }
}

void VTKObjectHandler::saveModelToFile(QString fileName)
{
    QFileInfo fi(fileName);

    if(fi.suffix()=="stl")
    {
        vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
        stlWriter->SetFileName(fileName.toLocal8Bit().data());
        stlWriter->SetInputConnection(this->finalSourceAlgorithm);
        stlWriter->Write();
    }
    else if(fi.suffix()=="mod")
    {
        Model savingVTKModel;

        std::vector<Vector3D> tempVectors;
        std::vector<Material> tempMaterials;
        std::vector<Cell> tempCells;

        if(this->objectType==3)
        {
            tempMaterials.push_back(this->activeVTKModel.getMaterial(this->activeVTKModel.getCell(minActiveCell-1).getMaterialID()));

            if(!(this->separateCellColors[minActiveCell-1][0]==tempMaterials[0].getColor().getx()&&
                    this->separateCellColors[minActiveCell-1][1]==tempMaterials[0].getColor().gety()&&
                    this->separateCellColors[minActiveCell-1][2]==tempMaterials[0].getColor().getz()))
            {
               tempMaterials[0].setColor(Vector3D(this->separateCellColors[minActiveCell-1][0],
                                                  this->separateCellColors[minActiveCell-1][1],
                                                  this->separateCellColors[minActiveCell-1][2]));
            }
            for(int i = 0; i<this->activeVTKModel.getCellAmount(); i++)
            {
                if(i>=(minActiveCell-1)&&i<maxActiveCell)
                {
                    Cell tempModelCell = this->activeVTKModel.getCell(i);

                    int materialID = tempModelCell.getMaterialID();
                    int materialExists = 0;
                    for(int m = 0; m<tempMaterials.size(); m++)
                    {
                        if(this->separateCellColors[i][0]==tempMaterials[m].getColor().getx()&&
                                this->separateCellColors[i][1]==tempMaterials[m].getColor().gety()&&
                                this->separateCellColors[i][2]==tempMaterials[m].getColor().getz())
                        {
                            materialID = m;
                            materialExists = 1;
                        }
                    }

                    if(!materialExists){
                        Material newMaterial = this->activeVTKModel.getMaterial(materialID);
                            newMaterial.setColor(Vector3D(this->separateCellColors[i][0],this->separateCellColors[i][1],this->separateCellColors[i][2]));
                            materialID = tempMaterials.size();
                            tempMaterials.push_back(newMaterial);
                    }

                    std::vector<int> indices;

                    for(int n = 0; n<tempModelCell.getIndices().size(); n++)
                    {

                        Vector3D theVector = this->activeVTKModel.getVector(tempModelCell.getIndices()[n]);
                        int vecExists = 0;
                        int vectorPosition = 0;
                        for(int v = 0;v<tempVectors.size();v++){
                            if(theVector.getx()==tempVectors[v].getx()&&
                               theVector.gety()==tempVectors[v].gety()&&
                               theVector.getz()==tempVectors[v].getz()){
                                    vecExists = 1;
                                    vectorPosition = v;
                                    v = tempVectors.size();
                               }
                        }

                        if(!vecExists){
                            indices.push_back(tempVectors.size());
                            theVector.setID(tempVectors.size());
                             tempVectors.push_back(theVector);
                        }
                        else{
                            indices.push_back(vectorPosition);
                        }
                    }

                    Cell tempCell(i,tempModelCell.getType(),materialID,indices);

                    tempCells.push_back(tempCell);

                }
            }

        }
        else if(this->objectType==2)
        {
            for(int i = 0; i<this->activePoints->GetNumberOfPoints(); i++)
            {
                double tempPoint[3];
                this->activePoints->GetPoint(i,tempPoint);
                tempVectors.push_back(Vector3D(tempPoint[0],tempPoint[1],tempPoint[2]));
            }

            for(int i = 0; i<this->activeCells->GetNumberOfCells(); i++)
            {
                int type = 0;

                vtkSmartPointer<vtkIdList> idList;

                this->activeCells->GetCell(i,idList);

                if(idList->GetNumberOfIds()==8)
                {
                    type = 1;
                }
                else if(idList->GetNumberOfIds()==4)
                {
                    type = 2;
                }
                else if(idList->GetNumberOfIds()==5)
                {
                    type = 3;
                }

                std::vector<int> indices;

                for(int n = 0; n<idList->GetNumberOfIds(); n++)
                {
                    indices.push_back(idList->GetId(n));
                }

                Cell tempCell(i,type,0,indices);

                tempCells.push_back(tempCell);
            }

            Vector3D color((double)this->activeColor.red()/255,(double)this->activeColor.green()/255,(double)this->activeColor.blue()/255);
            Material theMaterial(0,1,"N/A",color);
            tempMaterials.push_back(theMaterial);
        }
        else
        {
            std::cout<<"Cannot save as VTK"<<std::endl;
        }

        savingVTKModel.setVectors(tempVectors);
        savingVTKModel.setCells(tempCells);
        savingVTKModel.setMaterials(tempMaterials);

        savingVTKModel.loadInfoToFile(fileName.toLocal8Bit().data());
    }
}

void VTKObjectHandler::changeColor(QColor color)
{

    if(this->objectType==3)
    {
        for(int i = 0; i<this->activeVTKModel.getCellAmount(); i++)
        {
            if(i>=(minActiveCell-1)&&i<maxActiveCell)
            {
                this->separateCellColors[i][0] = (double)color.red()/255;
                this->separateCellColors[i][1] = (double)color.green()/255;
                this->separateCellColors[i][2] = (double)color.blue()/255;
            }
        }
    }
    else
    {
        this->activeColor = color;

    }
}

void VTKObjectHandler::resetColor()
{
    if(this->objectType==3)
    {
        for(int i = 0; i<this->activeVTKModel.getCellAmount(); i++)
        {
            Cell tempCell = this->activeVTKModel.getCell(i);
            this->separateCellColors[i][0] = 0.0;

            Vector3D color = this->activeVTKModel.getMaterial(tempCell.getMaterialID()).getColor();
            this->separateCellColors[i][1] = color.getx();
            this->separateCellColors[i][2] = color.gety();
            this->separateCellColors[i][3] = color.getz();
        }
    }
    else
    {
        this->activeColor.setRed(255);
        this->activeColor.setGreen(0);
        this->activeColor.setBlue(0);
    }
}