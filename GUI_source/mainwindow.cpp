// mainwindow.cpp-----------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::refreshRender()
{
    this->activeRenderer->ResetCamera();
    this->activeRenderer->ResetCameraClippingRange();

    this->activeRenderWindow->Render();
}

void MainWindow::refreshGrid()
{
    for(int i=0; i<this->actors.size(); i++)
    {
        if(this->uGrids.size()>i)
        {
            this->uGrids[i]->Reset();
            this->uGrids[i]->Squeeze();
        }
        this->activeRenderer->RemoveActor(this->actors[i]);

    }
    this->uGrids.clear();
    this->mappers.clear();
    this->actors.clear();
}

vtkAlgorithmOutput* MainWindow::filterStage(vtkAlgorithmOutput* firstFilterInput, int firstFilterIndex)
{
    vtkAlgorithmOutput* algorithmOutput = firstFilterInput;
    if(this->activeFilters[0])
    {
        if(firstFilterIndex!=0)
        {
            this->geometryFilter->SetInputConnection(algorithmOutput);
            this->initFilter(0);
            algorithmOutput = this->geometryFilter->GetOutputPort();
        }
    }
    if(this->activeFilters[1])
    {
        if(firstFilterIndex!=1)
        {
            this->shrinkFilter->SetInputConnection(algorithmOutput);
            this->initFilter(1);
            algorithmOutput = this->shrinkFilter->GetOutputPort();
        }
    }
    if(this->activeFilters[2])
    {
        if(firstFilterIndex!=2)
        {
            this->clipFilter->SetInputConnection(algorithmOutput);
            this->initFilter(2);
            algorithmOutput = this->clipFilter->GetOutputPort();
        }
    }
    if(this->activeFilters[3])
    {
        if(firstFilterIndex!=3)
        {
            this->contourFilter->SetInputConnection(algorithmOutput);
            this->initFilter(3);
            algorithmOutput = this->contourFilter->GetOutputPort();
        }
    }
    if(this->activeFilters[4])
    {
        if(firstFilterIndex!=4)
        {
            this->outlineFilter->SetInputConnection(algorithmOutput);
            this->initFilter(4);
            algorithmOutput = this->outlineFilter->GetOutputPort();
        }
    }
    if(this->activeFilters[5])
    {
        if(firstFilterIndex!=5)
        {
            this->outlineCornerFilter->SetInputConnection(algorithmOutput);
            this->initFilter(5);
            algorithmOutput = this->outlineCornerFilter->GetOutputPort();
        }
    }
    if(this->activeFilters[6])
    {
        if(firstFilterIndex!=6)
        {
            this->splineFilter->SetInputConnection(algorithmOutput);
            this->initFilter(6);
            algorithmOutput = this->splineFilter->GetOutputPort();
        }
    }
    return algorithmOutput;
}

vtkSmartPointer<vtkDataSetMapper> MainWindow::mapperStage(vtkSmartPointer<vtkUnstructuredGrid> theGrid)
{
    vtkSmartPointer<vtkDataSetMapper> tempMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    if(this->activeFilters[0])
    {
            this->geometryFilter->SetInputData(theGrid);
            this->initFilter(0);
            tempMapper->SetInputConnection(this->filterStage(this->geometryFilter->GetOutputPort(), 0));
            return tempMapper;
    }
    if(this->activeFilters[1])
    {
            this->shrinkFilter->SetInputData(theGrid);
            this->initFilter(1);
            tempMapper->SetInputConnection(this->filterStage(this->shrinkFilter->GetOutputPort(), 1));
            return tempMapper;
    }
    if(this->activeFilters[2])
    {
            this->clipFilter->SetInputData(theGrid);
            this->initFilter(2);
            tempMapper->SetInputConnection(this->filterStage(this->clipFilter->GetOutputPort(), 2));
            return tempMapper;
    }
    if(this->activeFilters[3])
    {
            this->contourFilter->SetInputData(theGrid);
            this->initFilter(3);
            tempMapper->SetInputConnection(this->filterStage(this->contourFilter->GetOutputPort(), 3));
            return tempMapper;
    }
    if(this->activeFilters[4])
    {
            this->outlineFilter->SetInputData(theGrid);
            this->initFilter(4);
            tempMapper->SetInputConnection(this->filterStage(this->outlineFilter->GetOutputPort(), 4));
            return tempMapper;
    }
    if(this->activeFilters[5])
    {
            this->outlineCornerFilter->SetInputData(theGrid);
            this->initFilter(5);
            tempMapper->SetInputConnection(this->filterStage(this->outlineCornerFilter->GetOutputPort(), 5));
            return tempMapper;
    }
    if(this->activeFilters[6])
    {
            this->splineFilter->SetInputData(theGrid);
            this->initFilter(6);
            tempMapper->SetInputConnection(this->filterStage(this->splineFilter->GetOutputPort(), 6));
            return tempMapper;
    }
    tempMapper->SetInputData(theGrid);
    return tempMapper;
}

