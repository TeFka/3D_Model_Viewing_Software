// mainwindow.cpp-----------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::refreshRender()
{
    this->activeRenderWindow->Render();
}

// remove allProps form Actor class
void MainWindow::refreshGrid()
{
    this->activeRenderer->RemoveAllViewProps();
    this->cells->Reset();
    this->cells->Squeeze();
}

void MainWindow::refreshGUI()
{

    this->allowGUIChange = 0;

    ui->cellMinShow->setRange(1, 1);
    ui->cellMaxShow->setRange(1, 1);
    ui->cellMinShow->setValue(1);
    ui->cellMaxShow->setValue(1);
    ui->shrinkCheck->setCheckState(Qt::Unchecked);
    ui->clipCheck->setCheckState(Qt::Unchecked);
    ui->check1->setCheckState(Qt::Unchecked);
    ui->check2->setCheckState(Qt::Unchecked);
    ui->check3->setCheckState(Qt::Unchecked);
    ui->solidRadioB->toggle();

    this->allowGUIChange = 1;

}

void MainWindow::updateObject()
{
    vtkPolyData* polydata;
    if(this->objectType>=2)
    {
        if(this->objectType==3)
        {
            this->updateVTKModel();
        }
        this->geometryFilter->SetInputData(this->activeGrid);
        this->mapperStage(this->geometryFilter->GetOutputPort());
    }
    else
    {
        if (this->objectType == 1)
        {
            this->mapperStage(this->activeReader->GetOutputPort());
            polydata = this->activeReader->GetOutput();
        }
    }


    if(ui->pointsRadioB->isChecked())
    {
        this->activeActor->GetProperty()->SetRepresentationToPoints();
    }
    else if(ui->wireRadioB->isChecked())
    {
        this->activeActor->GetProperty()->SetRepresentationToWireframe();
    }
    else
    {
        this->activeActor->GetProperty()->SetRepresentationToSurface();
    }

    this->updateViewer();
    this->refreshRender();
}

void MainWindow::updateText()
{
    if(ui->showInfo->isChecked())
    {
        vtkSmartPointer<vtkTextActor> tempVolumeTextActor = vtkSmartPointer<vtkTextActor>::New();
        if(objectType==0||objectType==2)
        {
            tempVolumeTextActor->SetInput ("Volume: N/A");
        }
        else
        {
            if(this->objectVolume<0.00001)
            {
                tempVolumeTextActor->SetInput (("Volume: "+std::to_string(this->objectVolume*1000000)+"cm3").data());
            }
            else
            {
                tempVolumeTextActor->SetInput (("Volume: "+std::to_string(this->objectVolume)+"m3").data());
            }
        }
        tempVolumeTextActor->SetPosition ( 10, 70 );
        tempVolumeTextActor->GetTextProperty()->SetFontSize ( 15 );
        tempVolumeTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
        this->activeRenderer->AddActor2D ( tempVolumeTextActor );

        vtkSmartPointer<vtkTextActor> tempMaxCellNumTextActor = vtkSmartPointer<vtkTextActor>::New();

        int cellsNum = 0;
        if(this->objectType<=2)
        {
            cellsNum = 1;
        }
        else
        {
            cellsNum = this->activeVTKModel.getCellAmount();
        }
        tempMaxCellNumTextActor->SetInput (("Max Cells: "+std::to_string(cellsNum)).data());
        tempMaxCellNumTextActor->SetPosition ( 10, 50 );
        tempMaxCellNumTextActor->GetTextProperty()->SetFontSize ( 15 );
        tempMaxCellNumTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
        this->activeRenderer->AddActor2D ( tempMaxCellNumTextActor );

        vtkSmartPointer<vtkTextActor> tempWeightTextActor = vtkSmartPointer<vtkTextActor>::New();

        if(this->objectType<=2)
        {
            tempWeightTextActor->SetInput ("Weight: N/A");
        }
        else
        {
            if(this->objectWeight<0.001)
            {
                tempWeightTextActor->SetInput (("Weight: "+std::to_string(this->objectWeight*1000)+"g").data());
            }
            else
            {
                tempWeightTextActor->SetInput (("Weight: "+std::to_string(this->objectWeight)+"kg").data());
            }
        }
        tempWeightTextActor->SetPosition ( 10, 30 );
        tempWeightTextActor->GetTextProperty()->SetFontSize ( 15 );
        tempWeightTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
        this->activeRenderer->AddActor2D ( tempWeightTextActor );

        vtkSmartPointer<vtkTextActor> tempPositionTextActor = vtkSmartPointer<vtkTextActor>::New();

        Vector3D objPos;
        if(this->objectType<=2)
        {
            objPos.setx(0.0);
            objPos.sety(0.0);
            objPos.setz(0.0);
        }
        else
        {
            objPos = this->activeVTKModel.getModelCenter();
        }

        tempPositionTextActor->SetInput (("Position: "+std::to_string(objPos.getx())+" "+std::to_string(objPos.gety())+" "+std::to_string(objPos.getz())).data());
        tempPositionTextActor->SetPosition ( 10, 10 );
        tempPositionTextActor->GetTextProperty()->SetFontSize ( 15 );
        tempPositionTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
        this->activeRenderer->AddActor2D ( tempPositionTextActor );
    }
}

