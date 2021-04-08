// mainwindow.cpp-----------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::refreshRender()
{
    this->activeRenderer->ResetCamera();
    this->activeRenderer->ResetCameraClippingRange();

    this->activeRenderWindow->Render();
}

// remove allProps form Actor class
void MainWindow::refreshGrid()
{
    this->activeRenderer->RemoveAllViewProps();
    this->cells->Reset();
    this->cells->Squeeze();

}

void MainWindow::updateObject()
{
    refreshGrid();
    vtkSmartPointer<vtkActor> tempActor = vtkSmartPointer<vtkActor>::New();
    if(this->objectType>=2)
    {
        tempActor->SetMapper(this->mapperGridStage(this->activeGrid));
    }
    else
    {
        if (this->objectType == 1)
        {
            tempActor->SetMapper(this->mapperStage(this->activeReader->GetOutputPort()));
        }
        if(this->objectType==0)
        {
            vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
            tempActor->SetMapper(this->mapperStage(cubeSource->GetOutputPort()));
        }
    }

    if(this->objectType<=2)
    {
        tempActor->GetProperty()->EdgeVisibilityOn();

        tempActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
        tempActor->GetProperty()->LightingOff();
    }
    this->activeRenderer->AddActor(tempActor);
}

void MainWindow::updateText()
{
    vtkSmartPointer<vtkTextActor> tempVolumeTextActor = vtkSmartPointer<vtkTextActor>::New();
    if(objectType==0){
        tempVolumeTextActor->SetInput ("Volume: N/A");
    }
    else{
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
        this->objectDimensions.setx(this->objectParameters->GetVolumeX());
        this->objectDimensions.sety(this->objectParameters->GetVolumeY());
        this->objectDimensions.setz(this->objectParameters->GetVolumeZ());

        this->objectPosition.setx(0.0);
        this->objectPosition.setx(0.0);
        this->objectPosition.setx(0.0);
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

    this->refreshGrid();

    vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkActor> tempActor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    // init model

    std::vector<Vector3D> vectors = this->activeVTKModel.getVectors();
    for(int i =0; i<vectors.size(); i++)
    {
        points->InsertNextPoint(vectors[i].getx(),vectors[i].gety(),vectors[i].getz());
    }

    tempGrid->SetPoints(points);

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

            Vector3D color = this->activeVTKModel.getMaterial(tempCell.getMaterialID()).getColor();
            //cellData->SetTuple3(i, color.getx(),color.gety(),color.getz());
        }
        else
        {
            //this->cellData->RemoveTuple(i);
        }
    }
    //tempGrid->GetCellData()->SetScalars(cellData);

    this->objectType = 3;

    tempActor->SetMapper(this->mapperGridStage(tempGrid));
    tempActor->GetProperty()->EdgeVisibilityOn();

    tempActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(tempActor);

    this->updateText();

    this->makeMeasurement();

    this->activeGrid = tempGrid;
}

