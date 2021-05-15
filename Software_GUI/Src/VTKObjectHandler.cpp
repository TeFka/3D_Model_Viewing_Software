
#include "../Inc/VTKObjectHandler.h"

//default constructor
VTKObjectHandler::VTKObjectHandler()
{

}

//function to refresh object data
void VTKObjectHandler::refresh()
{
    this->activeCells->Reset();
    this->activeCells->Squeeze();
}

//function to get  object final source algorithm
vtkAlgorithmOutput* VTKObjectHandler::getSource()
{
    return this->finalSourceAlgorithm;
}

//function to get object poly data
vtkPolyData* VTKObjectHandler::getPolydata()
{
    return this->finalPolyData;
}

//function to get object grid
vtkSmartPointer<vtkUnstructuredGrid> VTKObjectHandler::getGrid()
{
    return this->activeGrid;
}

//function to get object points
vtkSmartPointer<vtkPoints> VTKObjectHandler::getPoints()
{
    return this->finalPolyData->GetPoints();
}

//function to get object cells
vtkSmartPointer<vtkCellArray> VTKObjectHandler::getCells()
{
    return this->activeCells;
}

//function to get number of shown object points
int VTKObjectHandler::getShownPointAmount(){
    if(this->objectType==3){
    return this->shownPoints;
    }
    else{
        return this->finalPolyData->GetPoints()->GetNumberOfPoints();
    }
}

//function to get object main color
QColor VTKObjectHandler::getColor()
{
    return this->activeColor;
}

//function to get color of specific object cell
std::array<double,3> VTKObjectHandler::getCellColor(int index)
{
    return this->separateCellColors[index];
}

//function to get object type
int VTKObjectHandler::getObjectType()
{
    return this->objectType;
}

//function to get object volume
double VTKObjectHandler::getVolume()
{
    return this->objectVolume;
}

//function to get object weight
double VTKObjectHandler::getWeight()
{
    return this->objectWeight;
}

//function to get number of cells object has
int VTKObjectHandler::getCellAmount()
{
    return this->cellAmount;
}

//function to get the number of the lowest cell of the cell list that is shown
int VTKObjectHandler::getMinActiveCell()
{
    return this->minActiveCell;
}

//function to get the number of the highest cell of the cell list that is shown
int VTKObjectHandler::getMaxActiveCell()
{
    return this->maxActiveCell;
}


//function to get object position
Vector3D VTKObjectHandler::getPosition()
{
    return this->objectPosition;
}

//function to get object dimensions
Vector3D VTKObjectHandler::getDimensions()
{
    return this->objectDimensions;
}

//function to get the object dimension average
double VTKObjectHandler::getDimensionAverage()
{
    return this->dimensionAverage;
}


//function to set object color
void VTKObjectHandler::setColor(QColor color)
{
    this->activeColor = color;
}

//function to set color of a specific object cell
void VTKObjectHandler::setCellColor(int index,double redVal,double greenVal,double blueVal)
{
    this->separateCellColors[index][0] = redVal;
    this->separateCellColors[index][1] = greenVal;
    this->separateCellColors[index][2] = blueVal;
}

//function to set minimum cell that will be shown
void VTKObjectHandler::setMinActiveCell(int newVal)
{
    this->minActiveCell = newVal;
}

//function to set maximum cell that will be shown
void VTKObjectHandler::setMaxActiveCell(int newVal)
{
    this->maxActiveCell = newVal;
}

//function to set polydata of object
void VTKObjectHandler::handlePolydata(){
    this->activePoints = this->finalPolyData->GetPoints();
    this->activeCells = this->finalPolyData->GetPolys();
}