vtkSmartPointer<vtkDataSetMapper> MainWindow::mapperStage(vtkAlgorithmOutput* geometryInput)
{
    vtkSmartPointer<vtkDataSetMapper> tempMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    if(this->activeFilters[0])
    {
            this->geometryFilter->SetInputConnection(geometryInput);
            this->initFilter(0);
            tempMapper->SetInputConnection(this->filterStage(this->geometryFilter->GetOutputPort(), 0));
            return tempMapper;
    }
    if(this->activeFilters[1])
    {
            this->shrinkFilter->SetInputConnection(geometryInput);
            this->initFilter(1);
            tempMapper->SetInputConnection(this->filterStage(this->shrinkFilter->GetOutputPort(), 1));
            return tempMapper;
    }
    if(this->activeFilters[2])
    {
            this->clipFilter->SetInputConnection(geometryInput);
            this->initFilter(2);
            tempMapper->SetInputConnection(this->filterStage(this->clipFilter->GetOutputPort(), 2));
            return tempMapper;
    }
    if(this->activeFilters[3])
    {
            this->contourFilter->SetInputConnection(geometryInput);
            this->initFilter(3);
            tempMapper->SetInputConnection(this->filterStage(this->contourFilter->GetOutputPort(), 3));
            return tempMapper;
    }
    if(this->activeFilters[4])
    {
            this->outlineFilter->SetInputConnection(geometryInput);
            this->initFilter(4);
            tempMapper->SetInputConnection(this->filterStage(this->outlineFilter->GetOutputPort(), 4));
            return tempMapper;
    }
    if(this->activeFilters[5])
    {
            this->outlineCornerFilter->SetInputConnection(geometryInput);
            this->initFilter(5);
            tempMapper->SetInputConnection(this->filterStage(this->outlineCornerFilter->GetOutputPort(), 5));
            return tempMapper;
    }
    if(this->activeFilters[6])
    {
            this->splineFilter->SetInputConnection(geometryInput);
            this->initFilter(6);
            tempMapper->SetInputConnection(this->filterStage(this->splineFilter->GetOutputPort(), 6));
            return tempMapper;
    }
    tempMapper->SetInputConnection(geometryInput);
    return tempMapper;
}

vtkSmartPointer<vtkUnstructuredGrid> MainWindow::drawHexahedron(Cell *cell)
{
    vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    std::vector<int> indx = cell->getIndices();
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkHexahedron> hex = vtkSmartPointer<vtkHexahedron>::New();

    for(int n = 0; n<indx.size(); n++)
    {
        Vector3D tempVec = this->activeVTKModel.getVector(indx[n]);
        this->pointCoordinates.push_back({tempVec.getx(), tempVec.gety(), tempVec.getz()});

        points->InsertNextPoint(tempVec.getx(), tempVec.gety(), tempVec.getz());

        hex->GetPointIds()->SetId(n, n);
    }

    this->cells->InsertNextCell(hex);
    tempGrid->SetPoints(points);
    tempGrid->InsertNextCell(hex->GetCellType(), hex->GetPointIds());
    return tempGrid;
}