vtkAlgorithmOutput* MainWindow::filterStage(vtkAlgorithmOutput* firstFilterInput, int firstFilterIndex)
{
    vtkAlgorithmOutput* algorithmOutput = firstFilterInput;

    if(this->activeFilters[0])
    {
        if(firstFilterIndex!=0)
        {
            this->shrinkFilter->SetInputConnection(algorithmOutput);
            this->initFilter(0);
            algorithmOutput = this->shrinkFilter->GetOutputPort();
        }
    }
    if(this->activeFilters[1])
    {
        if(firstFilterIndex!=1)
        {
            this->clipFilter->SetInputConnection(algorithmOutput);
            this->initFilter(1);
            algorithmOutput = this->clipFilter->GetOutputPort();
        }
    }
    if(this->activeFilters[2])
    {
        if(firstFilterIndex!=2)
        {
            this->contourFilter->SetInputConnection(algorithmOutput);
            this->initFilter(2);
            algorithmOutput = this->contourFilter->GetOutputPort();
        }
    }
    if(this->activeFilters[3])
    {
        if(firstFilterIndex!=3)
        {
            this->outlineFilter->SetInputConnection(algorithmOutput);
            this->initFilter(3);
            algorithmOutput = this->outlineFilter->GetOutputPort();
        }
    }
    if(this->activeFilters[4])
    {
        if(firstFilterIndex!=4)
        {
            this->outlineCornerFilter->SetInputConnection(algorithmOutput);
            this->initFilter(4);
            algorithmOutput = this->outlineCornerFilter->GetOutputPort();
        }
    }
    if(this->activeFilters[5])
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

vtkSmartPointer<vtkDataSetMapper> MainWindow::mapperGridStage(vtkSmartPointer<vtkUnstructuredGrid> theGrid)
{
    vtkSmartPointer<vtkDataSetMapper> tempMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    this->geometryFilter->SetInputData(theGrid);
    if(this->activeFilters[0])
    {
        this->shrinkFilter->SetInputConnection(this->geometryFilter->GetOutputPort());
        this->initFilter(0);
        tempMapper->SetInputConnection(this->filterStage(this->shrinkFilter->GetOutputPort(), 0));
    }
    else if(this->activeFilters[1])
    {
        this->clipFilter->SetInputConnection(this->geometryFilter->GetOutputPort());
        this->initFilter(1);
        tempMapper->SetInputConnection(this->filterStage(this->clipFilter->GetOutputPort(), 1));
    }
    else if(this->activeFilters[2])
    {
        this->contourFilter->SetInputConnection(this->geometryFilter->GetOutputPort());
        this->initFilter(2);
        tempMapper->SetInputConnection(this->filterStage(this->contourFilter->GetOutputPort(), 2));
    }
    else if(this->activeFilters[3])
    {
        this->outlineFilter->SetInputConnection(this->geometryFilter->GetOutputPort());
        this->initFilter(3);
        tempMapper->SetInputConnection(this->filterStage(this->outlineFilter->GetOutputPort(), 3));
    }
    else if(this->activeFilters[4])
    {
        this->outlineCornerFilter->SetInputConnection(this->geometryFilter->GetOutputPort());
        this->initFilter(4);
        tempMapper->SetInputConnection(this->filterStage(this->outlineCornerFilter->GetOutputPort(), 4));
    }
    else if(this->activeFilters[5])
    {
        this->splineFilter->SetInputConnection(this->geometryFilter->GetOutputPort());
        this->initFilter(5);
        tempMapper->SetInputConnection(this->filterStage(this->splineFilter->GetOutputPort(), 5));
    }
    else
    {
        tempMapper->SetInputConnection(this->geometryFilter->GetOutputPort());
        tempMapper->SetScalarRange(0, this->activeVTKModel.getCellAmount());
        //tempMapper->SetLookupTable(this->lut);
        tempMapper->SetScalarModeToUseCellData();
        tempMapper->Update();
    }

    return tempMapper;
}

vtkSmartPointer<vtkDataSetMapper> MainWindow::mapperStage(vtkAlgorithmOutput* geometryInput)
{
    vtkSmartPointer<vtkDataSetMapper> tempMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    if(this->activeFilters[0])
    {
        this->shrinkFilter->SetInputConnection(geometryInput);
        this->initFilter(0);
        tempMapper->SetInputConnection(this->filterStage(this->shrinkFilter->GetOutputPort(), 0));
    }
    else if(this->activeFilters[1])
    {
        this->clipFilter->SetInputConnection(geometryInput);
        this->initFilter(1);
        tempMapper->SetInputConnection(this->filterStage(this->clipFilter->GetOutputPort(), 1));
    }
    else if(this->activeFilters[2])
    {
        this->contourFilter->SetInputConnection(geometryInput);
        this->initFilter(2);
        tempMapper->SetInputConnection(this->filterStage(this->contourFilter->GetOutputPort(), 2));
    }
    else if(this->activeFilters[3])
    {
        this->outlineFilter->SetInputConnection(geometryInput);
        this->initFilter(3);
        tempMapper->SetInputConnection(this->filterStage(this->outlineFilter->GetOutputPort(), 3));
    }
    else if(this->activeFilters[4])
    {
        this->outlineCornerFilter->SetInputConnection(geometryInput);
        this->initFilter(4);
        tempMapper->SetInputConnection(this->filterStage(this->outlineCornerFilter->GetOutputPort(), 4));
    }
    else if(this->activeFilters[5])
    {
        this->splineFilter->SetInputConnection(geometryInput);
        this->initFilter(5);
        tempMapper->SetInputConnection(this->filterStage(this->splineFilter->GetOutputPort(), 5));
    }
    else
    {
        tempMapper->SetInputConnection(geometryInput);
    }

    return tempMapper;
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
    this->refreshGrid();
    vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkActor> tempActor = vtkSmartPointer<vtkActor>::New();
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

    this->objectVolume = 1.0;

    this->updateText();
    this->makeMeasurement();

    tempActor->SetMapper(this->mapperGridStage(tempGrid));
    tempActor->GetProperty()->EdgeVisibilityOn();

    tempActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    tempActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(tempActor);
    this->activeGrid = tempGrid;
    ui->cellMinShow->setRange(1, 1);
    ui->cellMaxShow->setRange(1, 1);
    ui->cellMinShow->setValue(1);
    ui->cellMaxShow->setValue(1);

    this->refreshRender();
}

void MainWindow::displayTetrahedron()
{
    this->refreshGrid();
    vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkActor> tempActor = vtkSmartPointer<vtkActor>::New();
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

    objectParameters->SetInputData(tempGrid);

    this->objectType = 2;

    Vector3D Aval(0.0, 0.0, 0.0);
    Vector3D Bval(1.0, 0.0, 0.0);
    Vector3D Cval(1.0, 1.0, 0.0);
    Vector3D Dval(0.0, 1.0, 1.0);

//calculates volume of tetrahedron.
    double Vtetra1 = (((Bval-Aval).cross_product((Cval-Aval)))*(Dval-Aval));

    Vtetra1 = (Vtetra1/(6.0-12.0*(Vtetra1<0)));
    this->objectVolume = Vtetra1;

    this->updateText();
    this->makeMeasurement();

    tempActor->SetMapper(this->mapperGridStage(tempGrid));
    tempActor->GetProperty()->EdgeVisibilityOn();

    tempActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    tempActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(tempActor);
    this->activeGrid = tempGrid;
    ui->cellMinShow->setRange(1, 1);
    ui->cellMaxShow->setRange(1, 1);
    ui->cellMinShow->setValue(1);
    ui->cellMaxShow->setValue(1);

    this->refreshRender();
}

void MainWindow::displayPyramid()
{
    this->refreshGrid();
    vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkActor> tempActor = vtkSmartPointer<vtkActor>::New();
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

    objectParameters->SetInputData(tempGrid);

    this->objectType = 2;

    Vector3D Aval(1.0, 1.0, 1.0);
    Vector3D Bval(-1.0, 1.0, 1.0);
    Vector3D Cval(-1.0, -1.0, 1.0);
    Vector3D Dval(1.0, -1.0, 1.0);
    Vector3D Eval(0.0, 0.0, 0.0);

    //calculates volume of each tetrahedron.
//configuration of vertices were checked using the test code, so there is no overlapping of area between the tetrahedrons
    double Vtetra1 = (((Bval-Aval).cross_product((Cval-Aval)))*(Dval-Aval));
    double Vtetra2 = (((Bval-Eval).cross_product((Cval-Eval)))*(Dval-Eval));

//makes volumes positive
    Vtetra1 = (Vtetra1/(6.0-12.0*(Vtetra1<0)));
    Vtetra2 = (Vtetra2/(6.0-12.0*(Vtetra2<0)));

    //adds all the volume of tetrahedrons to aquire the final volume of the pyramid
    this->objectVolume = (Vtetra1 + Vtetra2);

    this->updateText();
    this->makeMeasurement();

    tempActor->SetMapper(this->mapperGridStage(tempGrid));
    tempActor->GetProperty()->EdgeVisibilityOn();

    tempActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    tempActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(tempActor);
    this->activeGrid = tempGrid;
    ui->cellMinShow->setRange(1, 1);
    ui->cellMaxShow->setRange(1, 1);
    ui->cellMinShow->setValue(1);
    ui->cellMaxShow->setValue(1);

    this->refreshRender();
}

//Function of class Mainwindow, handleOpenButton()
//Function to get specified model file
// Arguments for handleOpenButton(): none(file chosen using getSaveFileName() function)
// return value: none (file is opened)
void MainWindow::handleOpenButton()
{
    this->activeFileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "./", tr("STL Files(*.stl *.mod)"));
    QFileInfo fi(this->activeFileName);
    emit statusUpdateMessage( QString("Loaded: ")+fi.suffix(), 0 );
    if(fi.suffix()=="stl")
    {
        this->refreshGrid();
        vtkSmartPointer<vtkActor> tempActor = vtkSmartPointer<vtkActor>::New();
        //emit statusUpdateMessage( QString("Loaded: ")+this->activeFileName, 0 );
        this->activeReader->SetFileName(this->activeFileName.toLatin1().data());
        this->activeReader->Update();
        this->objectType = 1;

        this->objectParameters->SetInputConnection(this->activeReader->GetOutputPort());

        this->objectVolume = this->objectParameters->GetVolume();

        tempActor->SetMapper(this->mapperStage(this->activeReader->GetOutputPort()));
        tempActor->GetProperty()->EdgeVisibilityOn();

        tempActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
        tempActor->GetProperty()->LightingOff();

        this->activeRenderer->AddActor(tempActor);

        this->updateText();
        this->makeMeasurement();

        ui->cellMinShow->setRange(1, 1);
        ui->cellMaxShow->setRange(1, 1);
        ui->cellMinShow->setValue(1);
        ui->cellMaxShow->setValue(1);

    }
    else if(fi.suffix()=="mod")
    {
        this->refreshGrid();

        vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
        vtkSmartPointer<vtkActor> tempActor = vtkSmartPointer<vtkActor>::New();
        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
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
        cellData->SetNumberOfTuples(this->activeVTKModel.getCellAmount());

        lut->SetNumberOfTableValues((float)this->activeVTKModel.getCellAmount());
        lut->SetTableRange(0.0, (float)(this->activeVTKModel.getCellAmount()-1));

        lut->Build();

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
            cellData->InsertTuple3(i, color.getx(),color.gety(),color.getz());

            //lut->SetTableValue(i, rgb[0], rgb[1], rgb[2]);

            this->objectVolume += tempCell.getVolume();
            this->objectWeight += tempCell.getWeight();
        }

        tempGrid->GetCellData()->SetScalars(cellData);
        this->objectType = 3;

        tempActor->SetMapper(this->mapperGridStage(tempGrid));
        tempActor->GetProperty()->EdgeVisibilityOn();

        //tempActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
        tempActor->GetProperty()->LightingOff();

        this->activeRenderer->AddActor(tempActor);

        this->updateText();
        this->makeMeasurement();

        this->activeGrid = tempGrid;

        ui->cellMinShow->setRange(1, this->activeVTKModel.getCellAmount());
        ui->cellMaxShow->setRange(1, this->activeVTKModel.getCellAmount());
        ui->cellMinShow->setValue(1);
        ui->cellMaxShow->setValue(this->activeVTKModel.getCellAmount());
    }
    this->refreshRender();
}

