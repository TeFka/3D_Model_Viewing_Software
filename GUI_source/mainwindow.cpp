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

void MainWindow::filterStage()
{
    /*if(ui->shrinkCheck->isChecked())
    {
        if(ui->clipCheck->isChecked())
        {
            this->shrinkFilter->SetInputConnection(this->clipFilter->GetOutputPort());
        }
        else
        {
            if(this->objectType==0)
            {
                vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
                this->shrinkFilter->SetInputConnection( cubeSource->GetOutputPort() );
            }
            else if(this->objectType==1)
            {
                this->shrinkFilter->SetInputConnection(this->activeReader->GetOutputPort());
            }
            else
            {
                this->shrinkFilter->SetInputData(this->uGrid);
            }
        }
        this->initShrinkFilter();
        this->activeMapper->SetInputConnection( this->shrinkFilter->GetOutputPort() );
    }
    else
    {
        if(ui->clipCheck->isChecked())
        {
            handleClipFilter();
        }
        else
        {
            if(this->objectType==0)
            {
                vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
                this->activeMapper->SetInputConnection( cubeSource->GetOutputPort() );
            }
            else if(this->objectType==1)
            {
                this->activeMapper->SetInputConnection(this->activeReader->GetOutputPort());
            }
            else
            {
                this->activeMapper->SetInputData(this->uGrid);
            }
        }
    }*/
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
    vtkSmartPointer<vtkDataSetMapper> tempMapper = vtkSmartPointer<vtkDataSetMapper>::New();
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

    tempMapper->SetInputData(tempGrid);

    tempActor->SetMapper(tempMapper);
    tempActor->GetProperty()->EdgeVisibilityOn();

    tempActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );

    this->activeRenderer->AddActor(tempActor);

    //this->activeRenderWindow->AddRenderer(tempRenderer);
    this->uGrids.push_back(tempGrid);
    this->mappers.push_back(tempMapper);
    this->actors.push_back(tempActor);

    this->objectType = 2;
    this->refreshRender();
}

void MainWindow::displayTetrahedron()
{
    this->refreshGrid();
    vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkDataSetMapper> tempMapper = vtkSmartPointer<vtkDataSetMapper>::New();
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

    tempMapper->SetInputData(tempGrid);

    tempActor->SetMapper(tempMapper);
    tempActor->GetProperty()->EdgeVisibilityOn();

    tempActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );

    this->activeRenderer->AddActor(tempActor);

    //this->activeRenderWindow->AddRenderer(tempRenderer);
    this->uGrids.push_back(tempGrid);
    this->mappers.push_back(tempMapper);
    this->actors.push_back(tempActor);

    this->objectType = 2;
    this->refreshRender();
}

void MainWindow::displayPyramid()
{
    this->refreshGrid();
    vtkSmartPointer<vtkUnstructuredGrid> tempGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkDataSetMapper> tempMapper = vtkSmartPointer<vtkDataSetMapper>::New();
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

    tempMapper->SetInputData(tempGrid);

    tempActor->SetMapper(tempMapper);
    tempActor->GetProperty()->EdgeVisibilityOn();

    tempActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );

    this->activeRenderer->AddActor(tempActor);

    //this->activeRenderWindow->AddRenderer(tempRenderer);
    this->uGrids.push_back(tempGrid);
    this->mappers.push_back(tempMapper);
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
        if(ui->clipCheck->isChecked()||ui->shrinkCheck->isChecked())
        {
            if(ui->clipCheck->isChecked())
            {
                this->clipFilter->SetInputConnection( this->activeReader->GetOutputPort() ) ;
                this->initClipFilter();
            }
            if(ui->shrinkCheck->isChecked())
            {
                if(ui->clipCheck->isChecked())
                {
                    this->shrinkFilter->SetInputConnection(this->clipFilter->GetOutputPort());
                }
                else
                {
                    this->shrinkFilter->SetInputConnection(this->activeReader->GetOutputPort());
                }
                this->initShrinkFilter();
                tempMapper->SetInputConnection( this->shrinkFilter->GetOutputPort() );
            }
            else
            {
                tempMapper->SetInputConnection( this->clipFilter->GetOutputPort() );
            }
        }
        else
        {
            tempMapper->SetInputConnection( this->activeReader->GetOutputPort() );
        }
        tempActor->SetMapper(tempMapper);
        tempActor->GetProperty()->EdgeVisibilityOn();
        tempActor->GetProperty()->SetColor(this->activeColors->GetColor3d("Red").GetData());
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
            vtkSmartPointer<vtkDataSetMapper> tempMapper = vtkSmartPointer<vtkDataSetMapper>::New();
            vtkSmartPointer<vtkActor> tempActor = vtkSmartPointer<vtkActor>::New();
            //vtkSmartPointer<vtkRenderer> tempRenderer = vtkSmartPointer<vtkRenderer>::New();
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

            tempMapper->SetInputData(tempGrid);

            tempActor->SetMapper(tempMapper);
            tempActor->GetProperty()->EdgeVisibilityOn();

            Vector3D color = this->activeVTKModel.getMaterial(tempCell.getMaterialID()).getColor();
            tempActor->GetProperty()->SetColor(color.getx(),color.getx(),color.getx());

            this->activeRenderer->AddActor(tempActor);

            //this->activeRenderWindow->AddRenderer(tempRenderer);
            this->uGrids.push_back(tempGrid);
            this->mappers.push_back(tempMapper);
            this->actors.push_back(tempActor);
            //this->renderers.push_back(tempRenderer);
        }
        //render grid
        //this->activeMapper->SetInputData(this->uGrid);
    }
    this->refreshRender();
}