vtkSmartPointer<vtkUnstructuredGrid> MainWindow::drawTetrahedron(Cell *cell)
{
    vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    std::vector<int> indx = cell->getIndices();
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkTetra> tetr = vtkSmartPointer<vtkTetra>::New();

    for(int n = 0; n<indx.size(); n++)
    {
        Vector3D tempVec = this->activeVTKModel.getVector(indx[n]);
        this->pointCoordinates.push_back({{tempVec.getx(), tempVec.gety(), tempVec.getz()}});

        points->InsertNextPoint(tempVec.getx(), tempVec.gety(), tempVec.getz());

        tetr->GetPointIds()->SetId(n, n);
    }

    this->cells->InsertNextCell(tetr);
    tempGrid->SetPoints(points);
    tempGrid->InsertNextCell(tetr->GetCellType(), tetr->GetPointIds());
    return tempGrid;
}

vtkSmartPointer<vtkUnstructuredGrid> MainWindow::drawPyramid(Cell *cell)
{
    vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    std::vector<int> indx = cell->getIndices();
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkPyramid> pyr = vtkSmartPointer<vtkPyramid>::New();

    for(int n = 0; n<indx.size(); n++)
    {
        Vector3D tempVec = this->activeVTKModel.getVector(indx[n]);
        this->pointCoordinates.push_back({{tempVec.getx(), tempVec.gety(), tempVec.getz()}});

        points->InsertNextPoint(tempVec.getx(), tempVec.gety(), tempVec.getz());

        pyr->GetPointIds()->SetId(n, n);
    }

    this->cells->InsertNextCell(pyr);
    tempGrid->SetPoints(points);
    tempGrid->InsertNextCell(pyr->GetCellType(), pyr->GetPointIds());
    return tempGrid;
}

void MainWindow::displayHexahedron()
{
    this->refreshGrid();
    vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    //vtkSmartPointer<vtkDataSetMapper> tempMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkActor> tempActor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    this->pointCoordinates.clear();
    this->cells->Reset();
    this->cells->Squeeze();
    //draw
    this->pointCoordinates.push_back({{0.0, 0.0, 0.0}}); // Face 1
    this->pointCoordinates.push_back({{1.0, 0.0, 0.0}});
    this->pointCoordinates.push_back({{1.0, 1.0, 0.0}});
    this->pointCoordinates.push_back({{0.0, 1.0, 0.0}});
    this->pointCoordinates.push_back({{0.0, 0.0, 1.0}}); // Face 2
    this->pointCoordinates.push_back({{1.0, 0.0, 1.0}});
    this->pointCoordinates.push_back({{1.0, 1.0, 1.0}});
    this->pointCoordinates.push_back({{0.0, 1.0, 1.0}});

    // Create a hexahedron from the points.
    vtkSmartPointer<vtkHexahedron> hex = vtkSmartPointer<vtkHexahedron>::New();

    for (auto i = 0; i < this->pointCoordinates.size(); ++i)
    {
        points->InsertNextPoint(pointCoordinates[i].data());
        hex->GetPointIds()->SetId(i, i);
    }
    this->cells->InsertNextCell(hex);
    tempGrid->SetPoints(points);
    tempGrid->InsertNextCell(hex->GetCellType(), hex->GetPointIds());

    //tempMapper = mapperStage(tempGrid);

    tempActor->SetMapper(this->mapperStage(tempGrid));
    tempActor->GetProperty()->EdgeVisibilityOn();

    tempActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    tempActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(tempActor);

    this->uGrids.push_back(tempGrid);
    //this->mappers.push_back(tempMapper);
    this->actors.push_back(tempActor);

    this->objectType = 2;
    this->refreshRender();
}