void MainWindow::resetViewer()
{
    this->refreshGrid();
    vtkSmartPointer<vtkActor> tempActor = vtkSmartPointer<vtkActor>::New();

    ui->shrinkCheck->setCheckState(Qt::Unchecked);
    ui->clipCheck->setCheckState(Qt::Unchecked);

    this->objectType = 0;
    this->objectVolume = 1.0;

    vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();

    tempActor->SetMapper(this->mapperStage(cubeSource->GetOutputPort()));

    tempActor->GetProperty()->EdgeVisibilityOn();

    tempActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    tempActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(tempActor);

    this->updateText();
    this->makeMeasurement();

    this->activeRenderer->SetBackground( this->activeColors->GetColor3d("Silver").GetData() );
    this->activeRenderer->GetActiveCamera()->Azimuth(30);
    this->activeRenderer->GetActiveCamera()->Elevation(30);

    ui->cellMinShow->setRange(1, 1);
    ui->cellMaxShow->setRange(1, 1);
    ui->cellMinShow->setValue(1);
    ui->cellMaxShow->setValue(1);

    this->refreshRender();
}

void MainWindow::resetCamera()
{
    this->activeRenderer->ResetCamera();
    this->activeRenderer->GetActiveCamera()->Azimuth(30);
    this->activeRenderer->GetActiveCamera()->Elevation(30);
    this->activeRenderer->ResetCameraClippingRange();
    this->activeRenderWindow->Render();
}

