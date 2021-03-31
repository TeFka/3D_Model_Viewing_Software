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
    //this->activeGrid->Reset();
    //this->activeGrid->Squeeze();
    //this->cells->Reset();
    //this->cells->Squeeze();
    //this->gridPoints->Reset();
    //this->gridPoints->Squeeze();
    //this->pointCoordinates.clear();

    //for(int i =0;i<cellData->SetNumberOfTuples(this->activeVTKModel.getCellAmount());

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
    this->activeRenderer->AddActor(tempActor);
}

void MainWindow::updateText()
{
    //int volume
    //textActor->SetInput ( "Hello world" );
    //textActor->SetPosition2 ( 10, 40 );
    //textActor->GetTextProperty()->SetFontSize ( 24 );
    //textActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
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
        //tempMapper->SetInputData(this->activeGrid);
        tempMapper->SetInputConnection(this->geometryFilter->GetOutputPort());
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

    this->objectType = 2;

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

    this->objectType = 2;

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

        //this->updateObject();

        tempActor->SetMapper(this->mapperStage(this->activeReader->GetOutputPort()));
        tempActor->GetProperty()->EdgeVisibilityOn();

        tempActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
        tempActor->GetProperty()->LightingOff();

        this->activeRenderer->AddActor(tempActor);

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
            float rgb[3];
            rgb[0] = color.getx();
            rgb[1] = color.gety();
            rgb[2] = color.getz();
            cellData->InsertTuple(i, rgb);
        }

        tempGrid->GetCellData()->SetScalars(cellData);

        this->objectType = 3;

        tempActor->SetMapper(this->mapperGridStage(tempGrid));
        tempActor->GetProperty()->EdgeVisibilityOn();

        //tempActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
        tempActor->GetProperty()->LightingOff();

        this->activeRenderer->AddActor(tempActor);
        this->activeGrid = tempGrid;
        ui->cellMinShow->setRange(1, this->activeVTKModel.getCellAmount());
        ui->cellMaxShow->setRange(1, this->activeVTKModel.getCellAmount());
        ui->cellMinShow->setValue(1);
        ui->cellMaxShow->setValue(this->activeVTKModel.getCellAmount());
    }
    this->refreshRender();
}

void MainWindow::changeLight(int newVal)
{
    emit statusUpdateMessage( QString("Light: ")+QString::number(newVal), 0 );
    this->activeLight->SetIntensity(((float)newVal/100));
    this->activeRenderWindow->Render();
}

void MainWindow::resetViewer()
{
    this->refreshGrid();
    vtkSmartPointer<vtkActor> tempActor = vtkSmartPointer<vtkActor>::New();

    ui->shrinkCheck->setCheckState(Qt::Unchecked);
    ui->clipCheck->setCheckState(Qt::Unchecked);
    this->changeLight(100);

    this->objectType = 0;

    //this->updateObject();

    vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();

    tempActor->SetMapper(this->mapperStage(cubeSource->GetOutputPort()));

    tempActor->GetProperty()->EdgeVisibilityOn();

    tempActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    tempActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(tempActor);;

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
        planeLeft->SetOrigin(0.0, 0.0, 0.0);
        planeLeft->SetNormal(-1.0, 0.0, 0.0);
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
    this->refreshRender();
}
void MainWindow::handleShrinkFilter()
{
    this->activeFilters[0] = ui->shrinkCheck->isChecked();
    this->updateObject();
    this->refreshRender();
}
void MainWindow::handleClipFilter()
{
    this->activeFilters[1] = ui->clipCheck->isChecked();
    this->updateObject();
    this->refreshRender();
}
void MainWindow::handleContourFilter()
{
    this->updateObject();
    this->refreshRender();
}
void MainWindow::handleOutlineFilter()
{
    this->updateObject();
    this->refreshRender();
}
void MainWindow::handleOutlineCornerFilter()
{
    this->updateObject();
    this->refreshRender();
}
void MainWindow::handleSplineFilter()
{
    this->updateObject();
    this->refreshRender();
}

void MainWindow::changeShrinkFilterValue(int newVal)
{
    if(newVal>1.0)
    {
        ui->shrinkFactor->setValue(1.0);
    }
    this->updateObject();
    this->refreshRender();
}

void MainWindow::setMinCellShow(int newVal)
{

    /*if(newVal<1)
    {
        ui->cellMinShow->setValue(1);
    }

    if(newVal>ui->cellMaxShow->value())
    {
        ui->cellMinShow->setValue(ui->cellMaxShow->value());
    }
    int i = 5;
    if((i>=(ui->cellMinShow->value()-1)) && (i<ui->cellMaxShow->value()))
    {
        this->activeActor->SetVisibility(1);
    }
    else
    {
        this->activeActor->SetVisibility(0);
    }

    this->refreshRender();
    */
}

void MainWindow::setMaxCellShow(int newVal)
{
    /*
    if(newVal>this->activeVTKModel.getCellAmount())
    {
        ui->cellMinShow->setValue(this->activeVTKModel.getCellAmount());
    }

    if(newVal<ui->cellMinShow->value())
    {
        ui->cellMaxShow->setValue(ui->cellMinShow->value());
    }
    int i = 5;
    if((i>=(ui->cellMinShow->value()-1)) && (i<ui->cellMaxShow->value()))
    {
        this->activeActor->SetVisibility(1);
    }
    else
    {
        this->activeActor->SetVisibility(0);
    }

    this->refreshRender();
    */
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
    //connect(ui->lightSlider, SIGNAL(valueChanged(int)), this, SLOT(changeLight(int)));
    //ui->lightSlider->setMinimum(0);
    //ui->lightSlider->setMaximum(100);

//check boxes
    connect(ui->shrinkCheck, SIGNAL(stateChanged(int)), this, SLOT(handleShrinkFilter()));
    connect(ui->clipCheck, SIGNAL(stateChanged(int)), this, SLOT(handleClipFilter()));

//spin boxes
    connect(ui->shrinkFactor, SIGNAL(valueChanged(double)), this, SLOT(changeShrinkFilterValue(int)));

    connect(ui->cellMinShow, SIGNAL(valueChanged(int)), this, SLOT(setMinCellShow(int)));
    connect(ui->cellMaxShow, SIGNAL(valueChanged(int)), this, SLOT(setMaxCellShow(int)));

    ui->shrinkFactor->setRange(0.0, 1.0);
    ui->shrinkFactor->setSingleStep(0.01);
    ui->shrinkFactor->setValue(1.0);

//set VTK variables
    //this->activeLight->SetLightTypeToSceneLight();
    //this->activeLight->SetPosition( 5, 5, 150 );
    //this->activeLight->SetPositional( true );
    //this->activeLight->SetConeAngle( 10 );
    //this->activeLight->SetFocalPoint( 0, 0, 0 );
    //this->activeLight->SetDiffuseColor( 1, 1, 1 );
    //this->activeLight->SetAmbientColor( 1, 1, 1 );
    //this->activeLight->SetSpecularColor( 1, 1, 1 );
    //this->activeLight->SetIntensity( 1.0 );

    //text writing
    //this->activeRenderer->AddActor2D ( volumeTextActor );
    //this->activeRenderer->AddActor2D ( cellNumTextActor );
    //this->activeRenderer->AddActor2D ( weightTextActor );
    //this->activeRenderer->AddActor2D ( positionTextActor );

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