void MainWindow::displayTetrahedron()
{
    this->refreshGrid();
    vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    //vtkSmartPointer<vtkDataSetMapper> tempMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkActor> tempActor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    this->pointCoordinates.clear();
    this->cells->Reset();
    this->cells->Squeeze();

    //draw
    this->pointCoordinates.push_back({{0.0, 0.0, 0.0}}); // Face 1
    this->pointCoordinates.push_back({{1.0, 0.0, 0.0}});
    this->pointCoordinates.push_back({{1.0, 1.0, 0.0}});
    this->pointCoordinates.push_back({{0.0, 1.0, 1.0}});

    // Create a hexahedron from the points.
    vtkSmartPointer<vtkTetra> tetr = vtkSmartPointer<vtkTetra>::New();

    for (auto i = 0; i < this->pointCoordinates.size(); ++i)
    {
        points->InsertNextPoint(pointCoordinates[i].data());
        tetr->GetPointIds()->SetId(i, i);
    }
    this->cells->InsertNextCell(tetr);
    tempGrid->SetPoints(points);
    tempGrid->InsertNextCell(tetr->GetCellType(), tetr->GetPointIds());

    //tempMapper = mapperStage(tempGrid);

    tempActor->SetMapper(mapperStage(tempGrid));
    tempActor->GetProperty()->EdgeVisibilityOn();

    tempActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    tempActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(tempActor);

    this->uGrids.push_back(tempGrid);
    //this->mappers.push_back(tempMapper);
    this->actors.push_back(tempActor);

    this->objectType = 2;
    this->refreshRender();
}

void MainWindow::displayPyramid()
{
    this->refreshGrid();
    vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    //vtkSmartPointer<vtkDataSetMapper> tempMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkActor> tempActor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    this->pointCoordinates.clear();
    this->cells->Reset();
    this->cells->Squeeze();
    //draw
    this->pointCoordinates.push_back({{1.0, 1.0, 1.0}}); // Face 1
    this->pointCoordinates.push_back({{-1.0, 1.0, 1.0}});
    this->pointCoordinates.push_back({{-1.0, -1.0, 1.0}});
    this->pointCoordinates.push_back({{1.0, -1.0, 1.0}});
    this->pointCoordinates.push_back({{0.0, 0.0, 0.0}}); // Face 2

    // Create a hexahedron from the points.
    vtkSmartPointer<vtkPyramid> pyr = vtkSmartPointer<vtkPyramid>::New();

    for (auto i = 0; i < this->pointCoordinates.size(); ++i)
    {
        points->InsertNextPoint(pointCoordinates[i].data());
        pyr->GetPointIds()->SetId(i, i);
    }
    this->cells->InsertNextCell(pyr);
    tempGrid->SetPoints(points);
    tempGrid->InsertNextCell(pyr->GetCellType(), pyr->GetPointIds());

    //tempMapper = mapperStage(tempGrid);

    tempActor->SetMapper(mapperStage(tempGrid));
    tempActor->GetProperty()->EdgeVisibilityOn();

    tempActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
    tempActor->GetProperty()->LightingOff();

    this->activeRenderer->AddActor(tempActor);

    this->uGrids.push_back(tempGrid);
    //this->mappers.push_back(tempMapper);
    this->actors.push_back(tempActor);

    this->objectType = 2;
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
        vtkSmartPointer<vtkDataSetMapper> tempMapper = vtkSmartPointer<vtkDataSetMapper>::New();
        vtkSmartPointer<vtkActor> tempActor = vtkSmartPointer<vtkActor>::New();
        //emit statusUpdateMessage( QString("Loaded: ")+this->activeFileName, 0 );
        this->activeReader->SetFileName(this->activeFileName.toLatin1().data());
        this->activeReader->Update();
        this->objectType = 1;

        tempActor->SetMapper(mapperStage(this->activeReader->GetOutputPort()));
        tempActor->GetProperty()->EdgeVisibilityOn();
        tempActor->GetProperty()->SetColor(this->activeColors->GetColor3d("Red").GetData());
        tempActor->GetProperty()->LightingOff();
        this->actors.push_back(tempActor);
        this->activeRenderer->AddActor(tempActor);
    }
    else if(fi.suffix()=="mod")
    {
        this->refreshGrid();
        // init model
        this->activeVTKModel.loadModel(this->activeFileName.toStdString().c_str());

        //rendering
        //refresh grid
        this->pointCoordinates.clear();
        this->cells->Reset();
        this->cells->Squeeze();
        //set values
        for(int i = 0; i<this->activeVTKModel.getCellAmount(); i++)
        {
            Cell tempCell = this->activeVTKModel.getCell(i);
            vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
            //vtkSmartPointer<vtkDataSetMapper> tempMapper = vtkSmartPointer<vtkDataSetMapper>::New();
            vtkSmartPointer<vtkActor> tempActor = vtkSmartPointer<vtkActor>::New();
            if(tempCell.getType()==1)
            {
                tempGrid = this->drawHexahedron(&tempCell);
            }
            if(tempCell.getType()==2)
            {
                tempGrid = this->drawPyramid(&tempCell);
            }
            if(tempCell.getType()==3)
            {
                tempGrid = this->drawTetrahedron(&tempCell);
            }

            //tempMapper->SetInputData(tempGrid);

            tempActor->SetMapper(mapperStage(tempGrid));
            tempActor->GetProperty()->EdgeVisibilityOn();

            Vector3D color = this->activeVTKModel.getMaterial(tempCell.getMaterialID()).getColor();
            tempActor->GetProperty()->SetColor(color.getx(),color.gety(),color.getz());
            tempActor->GetProperty()->LightingOff();

            this->activeRenderer->AddActor(tempActor);

            //this->activeRenderWindow->AddRenderer(tempRenderer);
            this->uGrids.push_back(tempGrid);
            this->actors.push_back(tempActor);
        }
        this->objectType = 3;
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
    ui->shrinkCheck->setCheckState(Qt::Unchecked);
    ui->clipCheck->setCheckState(Qt::Unchecked);
    this->changeLight(100);

    //vtkSmartPointer<vtkDataSetMapper> tempMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkActor> tempActor = vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
    //tempMapper->SetInputConnection( cubeSource->GetOutputPort() );

    tempActor->SetMapper(mapperStage(cubeSource->GetOutputPort()));
    tempActor->GetProperty()->EdgeVisibilityOn();
    tempActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );

    //this->mappers.push_back(tempMapper);
    this->actors.push_back(tempActor);

    this->activeRenderer->AddActor(tempActor);
    this->activeRenderer->SetBackground( this->activeColors->GetColor3d("Silver").GetData() );
    this->activeRenderer->GetActiveCamera()->Azimuth(30);
    this->activeRenderer->GetActiveCamera()->Elevation(30);
    this->refreshRender();
    this->objectType = 0;
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
    for(int i = 0; i<this->actors.size(); i++)
    {
        this->actors[i]->GetProperty()->SetColor((double)color.red()/255,(double)color.green()/255,(double)color.blue()/255);
    }
    this->activeRenderWindow->Render();
}