//function to set object parameters
void VTKObjectHandler::makeMeasurements()
{
    if(this->objectType==3){

        //use VTK model calss to set parameters of VTk object
        this->objectDimensions.setx(this->activeVTKModel.getModelDimensions().getx());
        this->objectDimensions.sety(this->activeVTKModel.getModelDimensions().gety());
        this->objectDimensions.setz(this->activeVTKModel.getModelDimensions().getz());

        this->objectPosition.setx(this->activeVTKModel.getModelCenter().getx());
        this->objectPosition.sety(this->activeVTKModel.getModelCenter().gety());
        this->objectPosition.setz(this->activeVTKModel.getModelCenter().getz());

        this->dimensionAverage = ((this->objectDimensions.getx()+this->objectDimensions.gety()+this->objectDimensions.getz())/3);

        for(int i = 0; i<this->activeVTKModel.getCellAmount(); i++)
        {
                this->objectVolume += this->activeVTKModel.getCell(i).getVolume();
                this->objectWeight += this->activeVTKModel.getCell(i).getWeight();
        }
    }
    else{

        //set input of parameters for non VTK object
        if(this->objectType==2){
            this->objectParameters->SetInputData(this->activeGrid);
        }
        else{
        this->objectParameters->SetInputData(this->finalPolyData);
        }
        this->objectVolume = this->objectParameters->GetVolume();

        this->objectWeight = 0;

    if(objectType==2||objectType==0)
    {
        //set default parameters for basic object
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
        //set parameters for STl object
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

        //set model dimensions based on minimum and maximum values
        this->objectDimensions.setx(xMax-xMin);
        this->objectDimensions.sety(yMax-yMin);
        this->objectDimensions.setz(zMax-zMin);

        this->dimensionAverage = ((this->objectDimensions.getx()+this->objectDimensions.gety()+this->objectDimensions.getz())/3);

        //set model position based on minimum and maximum values
        this->objectPosition.setx((xMax+xMin)/2);
        this->objectPosition.setx((yMax+yMin)/2);
        this->objectPosition.setx((zMax+zMin)/2);
    }
    }
}

 void VTKObjectHandler::geometryStage(){

 }