void MainWindow::changeLight(int newVal)
{
    emit statusUpdateMessage( QString("Light: ")+QString::number(newVal), 0 );
    this->activeLight->SetIntensity(((float)newVal/100));
    this->activeRenderWindow->Render();
}

void MainWindow::resetObject()
{
    this->refreshGrid();
    ui->shrinkCheck->setCheckState(Qt::Unchecked);
    ui->clipCheck->setCheckState(Qt::Unchecked);
    this->changeLight(100);

    vtkSmartPointer<vtkDataSetMapper> tempMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkActor> tempActor = vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
    tempMapper->SetInputConnection( cubeSource->GetOutputPort() );

    tempActor->SetMapper(tempMapper);
    tempActor->GetProperty()->EdgeVisibilityOn();
    tempActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );

    this->mappers.push_back(tempMapper);
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
    this->actors[0]->GetProperty()->SetColor((double)color.red()/255,(double)color.green()/255,(double)color.blue()/255);
    this->activeRenderWindow->Render();
}

void MainWindow::initShrinkFilter()
{
    shrinkFilter->SetShrinkFactor(0.3);
    shrinkFilter->Update();
}

void MainWindow::initClipFilter()
{
    vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New();
    planeLeft->SetOrigin(0.0, 0.0, 0.0);
    planeLeft->SetNormal(-1.0, 0.0, 0.0);
    clipFilter->SetClipFunction( planeLeft.Get() );
}

void MainWindow::handleShrinkFilter()
{
    /*if(ui->shrinkCheck->isChecked())
    {
        if(ui->clipCheck->isChecked())
        {
            this->shrinkFilter->SetInputConnection(this->clipFilter->GetOutputPort());
        }
        else
        {
            if(this->objectType==0)
            {
                vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
                this->shrinkFilter->SetInputConnection( cubeSource->GetOutputPort() );
            }
            else if(this->objectType==1)
            {
                this->shrinkFilter->SetInputConnection(this->activeReader->GetOutputPort());
            }
            else
            {
                this->shrinkFilter->SetInputData(this->uGrid);
            }
        }
        this->initShrinkFilter();
        this->activeMapper->SetInputConnection( this->shrinkFilter->GetOutputPort() );
    }
    else
    {
        if(ui->clipCheck->isChecked())
        {
            handleClipFilter();
        }
        else
        {
            if(this->objectType==0)
            {
                vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
                this->activeMapper->SetInputConnection( cubeSource->GetOutputPort() );
            }
            else if(this->objectType==1)
            {
                this->activeMapper->SetInputConnection(this->activeReader->GetOutputPort());
            }
            else
            {
                this->activeMapper->SetInputData(this->uGrid);
            }
        }
    }
    this->refreshRender();*/
}

void MainWindow::handleClipFilter()
{
    /*if(ui->clipCheck->isChecked())
    {
        if(ui->shrinkCheck->isChecked())
        {
            this->clipFilter->SetInputConnection(this->shrinkFilter->GetOutputPort());
        }
        else
        {
            if(this->objectType==0)
            {
                vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
                this->clipFilter->SetInputConnection( cubeSource->GetOutputPort() );
            }
            else if(this->objectType==1)
            {
                this->clipFilter->SetInputConnection(this->activeReader->GetOutputPort());
            }
            else
            {
                this->clipFilter->SetInputData(this->uGrid);
            }
        }
        this->initClipFilter();
        this->activeMapper->SetInputConnection( this->clipFilter->GetOutputPort() );
    }
    else
    {
        if(ui->shrinkCheck->isChecked())
        {
            handleShrinkFilter();
        }
        else
        {
            if(this->objectType==0)
            {
                vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
                this->activeMapper->SetInputConnection( cubeSource->GetOutputPort() );
            }
            else if(this->objectType==1)
            {
                this->activeMapper->SetInputConnection(this->activeReader->GetOutputPort());
            }
            else
            {
                this->activeMapper->SetInputData(this->uGrid);
            }
        }
    }
    this->refreshRender();*/
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
    connect( ui->resetObject, &QPushButton::released, this, &MainWindow::resetObject );
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
    connect(ui->shrinkCheck, SIGNAL(stateChanged(int)), this, SLOT(handleShrinkFilter()));
    connect(ui->clipCheck, SIGNAL(stateChanged(int)), this, SLOT(handleClipFilter()));

//set VTK variables
    this->activeLight->SetLightTypeToSceneLight();
    this->activeLight->SetPosition( 5, 5, 150 );
    this->activeLight->SetPositional( true );
    this->activeLight->SetConeAngle( 10 );
    this->activeLight->SetFocalPoint( 0, 0, 0 );
    this->activeLight->SetDiffuseColor( 1, 1, 1 );
    this->activeLight->SetAmbientColor( 1, 1, 1 );
    this->activeLight->SetSpecularColor( 1, 1, 1 );
    this->activeLight->SetIntensity( 1.0 );

// note that vtkWidget is the name I gave to my QtVTKOpenGLWidget in Qt
// creator
    ui->qvtkWidget->SetRenderWindow( this->activeRenderWindow );
// ###### We've already created the renderWindow this time as a qt
// widget ######
//vtkSmartPointer<vtkRenderWindow> renderWindow =
// vtkSmartPointer<vtkRenderWindow>::New();
    this->activeRenderWindow = ui->qvtkWidget->GetRenderWindow();

    this->activeRenderWindow->AddRenderer( this->activeRenderer );

    this->resetObject();

    this->activeRenderer->AddLight(this->activeLight);
    this->activeRenderer->LightFollowCameraOn();
}
MainWindow::~MainWindow()
{
    delete ui;
}
// /mainwindow.cpp----------------------------------------------------------