void MainWindow::initFilter(int index)
{
    switch(index)
    {
    case 0:
    {
        break;
    }
    case 1:
    {
        this->shrinkFilter->SetShrinkFactor(0.3);
        this->shrinkFilter->Update();
        break;
    }
    case 2:
    {
        vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New();
        planeLeft->SetOrigin(0.0, 0.0, 0.0);
        planeLeft->SetNormal(-1.0, 0.0, 0.0);
        this->clipFilter->SetClipFunction( planeLeft.Get() );
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
    case 6:
    {
        break;
    }
    }
}

void MainWindow::handleFilter(int index)
{
    switch(index)
    {
    case 0:
    {
        break;
    }
    case 1:
    {
        this->activeFilters[1] = ui->shrinkCheck->isChecked();
        break;
    }
    case 2:
    {
        this->activeFilters[2] = ui->clipCheck->isChecked();
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
    case 6:
    {
        break;
    }
    }

    if(this->objectType>2){
        for(int i = 0;i<this->uGrids.size();i++){
            this->actors[i]->SetMapper(mapperStage(this->uGrids[i]));
        }
    }
    else{
        if (this->objectType == 0){
            this->actors[0]->SetMapper(mapperStage(this->activeReader->GetOutputPort()));
        }
        if(this->objectType==1){
            vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
            this->actors[0]->SetMapper(mapperStage(cubeSource->GetOutputPort()));
        }
    }
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
    connect(ui->lightSlider, SIGNAL(valueChanged(int)), this, SLOT(changeLight(int)));
    ui->lightSlider->setMinimum(0);
    ui->lightSlider->setMaximum(100);
//check boxes
    connect(ui->shrinkCheck, SIGNAL(stateChanged(int)), this, SLOT(handleFilter(1)));
    connect(ui->clipCheck, SIGNAL(stateChanged(int)), this, SLOT(handleFilter(2)));

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

// creator
    ui->qvtkWidget->SetRenderWindow( this->activeRenderWindow );

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