void MainWindow::makeMeasurement()
{
    if(objectType==2||objectType==0)
    {
        this->objectDimensions.setx(1.0);
        this->objectDimensions.sety(1.0);
        this->objectDimensions.setz(1.0);

        this->objectPosition.setx(0.0);
        this->objectPosition.setx(0.0);
        this->objectPosition.setx(0.0);
    }
    else if(objectType==1)
    {
        vtkSmartPointer<vtkPoints> STLPoints = this->activeReader->GetOutput()->GetPoints();
        double xMin=0;
        double yMin=0;
        double zMin=0;
        double xMax=0;
        double yMax=0;
        double zMax=0;
        //go through all vectors and check their positions
        for(int i = 0; i<STLPoints->GetNumberOfPoints(); i++)
        {
            double STLpoint[3];
            STLPoints->GetPoint(i,STLpoint);
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
        std::cout<<this->objectDimensions.getx()<<"  "<<this->objectDimensions.gety()<<"  "<<this->objectDimensions.getz()<<std::endl;
    }
    else
    {
        this->objectDimensions.setx(this->activeVTKModel.getModelDimensions().getx());
        this->objectDimensions.sety(this->activeVTKModel.getModelDimensions().gety());
        this->objectDimensions.setz(this->activeVTKModel.getModelDimensions().getz());

        this->objectPosition.setx(this->activeVTKModel.getModelCenter().getx());
        this->objectPosition.setx(this->activeVTKModel.getModelCenter().gety());
        this->objectPosition.setx(this->activeVTKModel.getModelCenter().getz());
    }
}

void MainWindow::updateVTKModel()
{
    if(this->objectType==3)
    {
        this->cells->Reset();
        this->cells->Squeeze();

        vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
        vtkSmartPointer<vtkUnsignedCharArray> cellData = vtkSmartPointer<vtkUnsignedCharArray>::New();

        // init model
        std::vector<Vector3D> vectors = this->activeVTKModel.getVectors();
        for(int i =0; i<vectors.size(); i++)
        {
            points->InsertNextPoint(vectors[i].getx(),vectors[i].gety(),vectors[i].getz());
        }

        tempGrid->SetPoints(points);

        cellData->SetNumberOfComponents(3);

        this->objectVolume = 0.0;
        this->objectWeight = 0.0;
        //set values
        for(int i = 0; i<this->activeVTKModel.getCellAmount(); i++)
        {
            if((i+1)>=ui->cellMinShow->value()&&(i+1)<=ui->cellMaxShow->value())
            {
                Cell tempCell = this->activeVTKModel.getCell(i);
                if(tempCell.getType()==1)
                {
                    this->drawHexahedron(&tempCell,tempGrid);
                }
                if(tempCell.getType()==2)
                {
                    this->drawPyramid(&tempCell,tempGrid);
                }
                if(tempCell.getType()==3)
                {
                    this->drawTetrahedron(&tempCell,tempGrid);
                }

                this->objectVolume += tempCell.getVolume();
                this->objectWeight += tempCell.getWeight();
                float rgb[3];
                if(this->separateCellColors[i][0]==0.0)
                {
                    Vector3D color = this->activeVTKModel.getMaterial(tempCell.getMaterialID()).getColor();
                    rgb[0] = 255*color.getx();
                    rgb[1] = 255*color.gety();
                    rgb[2] = 255*color.getz();
                }
                else
                {
                    rgb[0] = 255*this->separateCellColors[i][1];
                    rgb[1] = 255*this->separateCellColors[i][2];
                    rgb[2] = 255*this->separateCellColors[i][3];
                }
                cellData->InsertNextTuple(rgb);
            }
        }
        tempGrid->GetCellData()->SetScalars(cellData);

        this->objectType = 3;
        this->activeGrid = tempGrid;
    }
}

void MainWindow::updateAxes(double xOffset,double yOffset,double zOffset, int axisExist)
{
    if(ui->showAxis->isChecked())
    {
        if(axisExist)
        {
            this->activeRenderer->RemoveActor(this->axes);
        }
        vtkSmartPointer<vtkTransform> uTransform = vtkSmartPointer<vtkTransform>::New();

        uTransform->Translate(this->objectPosition.getx()+(2*this->objectDimensions.getx()*xOffset),
                              this->objectPosition.gety()+(2*this->objectDimensions.gety()*yOffset),
                              this->objectPosition.getz()+(2*this->objectDimensions.getz()*zOffset));

        this->axes->SetUserTransform(uTransform);

        this->axes->SetTotalLength(this->objectDimensions.getx(),this->objectDimensions.getx(),this->objectDimensions.getx());
        this->activeRenderer->AddActor(this->axes);
    }
}

void MainWindow::updatePoints(vtkSmartPointer<vtkPoints> thePoints)
{
    vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetPhiResolution(21);
    sphere->SetThetaResolution(21);
    double radius = (sqrt(this->objectDimensions.getx()*this->objectDimensions.getx()+this->objectDimensions.gety()*this->objectDimensions.gety()+
                          this->objectDimensions.getz()*this->objectDimensions.getz())/10.0);
    if(radius>0.05)
    {
        radius=0.05;
    }
    sphere->SetRadius(radius);
    // Create a polydata to store everything in
    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(thePoints);

    vtkSmartPointer<vtkGlyph3DMapper> pointMapper = vtkSmartPointer<vtkGlyph3DMapper>::New();
    pointMapper->SetInputData(polyData);
    pointMapper->SetSourceConnection(sphere->GetOutputPort());

    vtkSmartPointer<vtkActor> pointActor = vtkSmartPointer<vtkActor>::New();
    pointActor->SetMapper(pointMapper);
    pointActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    this->activeRenderer->AddActor(pointActor);
}

vtkAlgorithmOutput* MainWindow::filterStage(vtkAlgorithmOutput* firstFilterInput, int firstFilterIndex)
{
    vtkAlgorithmOutput* algorithmOutput = firstFilterInput;

    if(ui->shrinkCheck->isChecked())
    {
        if(firstFilterIndex!=0)
        {
            this->shrinkFilter->SetInputConnection(algorithmOutput);
            this->initFilter(0);
            algorithmOutput = this->shrinkFilter->GetOutputPort();
        }
    }
    if(ui->clipCheck->isChecked())
    {
        if(firstFilterIndex!=1)
        {
            this->clipFilter->SetInputConnection(algorithmOutput);
            this->initFilter(1);
            algorithmOutput = this->clipFilter->GetOutputPort();
        }
    }
    if(ui->contourCheck->isChecked())
    {
        if(firstFilterIndex!=2)
        {
            this->contourFilter->SetInputConnection(algorithmOutput);
            this->initFilter(2);
            algorithmOutput = this->contourFilter->GetOutputPort();
        }
    }
    if(ui->check1->isChecked())
    {
        if(firstFilterIndex!=3)
        {
            this->outlineFilter->SetInputConnection(algorithmOutput);
            this->initFilter(3);
            algorithmOutput = this->outlineFilter->GetOutputPort();
        }
    }
    if(ui->check2->isChecked())
    {
        if(firstFilterIndex!=4)
        {
            this->outlineCornerFilter->SetInputConnection(algorithmOutput);
            this->initFilter(4);
            algorithmOutput = this->outlineCornerFilter->GetOutputPort();
        }
    }
    if(ui->check3->isChecked())
    {
        if(firstFilterIndex!=5)
        {
            this->splineFilter->SetInputConnection(algorithmOutput);
            this->initFilter(5);
            algorithmOutput = this->splineFilter->GetOutputPort();
        }
    }
    return algorithmOutput;
}

void MainWindow::mapperStage(vtkAlgorithmOutput* geometryInput)
{
    if(ui->shrinkCheck->isChecked())
    {
        this->shrinkFilter->SetInputConnection(geometryInput);
        this->initFilter(0);
        this->activeMapper->SetInputConnection(this->filterStage(this->shrinkFilter->GetOutputPort(), 0));
    }
    else if(ui->clipCheck->isChecked())
    {
        this->clipFilter->SetInputConnection(geometryInput);
        this->initFilter(1);
        this->activeMapper->SetInputConnection(this->filterStage(this->clipFilter->GetOutputPort(), 1));
    }
    else if(ui->contourCheck->isChecked())
    {
        this->contourFilter->SetInputConnection(geometryInput);
        this->initFilter(2);
        this->activeMapper->SetInputConnection(this->filterStage(this->contourFilter->GetOutputPort(), 2));
    }
    else if(ui->check1->isChecked())
    {
        this->outlineFilter->SetInputConnection(geometryInput);
        this->initFilter(3);
        this->activeMapper->SetInputConnection(this->filterStage(this->outlineFilter->GetOutputPort(), 3));
    }
    else if(ui->check2->isChecked())
    {
        this->outlineCornerFilter->SetInputConnection(geometryInput);
        this->initFilter(4);
        this->activeMapper->SetInputConnection(this->filterStage(this->outlineCornerFilter->GetOutputPort(), 4));
    }
    else if(ui->check3->isChecked())
    {
        this->splineFilter->SetInputConnection(geometryInput);
        this->initFilter(5);
        this->activeMapper->SetInputConnection(this->filterStage(this->splineFilter->GetOutputPort(), 5));
    }
    else
    {
        this->activeMapper->SetInputConnection(geometryInput);
    }
}


void MainWindow::drawHexahedron(Cell *cell, vtkSmartPointer<vtkUnstructuredGrid> theGrid)
{
    std::vector<int> indx = cell->getIndices();
    vtkSmartPointer<vtkHexahedron> hex = vtkSmartPointer<vtkHexahedron>::New();

    for(auto n = 0; n<8; n++)
    {
        hex->GetPointIds()->SetId(n,indx[n]);
    }

    this->cells->InsertNextCell(hex);
    theGrid->InsertNextCell(hex->GetCellType(), hex->GetPointIds());
}

void MainWindow::drawTetrahedron(Cell *cell, vtkSmartPointer<vtkUnstructuredGrid> theGrid)
{
    std::vector<int> indx = cell->getIndices();
    vtkSmartPointer<vtkTetra> tetr = vtkSmartPointer<vtkTetra>::New();

    for(auto n = 0; n<4; n++)
    {
        tetr->GetPointIds()->SetId(n,indx[n]);
    }

    this->cells->InsertNextCell(tetr);
    theGrid->InsertNextCell(tetr->GetCellType(), tetr->GetPointIds());
}

void MainWindow::drawPyramid(Cell *cell, vtkSmartPointer<vtkUnstructuredGrid> theGrid)
{
    std::vector<int> indx = cell->getIndices();
    vtkSmartPointer<vtkPyramid> pyr = vtkSmartPointer<vtkPyramid>::New();

    for(auto n = 0; n<5; n++)
    {
        pyr->GetPointIds()->SetId(n,indx[n]);
    }

    this->cells->InsertNextCell(pyr);
    theGrid->InsertNextCell(pyr->GetCellType(), pyr->GetPointIds());
}

void MainWindow::displayHexahedron()
{
    this->refreshGUI();
    this->refreshGrid();
    vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    this->activeActor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    this->cells->Reset();
    this->cells->Squeeze();
    //draw
    points->InsertNextPoint(0.0, 0.0, 0.0); // Face 1
    points->InsertNextPoint(1.0, 0.0, 0.0);
    points->InsertNextPoint(1.0, 1.0, 0.0);
    points->InsertNextPoint(0.0, 1.0, 0.0);
    points->InsertNextPoint(0.0, 0.0, 1.0); // Face 2
    points->InsertNextPoint(1.0, 0.0, 1.0);
    points->InsertNextPoint(1.0, 1.0, 1.0);
    points->InsertNextPoint(0.0, 1.0, 1.0);

    // Create a hexahedron from the points.
    vtkSmartPointer<vtkHexahedron> hex = vtkSmartPointer<vtkHexahedron>::New();

    for (auto i = 0; i < 8; ++i)
    {
        hex->GetPointIds()->SetId(i, i);
    }

    this->cells->InsertNextCell(hex);
    tempGrid->SetPoints(points);
    tempGrid->InsertNextCell(hex->GetCellType(), hex->GetPointIds());

    this->objectType = 2;

    this->geometryFilter->SetInputData(tempGrid);
    this->mapperStage(this->geometryFilter->GetOutputPort());

    this->activeActor->SetMapper(this->activeMapper);
    this->activeActor->GetProperty()->EdgeVisibilityOn();

    this->activeActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    this->activeActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(this->activeActor);

    this->updateViewer();

    this->activeGrid = tempGrid;

    this->resetCamera();
    this->refreshRender();
}

void MainWindow::updateViewer()
{
    this->makeMeasurement();
    this->updateText();
    this->updateAxes();
}

void MainWindow::displayTetrahedron()
{
    this->refreshGUI();
    this->refreshGrid();
    vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    this->activeActor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    this->cells->Reset();
    this->cells->Squeeze();

    //draw
    points->InsertNextPoint(0.0, 0.0, 0.0); // Face 1
    points->InsertNextPoint(1.0, 0.0, 0.0);
    points->InsertNextPoint(1.0, 1.0, 0.0);
    points->InsertNextPoint(0.0, 1.0, 1.0);

    // Create a hexahedron from the points.
    vtkSmartPointer<vtkTetra> tetr = vtkSmartPointer<vtkTetra>::New();

    for (auto i = 0; i < 4; ++i)
    {
        tetr->GetPointIds()->SetId(i, i);
    }
    this->cells->InsertNextCell(tetr);
    tempGrid->SetPoints(points);
    tempGrid->InsertNextCell(tetr->GetCellType(), tetr->GetPointIds());

    this->objectType = 2;

    this->geometryFilter->SetInputData(tempGrid);
    this->mapperStage(this->geometryFilter->GetOutputPort());

    this->activeActor->SetMapper(this->activeMapper);
    this->activeActor->GetProperty()->EdgeVisibilityOn();

    this->activeActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    this->activeActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(this->activeActor);

    this->activeGrid = tempGrid;

    this->resetCamera();
    this->refreshRender();
}

void MainWindow::displayPyramid()
{
    this->refreshGUI();
    this->refreshGrid();
    vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    this->activeActor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    this->cells->Reset();
    this->cells->Squeeze();
    //draw
    points->InsertNextPoint(1.0, 1.0, 1.0); // Face 1
    points->InsertNextPoint(-1.0, 1.0, 1.0);
    points->InsertNextPoint(-1.0, -1.0, 1.0);
    points->InsertNextPoint(1.0, -1.0, 1.0);
    points->InsertNextPoint(0.0, 0.0, 0.0); // Face 2

    // Create a hexahedron from the points.
    vtkSmartPointer<vtkPyramid> pyr = vtkSmartPointer<vtkPyramid>::New();

    for (auto i = 0; i < 5; ++i)
    {
        pyr->GetPointIds()->SetId(i, i);
    }
    this->cells->InsertNextCell(pyr);
    tempGrid->SetPoints(points);
    tempGrid->InsertNextCell(pyr->GetCellType(), pyr->GetPointIds());

    this->objectType = 2;

    this->geometryFilter->SetInputData(tempGrid);
    this->mapperStage(this->geometryFilter->GetOutputPort());

    this->activeActor->SetMapper(this->activeMapper);
    this->activeActor->GetProperty()->EdgeVisibilityOn();

    this->activeActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    this->activeActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(this->activeActor);

    this->activeGrid = tempGrid;

    this->resetCamera();
    this->refreshRender();
}

void MainWindow::displaySphere()
{
    this->refreshGUI();
    this->refreshGrid();
    vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
    this->activeActor = vtkSmartPointer<vtkActor>::New();

    sphere->SetPhiResolution(21);
    sphere->SetThetaResolution(21);

    this->objectType = 0;

    this->mapperStage(sphere->GetOutputPort());

    this->activeActor->SetMapper(this->activeMapper);
    this->activeActor->GetProperty()->EdgeVisibilityOn();

    this->activeActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    this->activeActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(this->activeActor);

    this->resetCamera();
    this->refreshRender();
}
void MainWindow::displayDisk()
{
    this->refreshGUI();
    this->refreshGrid();
    vtkSmartPointer<vtkDiskSource> disk = vtkSmartPointer<vtkDiskSource>::New();
    this->activeActor = vtkSmartPointer<vtkActor>::New();

    disk->SetCircumferentialResolution(51);

    this->objectType = 0;

    this->mapperStage(disk->GetOutputPort());

    this->activeActor->SetMapper(this->activeMapper);
    this->activeActor->GetProperty()->EdgeVisibilityOn();

    this->activeActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    this->activeActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(this->activeActor);

    this->resetCamera();
    this->refreshRender();
}
void MainWindow::displayCone()
{
    this->refreshGUI();
    this->refreshGrid();
    vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
    this->activeActor = vtkSmartPointer<vtkActor>::New();

    cone->SetResolution(51);

    this->objectType = 0;

    this->mapperStage(cone->GetOutputPort());

    this->activeActor->SetMapper(this->activeMapper);
    this->activeActor->GetProperty()->EdgeVisibilityOn();

    this->activeActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    this->activeActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(this->activeActor);

    this->resetCamera();
    this->refreshRender();
}
void MainWindow::displayPlane()
{
    this->refreshGUI();
    this->refreshGrid();
    vtkSmartPointer<vtkPlaneSource> plane = vtkSmartPointer<vtkPlaneSource>::New();
    this->activeActor = vtkSmartPointer<vtkActor>::New();

    this->objectType = 0;

    this->mapperStage(plane->GetOutputPort());

    this->activeActor->SetMapper(this->activeMapper);
    this->activeActor->GetProperty()->EdgeVisibilityOn();

    this->activeActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    this->activeActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(this->activeActor);

    this->resetCamera();
    this->refreshRender();
}
void MainWindow::displayPointCluster(int numberOfPoints)
{
    this->refreshGUI();
    this->refreshGrid();
    vtkSmartPointer<vtkPointSource> cluster = vtkSmartPointer<vtkPointSource>::New();
    this->activeActor = vtkSmartPointer<vtkActor>::New();

    cluster->SetNumberOfPoints(numberOfPoints);

    this->objectType = 0;

    this->mapperStage(cluster->GetOutputPort());

    this->activeActor->SetMapper(this->activeMapper);
    this->activeActor->GetProperty()->EdgeVisibilityOn();

    this->activeActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    this->activeActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(this->activeActor);

    this->resetCamera();
    this->refreshRender();
}
void MainWindow::displayLine()
{
    this->refreshGUI();
    this->refreshGrid();
    vtkSmartPointer<vtkLineSource> line = vtkSmartPointer<vtkLineSource>::New();
    this->activeActor = vtkSmartPointer<vtkActor>::New();

    this->objectType = 0;

    this->mapperStage(line->GetOutputPort());

    this->activeActor->SetMapper(this->activeMapper);
    this->activeActor->GetProperty()->EdgeVisibilityOn();

    this->activeActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    this->activeActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(this->activeActor);

    this->resetCamera();
    this->refreshRender();
}

void MainWindow::displayCylinder()
{
    this->refreshGUI();
    this->refreshGrid();
    vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    this->activeActor = vtkSmartPointer<vtkActor>::New();

    cylinder->SetResolution(51);

    this->objectType = 0;

    this->mapperStage(cylinder->GetOutputPort());

    this->activeActor->SetMapper(this->activeMapper);
    this->activeActor->GetProperty()->EdgeVisibilityOn();

    this->activeActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    this->activeActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(this->activeActor);

    this->resetCamera();
    this->refreshRender();
}

//Function of class Mainwindow, handleOpenButton()
//Function to get specified model file
// Arguments for handleOpenButton(): none(file chosen using getSaveFileName() function)
// return value: none (file is opened)
void MainWindow::handleOpenButton()
{
    this->refreshGUI();
    this->activeFileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "./", tr("STL Files(*.stl *.mod)"));
    QFileInfo fi(this->activeFileName);
    emit statusUpdateMessage( QString("Loaded: ")+fi.suffix(), 0 );
    if(fi.suffix()=="stl")
    {
        this->refreshGrid();
        this->activeActor = vtkSmartPointer<vtkActor>::New();

        this->activeReader->SetFileName(this->activeFileName.toLatin1().data());
        this->activeReader->Update();
        this->objectType = 1;

        this->objectParameters->SetInputConnection(this->activeReader->GetOutputPort());

        this->objectVolume = this->objectParameters->GetVolume();

        this->mapperStage(this->activeReader->GetOutputPort());

        this->activeActor->SetMapper(this->activeMapper);
        this->activeActor->GetProperty()->EdgeVisibilityOn();

        this->activeActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
        this->activeActor->GetProperty()->LightingOff();

        this->activeRenderer->AddActor(this->activeActor);

        this->updateViewer();

        ui->cellMinShow->setRange(1, 1);
        ui->cellMaxShow->setRange(1, 1);
        ui->cellMinShow->setValue(1);
        ui->cellMaxShow->setValue(1);

    }
    else if(fi.suffix()=="mod")
    {
        this->refreshGrid();
        this->separateCellColors.clear();

        vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
        this->activeActor = vtkSmartPointer<vtkActor>::New();

        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
        vtkSmartPointer<vtkUnsignedCharArray> cellData = vtkSmartPointer<vtkUnsignedCharArray>::New();
        this->cells->Reset();
        this->cells->Squeeze();

        // init model
        this->activeVTKModel.loadModel(this->activeFileName.toStdString().c_str());

        std::vector<Vector3D> vectors = this->activeVTKModel.getVectors();
        for(int i =0; i<vectors.size(); i++)
        {
            points->InsertNextPoint(vectors[i].getx(),vectors[i].gety(),vectors[i].getz());
        }

        tempGrid->SetPoints(points);

        cellData->SetNumberOfComponents(3);

        this->objectVolume = 0.0;
        this->objectWeight = 0.0;
        //set values
        for(int i = 0; i<this->activeVTKModel.getCellAmount(); i++)
        {
            Cell tempCell = this->activeVTKModel.getCell(i);
            if(tempCell.getType()==1)
            {
                this->drawHexahedron(&tempCell,tempGrid);
            }
            if(tempCell.getType()==2)
            {
                this->drawPyramid(&tempCell,tempGrid);
            }
            if(tempCell.getType()==3)
            {
                this->drawTetrahedron(&tempCell,tempGrid);
            }

            Vector3D color = this->activeVTKModel.getMaterial(tempCell.getMaterialID()).getColor();
            this->separateCellColors.push_back({0.0,0.0,0.0,0.0});

            float rgb[3];
            rgb[0] = 255*color.getx();
            rgb[1] = 255*color.gety();
            rgb[2] = 255*color.getz();
            cellData->InsertNextTuple(rgb);

            this->objectVolume += tempCell.getVolume();
            this->objectWeight += tempCell.getWeight();
        }

        tempGrid->GetCellData()->SetScalars(cellData);

        this->allowGUIChange = 0;
        ui->cellMinShow->setRange(1, this->activeVTKModel.getCellAmount());
        ui->cellMaxShow->setRange(1, this->activeVTKModel.getCellAmount());
        ui->cellMinShow->setValue(1);
        ui->cellMaxShow->setValue(this->activeVTKModel.getCellAmount());
        this->allowGUIChange = 1;

        this->objectType = 3;

        this->geometryFilter->SetInputData(tempGrid);
        this->mapperStage(this->geometryFilter->GetOutputPort());

        this->activeActor->SetMapper(this->activeMapper);
        this->activeActor->GetProperty()->EdgeVisibilityOn();

        this->activeActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
        this->activeActor->GetProperty()->LightingOff();

        this->activeRenderer->AddActor(this->activeActor);

        this->activeGrid = tempGrid;

        this->updateViewer();
    }
    this->resetCamera();
    this->refreshRender();
}