//function to update VTK object
void VTKObjectHandler::updateVTKModel()
{
    if(this->objectType==3)
    {
        //refresh data
        this->refresh();

        this->activeGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
        this->cellColorData = vtkSmartPointer<vtkUnsignedCharArray>::New();

        //set points that are chosen to be shown
        this->shownPoints = 0;
        std::vector<int> chosenPoints;

        for(int i = 0;i<this->activeVTKModel.getVectorAmount();i++){
            chosenPoints.push_back(0);
        }

        this->activeGrid->SetPoints(this->activePoints);

        cellColorData->SetNumberOfComponents(3);

        this->objectVolume = 0.0;
        this->objectWeight = 0.0;

        //set cells that should be shown
        for(int i = 0; i<this->activeVTKModel.getCellAmount(); i++)
        {
            if(i>=(minActiveCell-1)&&i<maxActiveCell)
            {
                Cell tempCell = this->activeVTKModel.getCell(i);
                for(int n = 0;n<tempCell.getIndices().size();n++){
                    chosenPoints[tempCell.getIndices()[n]] = 1;
                }

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

        //get amount of point that should be shown
        for(int i = 0;i<this->activeVTKModel.getVectorAmount();i++){
            if(chosenPoints[i]){
                this->shownPoints++;
            }
        }

        this->activeGrid->GetCellData()->SetScalars(this->cellColorData);

        this->objectType = 3;

        this->geometryFilter->SetInputData(this->activeGrid);
        this->finalSourceAlgorithm = this->geometryFilter->GetOutputPort();
        this->finalPolyData = this->geometryFilter->GetOutput();

        //make object measurements
        this->makeMeasurements();
    }
}

//function to create and add hexahedron to the active grid
void VTKObjectHandler::drawHexahedron(Cell *cell)
{
    //get indices of required cell
    std::vector<int> indx = cell->getIndices();

    //declare VTK cell
    vtkSmartPointer<vtkHexahedron> hex = vtkSmartPointer<vtkHexahedron>::New();

    //set cell points
    for(auto n = 0; n<8; n++)
    {
        hex->GetPointIds()->SetId(n,indx[n]);
    }

    //add cell to grid
    this->activeCells->InsertNextCell(hex);
    this->activeGrid->InsertNextCell(hex->GetCellType(), hex->GetPointIds());
}

//function to create and add tetrahedron to the active grid
void VTKObjectHandler::drawTetrahedron(Cell *cell)
{
    //get indices of required cell
    std::vector<int> indx = cell->getIndices();

    //declare VTK cell
    vtkSmartPointer<vtkTetra> tetr = vtkSmartPointer<vtkTetra>::New();

    //set cell points
    for(auto n = 0; n<4; n++)
    {
        tetr->GetPointIds()->SetId(n,indx[n]);
    }

    //add cell to grid
    this->activeCells->InsertNextCell(tetr);
    this->activeGrid->InsertNextCell(tetr->GetCellType(), tetr->GetPointIds());
}

//function to create and add pyramid to the active grid
void VTKObjectHandler::drawPyramid(Cell *cell)
{
    //get indices of required cell
    std::vector<int> indx = cell->getIndices();

    //declare VTK cell
    vtkSmartPointer<vtkPyramid> pyr = vtkSmartPointer<vtkPyramid>::New();

    //set cell points
    for(auto n = 0; n<5; n++)
    {
        pyr->GetPointIds()->SetId(n,indx[n]);
    }

    //add cell to grid
    this->activeCells->InsertNextCell(pyr);
    this->activeGrid->InsertNextCell(pyr->GetCellType(), pyr->GetPointIds());
}

//function to display hexahedron using grid
void VTKObjectHandler::displayHexahedron()
{
    //refresh object data
    this->refresh();
    this->activeGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();

    this->activePoints = vtkSmartPointer<vtkPoints>::New();

    this->activeCells->Reset();
    this->activeCells->Squeeze();

    //define object points
    this->activePoints->InsertNextPoint(-0.5, -0.5, -0.5); // Face 1
    this->activePoints->InsertNextPoint(0.5, -0.5, -0.5);
    this->activePoints->InsertNextPoint(0.5, 0.5, -0.5);
    this->activePoints->InsertNextPoint(-0.5, 0.5, -0.5);
    this->activePoints->InsertNextPoint(-0.5, -0.5, 0.5); // Face 2
    this->activePoints->InsertNextPoint(0.5, -0.5, 0.5);
    this->activePoints->InsertNextPoint(0.5, 0.5, 0.5);
    this->activePoints->InsertNextPoint(-0.5, 0.5, 0.5);

    // Create a VTK cell
    vtkSmartPointer<vtkHexahedron> hex = vtkSmartPointer<vtkHexahedron>::New();

    //set cell points
    for (auto i = 0; i < 8; ++i)
    {
        hex->GetPointIds()->SetId(i, i);
    }

    //add cell to grid
    this->activeCells->InsertNextCell(hex);
    this->activeGrid->SetPoints(this->activePoints);
    this->activeGrid->InsertNextCell(hex->GetCellType(), hex->GetPointIds());

    //define final algorithm
    this->geometryFilter->SetInputData(this->activeGrid);
    this->finalSourceAlgorithm = this->geometryFilter->GetOutputPort();

    //define final poly data
    this->geometryFilter->Update();
    this->finalPolyData = this->geometryFilter->GetOutput();

    //set object data
    this->objectType = 2;
    this->cellAmount = 1;
    this->minActiveCell = 1;
    this->maxActiveCell = 1;

    //make object measurements
    this->makeMeasurements();

}

//function to display hexahedron using grid
void VTKObjectHandler::displayTetrahedron()
{
     //refresh object data
    this->refresh();
    this->activeGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();

    this->activePoints = vtkSmartPointer<vtkPoints>::New();

    //define object points
    this->activePoints->InsertNextPoint(-0.5, -0.5, -0.5); // Face 1
    this->activePoints->InsertNextPoint(0.5, -0.5, -0.5);
    this->activePoints->InsertNextPoint(0.5, 0.5, -0.5);
    this->activePoints->InsertNextPoint(-0.5, 0.5, 0.5);

   // Create a VTK cell
    vtkSmartPointer<vtkTetra> tetr = vtkSmartPointer<vtkTetra>::New();

    //set cell points
    for (auto i = 0; i < 4; ++i)
    {
        tetr->GetPointIds()->SetId(i, i);
    }

    //add cell to grid
    this->activeCells->InsertNextCell(tetr);
    this->activeGrid->SetPoints(this->activePoints);
    this->activeGrid->InsertNextCell(tetr->GetCellType(), tetr->GetPointIds());

     //define final algorithm
    this->geometryFilter->SetInputData(this->activeGrid);
    this->finalSourceAlgorithm = this->geometryFilter->GetOutputPort();

    //define final poly data
    this->geometryFilter->Update();
    this->finalPolyData = this->geometryFilter->GetOutput();

    //set object data
    this->objectType = 2;
    this->cellAmount = 1;
    this->minActiveCell = 1;
    this->maxActiveCell = 1;

    //make object measurements
    this->makeMeasurements();
}

//function to display hexahedron using grid
void VTKObjectHandler::displayPyramid()
{
    //refresh object data
    this->refresh();
    this->activeGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    this->activePoints = vtkSmartPointer<vtkPoints>::New();

    //define object points
    this->activePoints->InsertNextPoint(0.5, -0.5, 0.5); // Face 1
    this->activePoints->InsertNextPoint(-0.5, -0.5, 0.5);
    this->activePoints->InsertNextPoint(-0.5, -0.5, -0.5);
    this->activePoints->InsertNextPoint(0.5, -0.5, -0.5);
    this->activePoints->InsertNextPoint(0.0, 0.5, 0.0); // Face 2

    // Create a VTK cell
    vtkSmartPointer<vtkPyramid> pyr = vtkSmartPointer<vtkPyramid>::New();

    //set cell points
    for (auto i = 0; i < 5; ++i)
    {
        pyr->GetPointIds()->SetId(i, i);
    }

    //add cell to grid
    this->activeCells->InsertNextCell(pyr);
    this->activeGrid->SetPoints(this->activePoints);
    this->activeGrid->InsertNextCell(pyr->GetCellType(), pyr->GetPointIds());

     //define final algorithm
    this->geometryFilter->SetInputData(this->activeGrid);
    this->finalSourceAlgorithm = this->geometryFilter->GetOutputPort();

    //define final poly data
    this->geometryFilter->Update();
    this->finalPolyData = this->geometryFilter->GetOutput();

    //set object data
    this->objectType = 2;
    this->cellAmount = 1;
    this->minActiveCell = 1;
    this->maxActiveCell = 1;

    //make object measurements
    this->makeMeasurements();
}

//function to display sphere using VTK source
void VTKObjectHandler::displaySphere()
{
    this->refresh();

    //define VTk source
    vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();

    //set parameters
    sphere->SetPhiResolution(21);
    sphere->SetThetaResolution(21);
    sphere->Update();

    this->objectType = 0;

    //define final algorithm
    this->geometryFilter->SetInputConnection(sphere->GetOutputPort());
    this->finalSourceAlgorithm = this->geometryFilter->GetOutputPort();

    //define final polydata
    this->finalPolyData = sphere->GetOutput();

    //set object data
    this->cellAmount = 1;
    this->minActiveCell = 1;
    this->maxActiveCell = 1;

    //make measurements
    this->makeMeasurements();
}
//function to display hexahedron using VTk source
void VTKObjectHandler::displayDisk()
{

    this->refresh();

    //define VTk source
    vtkSmartPointer<vtkDiskSource> disk = vtkSmartPointer<vtkDiskSource>::New();

    //set parameters
    disk->SetCircumferentialResolution(51);
    disk->Update();

    this->objectType = 0;

    //define final algorithm
    this->geometryFilter->SetInputConnection(disk->GetOutputPort());
    this->finalSourceAlgorithm = this->geometryFilter->GetOutputPort();

    //define final polydata
    this->finalPolyData = disk->GetOutput();

    //set object data
    this->cellAmount = 1;
    this->minActiveCell = 1;
    this->maxActiveCell = 1;

    //make measurements
    this->makeMeasurements();
}

//function to display hexahedron using VTk source
void VTKObjectHandler::displayCone()
{

    this->refresh();

    //define VTk source
    vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();

    //set parameters
    cone->SetResolution(51);
    cone->Update();

    this->objectType = 0;

    //define final algorithm
    this->geometryFilter->SetInputConnection(cone->GetOutputPort());
    this->finalSourceAlgorithm = this->geometryFilter->GetOutputPort();

    //define final polydata
    this->finalPolyData = cone->GetOutput();

    //set object data
    this->cellAmount = 1;
    this->minActiveCell = 1;
    this->maxActiveCell = 1;

    //make measurements
    this->makeMeasurements();
}

//function to display hexahedron using VTk source
void VTKObjectHandler::displayPlane()
{
    this->refresh();

    //define VTk source
    vtkSmartPointer<vtkPlaneSource> plane = vtkSmartPointer<vtkPlaneSource>::New();

    //set parameters
    plane->Update();

    this->objectType = 0;

    //define final algorithm
    this->geometryFilter->SetInputConnection(plane->GetOutputPort());
    this->finalSourceAlgorithm = this->geometryFilter->GetOutputPort();

    //define final polydata
    this->finalPolyData = plane->GetOutput();

    //set object data
    this->cellAmount = 1;
    this->minActiveCell = 1;
    this->maxActiveCell = 1;

    //make measurements
    this->makeMeasurements();
}

//function to display hexahedron using VTk source
void VTKObjectHandler::displayPointCluster(int numberOfPoints)
{

    this->refresh();

    //define VTk source
    vtkSmartPointer<vtkPointSource> cluster = vtkSmartPointer<vtkPointSource>::New();

    //set parameters
    cluster->SetNumberOfPoints(numberOfPoints);
    cluster->Update();

    this->objectType = 0;

    //define final algorithm
    this->geometryFilter->SetInputConnection(cluster->GetOutputPort());
    this->finalSourceAlgorithm = this->geometryFilter->GetOutputPort();

    //define final polydata
    this->finalPolyData = cluster->GetOutput();

    //set object data
    this->cellAmount = 1;
    this->minActiveCell = 1;
    this->maxActiveCell = 1;

    //make measurements
    this->makeMeasurements();
}

//function to display hexahedron using VTk source
void VTKObjectHandler::displayLine()
{

    this->refresh();

    //define VTk source
    vtkSmartPointer<vtkLineSource> line = vtkSmartPointer<vtkLineSource>::New();

    line->Update();

    this->objectType = 0;

    //define final algorithm
    this->geometryFilter->SetInputConnection(line->GetOutputPort());
    this->finalSourceAlgorithm = this->geometryFilter->GetOutputPort();

    //define final polydata
    this->finalPolyData = line->GetOutput();

    //set object data
    this->cellAmount = 1;
    this->minActiveCell = 1;
    this->maxActiveCell = 1;

    //make measurements
    this->makeMeasurements();
}

//function to display hexahedron using VTk source
void VTKObjectHandler::displayCylinder()
{

    this->refresh();

    //define VTk source
    vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();

    //set parameters
    cylinder->SetResolution(51);
    cylinder->Update();

    this->objectType = 0;

    //define final algorithm
    this->geometryFilter->SetInputConnection(cylinder->GetOutputPort());
    this->finalSourceAlgorithm = this->geometryFilter->GetOutputPort();

    //define final polydata
    this->finalPolyData = cylinder->GetOutput();

    //set object data
    this->cellAmount = 1;
    this->minActiveCell = 1;
    this->maxActiveCell = 1;

    //make measurements
    this->makeMeasurements();
}

//function to display hexahedron using VTk source
void VTKObjectHandler::displayEarth()
{
    this->refresh();

    //define VTk source
    vtkSmartPointer<vtkEarthSource> earth = vtkSmartPointer<vtkEarthSource>::New();

    //set parameters
    earth->OutlineOn();
    earth->Update();

    this->objectType = 0;

    //define final algorithm
    this->geometryFilter->SetInputConnection(earth->GetOutputPort());
    this->finalSourceAlgorithm = this->geometryFilter->GetOutputPort();

    //define final polydata
    this->finalPolyData = earth->GetOutput();

    //set object data
    this->cellAmount = 1;
    this->minActiveCell = 1;
    this->maxActiveCell = 1;

    //make measurements
    this->makeMeasurements();
}

//function to load object from file
void VTKObjectHandler::getModelFromFile(QString fileName)
{

    QFileInfo fi(fileName);
    if(fi.suffix()=="stl")
    {
        //loading object from STl file
        this->refresh();

        this->activeReader->SetFileName(fileName.toLatin1().data());
        this->activeReader->Update();
        this->objectType = 1;

        this->objectParameters->SetInputConnection(this->activeReader->GetOutputPort());

        this->finalSourceAlgorithm = this->activeReader->GetOutputPort();
        this->finalPolyData = this->activeReader->GetOutput();

        this->cellAmount = 1;
        this->shownPoints = this->finalPolyData->GetPoints()->GetNumberOfPoints();

        this->makeMeasurements();

        this->minActiveCell = 1;
        this->maxActiveCell = 1;
    }
    else if(fi.suffix()=="mod")
    {
        //loading object from MOD file
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

        this->geometryFilter->SetInputData(this->activeGrid);
        this->finalSourceAlgorithm = this->geometryFilter->GetOutputPort();
        this->finalPolyData = this->geometryFilter->GetOutput();

        this->cellAmount = this->activeVTKModel.getCellAmount();
        this->shownPoints = this->finalPolyData->GetPoints()->GetNumberOfPoints();

        this->makeMeasurements();

        this->minActiveCell = 1;
        this->maxActiveCell = this->cellAmount;
    }
}

//function to save object to file
void VTKObjectHandler::saveModelToFile(QString fileName)
{
    QFileInfo fi(fileName);

    if(fi.suffix()=="stl")
    {
        //save object as STL file
        vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
        stlWriter->SetFileName(fileName.toLocal8Bit().data());
        stlWriter->SetInputConnection(this->finalSourceAlgorithm);
        stlWriter->Write();
    }
    else if(fi.suffix()=="mod")
    {
        //save object as MOD file
        Model savingVTKModel;

        std::vector<Vector3D> tempVectors;
        std::vector<Material> tempMaterials;
        std::vector<Cell> tempCells;

        if(this->objectType==3)
        {
            //saving MOD object as MOD
            tempMaterials.push_back(this->activeVTKModel.getMaterial(this->activeVTKModel.getCell(minActiveCell-1).getMaterialID()));

            if(!(this->separateCellColors[minActiveCell-1][0]==tempMaterials[0].getColor().getx()&&
                    this->separateCellColors[minActiveCell-1][1]==tempMaterials[0].getColor().gety()&&
                    this->separateCellColors[minActiveCell-1][2]==tempMaterials[0].getColor().getz()))
            {
                tempMaterials[0].setColor(Vector3D(this->separateCellColors[minActiveCell-1][0],
                                                   this->separateCellColors[minActiveCell-1][1],
                                                   this->separateCellColors[minActiveCell-1][2]));
            }

            //save model cells
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

                    if(!materialExists)
                    {
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
                        for(int v = 0; v<tempVectors.size(); v++)
                        {
                            if(theVector.getx()==tempVectors[v].getx()&&
                                    theVector.gety()==tempVectors[v].gety()&&
                                    theVector.getz()==tempVectors[v].getz())
                            {
                                vecExists = 1;
                                vectorPosition = v;
                                v = tempVectors.size();
                            }
                        }

                        if(!vecExists)
                        {
                            indices.push_back(tempVectors.size());
                            theVector.setID(tempVectors.size());
                            tempVectors.push_back(theVector);
                        }
                        else
                        {
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
                tempVectors[i].setID(i);
            }

            this->activeCells->InitTraversal();

            for(int i = 0; i<this->activeCells->GetNumberOfCells(); i++)
            {
                int type = 0;

                vtkSmartPointer<vtkIdList> idList = vtkSmartPointer<vtkIdList>::New();
                this->activeCells->GetNextCell(idList);
                if(idList->GetNumberOfIds()==8)
                {
                    type = 1;
                }
                else if(idList->GetNumberOfIds()==5)
                {
                    type = 2;
                }
                else if(idList->GetNumberOfIds()==4)
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
        else{
            std::cout<<"Cant save as MOD file"<<std::endl;
        }
        savingVTKModel.setVectors(tempVectors);
        savingVTKModel.setCells(tempCells);
        savingVTKModel.setMaterials(tempMaterials);
        savingVTKModel.loadInfoToFile(fileName.toLocal8Bit().data());
    }
}

//function to change object color
void VTKObjectHandler::changeColor(QColor color)
{
    //check if it is MOD object
    if(this->objectType==3)
    {
        //change color of shown cells
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
        //change main color
        this->activeColor = color;

    }
}


//function to reset object color
void VTKObjectHandler::resetColor()
{
    //check if it is MOD object
    if(this->objectType==3)
    {
        //reset color of every cell of MOD object
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
        //reset main color
        this->activeColor.setRed(255);
        this->activeColor.setGreen(0);
        this->activeColor.setBlue(0);
    }
}