void MainWindow::changeBackgroundColor()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Pick a color",  QColorDialog::DontUseNativeDialog);
    this->activeRenderer->SetBackground((double)color.red()/255,(double)color.green()/255,(double)color.blue()/255);
    this->activeRenderWindow->Render();
}

void MainWindow::changeObjectColor()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Pick a color",  QColorDialog::DontUseNativeDialog);

    //this->activeActor->GetProperty()->SetColor((double)color.red()/255,(double)color.green()/255,(double)color.blue()/255);

    this->activeRenderWindow->Render();
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
        double originX = (clipNormalsX)*(this->objectPosition.getx()+(this->objectDimensions.getx()*(this->clipOriginPart)));
        double originY = (clipNormalsY)*(this->objectPosition.gety()+(this->objectDimensions.gety()*(this->clipOriginPart)));
        double originZ = (clipNormalsZ)*(this->objectPosition.getz()+(this->objectDimensions.getz()*(this->clipOriginPart)));
        planeLeft->SetOrigin(originX, originY, originZ);
        planeLeft->SetNormal(clipNormalsX, clipNormalsY, clipNormalsZ);
        this->clipFilter->SetClipFunction( planeLeft.Get() );
        break;
    }
    case 2:
    {
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

void MainWindow::handleGeometryFilter()
{
    this->updateObject();
    this->updateText();
    this->refreshRender();
}
void MainWindow::handleShrinkFilter()
{
    this->activeFilters[0] = ui->shrinkCheck->isChecked();
    this->updateObject();
    this->updateText();
    this->refreshRender();
}
void MainWindow::handleClipFilter()
{
    this->activeFilters[1] = ui->clipCheck->isChecked();
    this->updateObject();
    this->updateText();
    this->refreshRender();
}
void MainWindow::handleContourFilter()
{
    this->updateObject();
    this->updateText();
    this->refreshRender();
}
void MainWindow::handleOutlineFilter()
{
    this->updateObject();
    this->updateText();
    this->refreshRender();
}
void MainWindow::handleOutlineCornerFilter()
{
    this->updateObject();
    this->updateText();
    this->refreshRender();
}
void MainWindow::handleSplineFilter()
{
    this->updateObject();
    this->updateText();
    this->refreshRender();
}

void MainWindow::changeShrinkFilterValue(int newVal)
{
    if(newVal>1.0)
    {
        ui->shrinkFactor->setValue(1.0);
    }
    this->updateObject();
    this->updateText();
    this->refreshRender();
}

void MainWindow::changeClipValue(int newVal)
{
    this->clipOriginPart = ((double)newVal/100);

    this->updateObject();
    this->updateText();
    this->refreshRender();
}

void MainWindow::changeClipX()
{
    clipNormalsX = ui->clipX->isChecked();
    this->updateObject();
    this->updateText();
    this->refreshRender();
}

void MainWindow::changeClipY()
{
    clipNormalsY = ui->clipY->isChecked();
    this->updateObject();
    this->updateText();
    this->refreshRender();
}

void MainWindow::changeClipZ()
{
    clipNormalsZ = ui->clipZ->isChecked();
    this->updateObject();
    this->updateText();
    this->refreshRender();
}

void MainWindow::setMinCellShow(int newVal)
{

    if(newVal<1)
    {
        ui->cellMinShow->setValue(1);
    }

    if(newVal>ui->cellMaxShow->value())
    {
        ui->cellMinShow->setValue(ui->cellMaxShow->value());
    }

    this->updateVTKModel();
    this->refreshRender();

}

void MainWindow::setMaxCellShow(int newVal)
{
    if(newVal>this->activeVTKModel.getCellAmount())
    {
        ui->cellMaxShow->setValue(this->activeVTKModel.getCellAmount());
    }

    if(newVal<ui->cellMinShow->value())
    {
        ui->cellMaxShow->setValue(ui->cellMinShow->value());
    }

    this->updateVTKModel();

    this->refreshRender();
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

// standard call to setup Qt UI (same as previously)
    ui->setupUi( this );

//Create connection to open action
    connect( ui->actionOpen, &QAction::triggered, this, &MainWindow::handleOpenButton);
    connect( ui->makeHex, &QPushButton::released, this, &MainWindow::displayHexahedron );
    connect( ui->makeTetra, &QPushButton::released, this, &MainWindow::displayTetrahedron );
    connect( ui->makePyr, &QPushButton::released, this, &MainWindow::displayPyramid );
    connect( ui->resetObject, &QPushButton::released, this, &MainWindow::resetViewer );
    connect( ui->resetCamera, &QPushButton::released, this, &MainWindow::resetCamera );
    connect( ui->backgroundColor, &QPushButton::released, this, &MainWindow::changeBackgroundColor );
    connect( ui->objectColor, &QPushButton::released, this, &MainWindow::changeObjectColor );

//Create connection to message bar
    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage );

//slider control
    connect(ui->clipSlider, SIGNAL(valueChanged(int)), this, SLOT(changeClipValue(int)));

//check boxes
    connect(ui->shrinkCheck, SIGNAL(stateChanged(int)), this, SLOT(handleShrinkFilter()));
    connect(ui->clipCheck, SIGNAL(stateChanged(int)), this, SLOT(handleClipFilter()));

    connect(ui->clipX, SIGNAL(stateChanged(int)), this, SLOT(changeClipX()));
    connect(ui->clipY, SIGNAL(stateChanged(int)), this, SLOT(changeClipY()));
    connect(ui->clipZ, SIGNAL(stateChanged(int)), this, SLOT(changeClipZ()));

//spin boxes
    connect(ui->shrinkFactor, SIGNAL(valueChanged(double)), this, SLOT(changeShrinkFilterValue(int)));

    connect(ui->cellMinShow, SIGNAL(valueChanged(int)), this, SLOT(setMinCellShow(int)));
    connect(ui->cellMaxShow, SIGNAL(valueChanged(int)), this, SLOT(setMaxCellShow(int)));

    ui->shrinkFactor->setRange(0.0, 1.0);
    ui->shrinkFactor->setSingleStep(0.01);
    ui->shrinkFactor->setValue(1.0);

// creator

    this->activeRenderWindow = ui->qvtkWidget->GetRenderWindow();

    this->activeRenderWindow->AddRenderer( this->activeRenderer );

    this->resetViewer();

    //this->activeRenderer->AddLight(this->activeLight);
    //this->activeRenderer->LightFollowCameraOn();
}
MainWindow::~MainWindow()
{
    delete ui;
}
// /mainwindow.cpp----------------------------------------------------------