void MainWindow::handleSaveButton()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save model (*.stl *.mod)"),"/theFile");

    QFileInfo fi(fileName);

    if(fi.suffix()=="stl")
    {
        vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
        stlWriter->SetFileName(fileName.toLocal8Bit().data());
        stlWriter->SetInputConnection(this->activeReader->GetOutputPort());
        stlWriter->Write();
    }
    else if(fi.suffix()=="mod")
    {
        Model savingVTKModel;

    }
}

void MainWindow::resetViewer()
{

    this->activeColor.setRed(255);
    this->activeColor.setGreen(0);
    this->activeColor.setBlue(0);

    this->displayHexahedron();

    this->updateViewer();

    this->activeRenderer->SetBackground( this->activeColors->GetColor3d("Silver").GetData() );
    this->activeRenderer->GetActiveCamera()->Azimuth(30);
    this->activeRenderer->GetActiveCamera()->Elevation(30);

    this->resetCamera();
    this->refreshRender();
}

void MainWindow::resetCamera()
{
    this->activeRenderer->ResetCamera();
    this->activeRenderer->GetActiveCamera()->Azimuth(30);
    this->activeRenderer->GetActiveCamera()->Elevation(30);
    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

void MainWindow::setCameraOrientationPosX()
{
    this->activeRenderer->GetActiveCamera()->SetPosition(this->objectPosition.getx()+3*this->objectDimensions.getx(),
            this->objectPosition.gety(),
            this->objectPosition.getz());
    this->activeRenderer->GetActiveCamera()->SetFocalPoint(this->objectPosition.getx(),this->objectPosition.gety(),this->objectPosition.getz());
    this->activeRenderer->GetActiveCamera()->SetViewUp(this->objectPosition.getx(),this->objectPosition.gety(),this->objectPosition.getz());
    this->updateAxes(0.0,0.0,-1.0,1);

    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}
void MainWindow::setCameraOrientationNegX()
{
    this->activeRenderer->ResetCamera();
    this->activeRenderer->ResetCameraClippingRange();
    this->activeRenderer->GetActiveCamera()->SetPosition(this->objectPosition.getx()-3*this->objectDimensions.getx(),
            this->objectPosition.gety(),
            this->objectPosition.getz());
    this->activeRenderer->GetActiveCamera()->SetFocalPoint(this->objectPosition.getx(),this->objectPosition.gety(),this->objectPosition.getz());
    this->activeRenderer->GetActiveCamera()->SetViewUp(this->objectPosition.getx(),this->objectPosition.gety(),this->objectPosition.getz());
    this->updateAxes(0.0,0.0,1.0,1);

    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}
void MainWindow::setCameraOrientationPosY()
{
    this->activeRenderer->ResetCamera();
    this->activeRenderer->GetActiveCamera()->SetPosition(this->objectPosition.getx(),
            this->objectPosition.gety()+3*this->objectDimensions.gety(),
            this->objectPosition.getz());
    this->activeRenderer->GetActiveCamera()->SetFocalPoint(this->objectPosition.getx(),this->objectPosition.gety(),this->objectPosition.getz());
    this->activeRenderer->GetActiveCamera()->SetViewUp(1.0,this->objectPosition.gety(),this->objectPosition.getz());

    this->updateAxes(1.0,0.0,-1.0,1);

    //this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

void MainWindow::setCameraOrientationNegY()
{
    this->activeRenderer->ResetCamera();
    this->activeRenderer->GetActiveCamera()->SetPosition(this->objectPosition.getx(),
            this->objectPosition.gety()-3*this->objectDimensions.gety(),
            this->objectPosition.getz());
    this->activeRenderer->GetActiveCamera()->SetFocalPoint(this->objectPosition.getx(),this->objectPosition.gety(),this->objectPosition.getz());
    this->activeRenderer->GetActiveCamera()->SetViewUp(1.0,this->objectPosition.gety(),this->objectPosition.getz());

    this->updateAxes(-1.0,0.0,0.0,1);

    //this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}
void MainWindow::setCameraOrientationPosZ()
{
    this->activeRenderer->ResetCamera();
    this->activeRenderer->GetActiveCamera()->SetPosition(this->objectPosition.getx(),
            this->objectPosition.gety(),
            this->objectPosition.getz()+3*this->objectDimensions.getz());
    this->activeRenderer->GetActiveCamera()->SetFocalPoint(this->objectPosition.getx(),this->objectPosition.gety(),this->objectPosition.getz());
    this->activeRenderer->GetActiveCamera()->SetViewUp(this->objectPosition.getx(),this->objectPosition.gety(),this->objectPosition.getz());
    this->updateAxes(1.0,0.0,1.0,1);

    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}
void MainWindow::setCameraOrientationNegZ()
{
    this->activeRenderer->ResetCamera();
    this->activeRenderer->GetActiveCamera()->SetPosition(this->objectPosition.getx(),
            this->objectPosition.gety(),
            this->objectPosition.getz()-3*this->objectDimensions.getz());
    this->activeRenderer->GetActiveCamera()->SetFocalPoint(this->objectPosition.getx(),this->objectPosition.gety(),this->objectPosition.getz());
    this->activeRenderer->GetActiveCamera()->SetViewUp(this->objectPosition.getx(),this->objectPosition.gety(),this->objectPosition.getz());
    this->updateAxes(-1.0,0.0,0.0,1);

    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

void MainWindow::setCameraOrientationPosShift()
{
    this->activeRenderer->GetActiveCamera()->Azimuth(90);
    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

void MainWindow::setCameraOrientationNegShift()
{
    this->activeRenderer->GetActiveCamera()->Azimuth(-90);
    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

void MainWindow::setCameraOrientationPosRotate()
{
    this->activeRenderer->GetActiveCamera()->Roll(-90.0);
    this->refreshRender();
}

void MainWindow::setCameraOrientationNegRotate()
{
    this->activeRenderer->GetActiveCamera()->Roll(90.0);
    this->refreshRender();
}

void MainWindow::changeBackgroundColor()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Pick a color",  QColorDialog::DontUseNativeDialog);
    this->activeRenderer->SetBackground((double)color.red()/255,(double)color.green()/255,(double)color.blue()/255);
    this->refreshRender();
}

void MainWindow::changeObjectColor()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Pick a color",  QColorDialog::DontUseNativeDialog);

    if(this->objectType>2)
    {
        for(int i = 0; i<this->activeVTKModel.getCellAmount(); i++)
        {
            if((i+1)>=ui->cellMinShow->value()&&(i+1)<=ui->cellMaxShow->value())
            {
                this->separateCellColors[i][0] = 1.0;
                this->separateCellColors[i][1] = (double)color.red()/255;
                this->separateCellColors[i][2] = (double)color.green()/255;
                this->separateCellColors[i][3] = (double)color.blue()/255;
            }
        }
    }
    else
    {
        this->activeColor = color;

    }
    this->updateObject();
    this->refreshRender();
}

void MainWindow::resetObjectColor()
{
    if(this->objectType<3)
    {
        this->activeColor.setRed(255);
        this->activeColor.setGreen(0);
        this->activeColor.setBlue(0);
    }
    else
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
    this->updateObject();
    this->refreshRender();
}

void MainWindow::initFilter(int index)
{
    switch(index)
    {
    case 0:
    {
        this->shrinkFilter->SetShrinkFactor(ui->shrinkFactor->value());
        this->shrinkFilter->Update();
        break;
    }
    case 1:
    {
        vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New();
        double originX = ((float)ui->clipX->isChecked())*(this->objectPosition.getx()+(this->objectDimensions.getx()*(this->clipOriginPart)));
        double originY = ((float)ui->clipY->isChecked())*(this->objectPosition.gety()+(this->objectDimensions.gety()*(this->clipOriginPart)));
        double originZ = ((float)ui->clipZ->isChecked())*(this->objectPosition.getz()+(this->objectDimensions.getz()*(this->clipOriginPart)));
        planeLeft->SetOrigin(originX, originY, originZ);
        planeLeft->SetNormal((float)ui->clipX->isChecked(), (float)ui->clipY->isChecked(), (float)ui->clipZ->isChecked());
        this->clipFilter->SetClipFunction( planeLeft.Get() );
        break;
    }
    case 2:
    {
        contourFilter->SetValue(0, 0.0);
        break;
    }
    case 3:
    {
        break;
    }
    case 4:
    {
        break;
    }
    case 5:
    {
        break;
    }
    }
}

void MainWindow::handleUpdate()
{
    if(this->allowGUIChange)
    {
        this->updateObject();
        this->refreshRender();
    }
}

void MainWindow::changeClipValue(int newVal)
{
    this->clipOriginPart = ((double)newVal/100);
    this->updateObject();
    this->refreshRender();
}

void MainWindow::handleHelpButton()
{
    AppHelp helpWindow;
    helpWindow.runHelp();
}

void MainWindow::handleNewButton()
{
    int chosenShape = 0;
    NewShapeChoice choiceWindow;
    choiceWindow.runChoice(chosenShape);
    switch(chosenShape)
    {
    case 1:
    {
        this->displayHexahedron();
        break;
    }
    case 2:
    {
        this->displayTetrahedron();
        break;
    }
    case 3:
    {
        this->displayPyramid();
        break;
    }
    case 4:
    {
        this->displaySphere();
        break;
    }
    case 5:
    {
        this->displayDisk();
        break;
    }
    case 6:
    {
        this->displayCone();
        break;
    }
    case 7:
    {
        this->displayPlane();
        break;
    }
    case 8:
    {
        this->displayPointCluster(500);
        break;
    }
    case 9:
    {
        this->displayLine();
        break;
    }
    case 10:
    {
        this->displayCylinder();
        break;
    }
    }

}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

// standard call to setup Qt UI (same as previously)
    ui->setupUi( this );

//Create connection to open action
    connect( ui->actionOpen, &QAction::triggered, this, &MainWindow::handleOpenButton);
    connect( ui->actionHelp, &QAction::triggered, this, &MainWindow::handleHelpButton);
    connect( ui->actionNew, &QAction::triggered, this, &MainWindow::handleNewButton);
    connect( ui->resetObject, &QPushButton::released, this, &MainWindow::resetViewer );
    connect( ui->resetCamera, &QPushButton::released, this, &MainWindow::resetCamera );
    connect( ui->backgroundColor, &QPushButton::released, this, &MainWindow::changeBackgroundColor );
    connect( ui->objectColor, &QPushButton::released, this, &MainWindow::changeObjectColor );
    connect( ui->resetObjColor, &QPushButton::released, this, &MainWindow::resetObjectColor );

    //camera
    connect( ui->orientationXPos, &QPushButton::released, this, MainWindow:: setCameraOrientationPosX);
    connect( ui->orientationXNeg, &QPushButton::released, this, &MainWindow::setCameraOrientationNegX );
    connect( ui->orientationYPos, &QPushButton::released, this, MainWindow:: setCameraOrientationPosY);
    connect( ui->orientationYNeg, &QPushButton::released, this, &MainWindow::setCameraOrientationNegY);
    connect( ui->orientationZPos, &QPushButton::released, this, MainWindow:: setCameraOrientationPosZ);
    connect( ui->orientationZNeg, &QPushButton::released, this, &MainWindow::setCameraOrientationNegZ );
    connect( ui->shift90Pos, &QPushButton::released, this, MainWindow:: setCameraOrientationPosShift);
    connect( ui->shift90Neg, &QPushButton::released, this, &MainWindow::setCameraOrientationNegShift );
    connect( ui->rotat90Pos, &QPushButton::released, this, MainWindow:: setCameraOrientationPosRotate);
    connect( ui->rotat90Neg, &QPushButton::released, this, &MainWindow::setCameraOrientationNegRotate );

//Create connection to message bar
    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage );

//slider control
    connect(ui->clipSlider, SIGNAL(valueChanged(int)), this, SLOT(changeClipValue(int)));

//check boxes
    connect(ui->shrinkCheck, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->clipCheck, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->contourCheck, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));

    connect(ui->clipX, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->clipY, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->clipZ, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));

    connect(ui->showInfo, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->showAxis, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));

//spin boxes
    connect(ui->shrinkFactor, SIGNAL(valueChanged(double)), this, SLOT(handleUpdate()));

    connect(ui->cellMinShow, SIGNAL(valueChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->cellMaxShow, SIGNAL(valueChanged(int)), this, SLOT(handleUpdate()));

//radio buttons
    connect(ui->solidRadioB, SIGNAL(clicked()), this, SLOT(handleUpdate()));
    connect(ui->wireRadioB, SIGNAL(clicked()), this, SLOT(handleUpdate()));
    connect(ui->pointsRadioB, SIGNAL(clicked()), this, SLOT(handleUpdate()));

// creator

    this->activeRenderWindow = ui->qvtkWidget->GetRenderWindow();

    this->activeRenderWindow->AddRenderer( this->activeRenderer );

    this->resetViewer();
}
MainWindow::~MainWindow()
{
    delete ui;
}
// /mainwindow.cpp----------------------------------------------------------
