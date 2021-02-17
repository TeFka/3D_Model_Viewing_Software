// mainwindow.cpp-----------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::refreshRender(){
	this->activeRenderer->ResetCamera();
    this->activeRenderer->ResetCameraClippingRange();

    this->activeRenderWindow->Render();
}

void MainWindow::drawHexahedron()
{

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
        this->points->InsertNextPoint(pointCoordinates[i].data());
        hex->GetPointIds()->SetId(i, i);
    }
    this->cells->InsertNextCell(hex);
    this->uGrid->SetPoints(this->points);
    this->uGrid->InsertNextCell(hex->GetCellType(), hex->GetPointIds());
}

void MainWindow::drawTetrahedron()
{
    this->pointCoordinates.push_back({{0.0, 0.0, 0.0}}); // Face 1
    this->pointCoordinates.push_back({{1.0, 0.0, 0.0}});
    this->pointCoordinates.push_back({{1.0, 1.0, 0.0}});
    this->pointCoordinates.push_back({{0.0, 1.0, 1.0}});

    // Create a hexahedron from the points.
    vtkSmartPointer<vtkTetra> tetr = vtkSmartPointer<vtkTetra>::New();

    for (auto i = 0; i < this->pointCoordinates.size(); ++i)
    {
        this->points->InsertNextPoint(pointCoordinates[i].data());
        tetr->GetPointIds()->SetId(i, i);
    }
    this->cells->InsertNextCell(tetr);
    this->uGrid->SetPoints(this->points);
    this->uGrid->InsertNextCell(tetr->GetCellType(), tetr->GetPointIds());
}

void MainWindow::drawPyramid()
{
    this->pointCoordinates.push_back({{1.0, 1.0, 1.0}}); // Face 1
    this->pointCoordinates.push_back({{-1.0, 1.0, 1.0}});
    this->pointCoordinates.push_back({{-1.0, -1.0, 1.0}});
    this->pointCoordinates.push_back({{1.0, -1.0, 1.0}});
    this->pointCoordinates.push_back({{0.0, 0.0, 0.0}}); // Face 2

    // Create a hexahedron from the points.
    vtkSmartPointer<vtkPyramid> pyr = vtkSmartPointer<vtkPyramid>::New();

    for (auto i = 0; i < this->pointCoordinates.size(); ++i)
    {
        this->points->InsertNextPoint(pointCoordinates[i].data());
        pyr->GetPointIds()->SetId(i, i);
    }
    this->cells->InsertNextCell(pyr);
    this->uGrid->SetPoints(this->points);
    this->uGrid->InsertNextCell(pyr->GetCellType(), pyr->GetPointIds());
}

void MainWindow::displayHexahedron()
{
    this->pointCoordinates.clear();
    this->points->Reset();
    this->points->Squeeze();
    this->cells->Reset();
    this->cells->Squeeze();
    this->uGrid->Reset();
    this->uGrid->Squeeze();
    drawHexahedron();
    this->objectType = 2;
    if(ui->clipCheck->isChecked()||ui->shrinkCheck->isChecked())
    {
        if(ui->clipCheck->isChecked())
        {
            this->clipFilter->SetInputData(this->uGrid);
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
                this->shrinkFilter->SetInputData(this->uGrid);;
            }
            this->initShrinkFilter();
            this->activeMapper->SetInputConnection( this->shrinkFilter->GetOutputPort() );
        }
        else
        {
            this->activeMapper->SetInputConnection( this->clipFilter->GetOutputPort() );
        }
    }
    else
    {
        this->activeMapper->SetInputData(this->uGrid);
    }
    this->refreshRender();
}

void MainWindow::displayTetrahedron()
{
    this->pointCoordinates.clear();
    this->points->Reset();
    this->points->Squeeze();
    this->cells->Reset();
    this->cells->Squeeze();
    this->uGrid->Reset();
    this->uGrid->Squeeze();
    drawTetrahedron();
    this->objectType = 2;
    if(ui->clipCheck->isChecked()||ui->shrinkCheck->isChecked())
    {
        if(ui->clipCheck->isChecked())
        {
            this->clipFilter->SetInputData(this->uGrid);
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
                this->shrinkFilter->SetInputData(this->uGrid);;
            }
            this->initShrinkFilter();
            this->activeMapper->SetInputConnection( this->shrinkFilter->GetOutputPort() );
        }
        else
        {
            this->activeMapper->SetInputConnection( this->clipFilter->GetOutputPort() );
        }
    }
    else
    {
        this->activeMapper->SetInputData(this->uGrid);
    }
    this->refreshRender();
}

void MainWindow::displayPyramid()
{
    this->pointCoordinates.clear();
    this->points->Reset();
    this->points->Squeeze();
    this->cells->Reset();
    this->cells->Squeeze();
    this->uGrid->Reset();
    this->uGrid->Squeeze();
    drawPyramid();
    this->objectType = 2;
    if(ui->clipCheck->isChecked()||ui->shrinkCheck->isChecked())
    {
        if(ui->clipCheck->isChecked())
        {
            this->clipFilter->SetInputData(this->uGrid);
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
                this->shrinkFilter->SetInputData(this->uGrid);;
            }
            this->initShrinkFilter();
            this->activeMapper->SetInputConnection( this->shrinkFilter->GetOutputPort() );
        }
        else
        {
            this->activeMapper->SetInputConnection( this->clipFilter->GetOutputPort() );
        }
    }
    else
    {
        this->activeMapper->SetInputData(this->uGrid);
    }
    this->refreshRender();
}

//Function of class Mainwindow, handleOpenButton()
//Function to get specified model file
// Arguments for handleOpenButton(): none(file chosen using getSaveFileName() function)
// return value: none (file is opened)
void MainWindow::handleOpenButton()
{
    this->activeFileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "./", tr("STL Files(*.stl)"));
    emit statusUpdateMessage( QString("Loaded: ")+this->activeFileName, 0 );
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
            this->activeMapper->SetInputConnection( this->shrinkFilter->GetOutputPort() );
        }
        else
        {
            this->activeMapper->SetInputConnection( this->clipFilter->GetOutputPort() );
        }
    }
    else
    {
        this->activeMapper->SetInputConnection( this->activeReader->GetOutputPort() );
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
    ui->shrinkCheck->setCheckState(Qt::Unchecked);
    ui->clipCheck->setCheckState(Qt::Unchecked);
    this->changeLight(100);
    vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
    this->activeMapper->SetInputConnection( cubeSource->GetOutputPort() );
    this->activeRenderWindow->Render();
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
    this->activeActor->GetProperty()->SetColor((double)color.red()/255,(double)color.green()/255,(double)color.blue()/255);
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
    if(ui->shrinkCheck->isChecked())
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
    this->refreshRender();
}

void MainWindow::handleClipFilter()
{
    if(ui->clipCheck->isChecked())
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
    ui->qvtkWidget->SetRenderWindow( this->renderWindow );

// Create a mapper that will hold the cube's geometry in a format
// suitable for rendering

// Create a cube using a vtkCubeSource
    vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
    this->activeMapper->SetInputConnection( cubeSource->GetOutputPort() );

// Create an actor that is used to set the cube's properties for rendering
// and place it in the window
    this->activeActor->SetMapper(this->activeMapper);
    this->activeActor->GetProperty()->EdgeVisibilityOn();
    this->activeActor->GetProperty()->SetColor( this->activeColors->GetColor3d("Red").GetData() );
// ###### We've already created the renderWindow this time as a qt
// widget ######
//vtkSmartPointer<vtkRenderWindow> renderWindow =
// vtkSmartPointer<vtkRenderWindow>::New();
    this->activeRenderWindow = ui->qvtkWidget->GetRenderWindow();

    this->activeRenderWindow->AddRenderer( this->activeRenderer );

    this->activeRenderer->AddActor(this->activeActor);
    this->activeRenderer->SetBackground( this->activeColors->GetColor3d("Silver").GetData() );
// Setup the renderers's camera
    this->activeRenderer->GetActiveCamera()->Azimuth(30);
    this->activeRenderer->GetActiveCamera()->Elevation(30);
    this->refreshRender();

    this->activeRenderer->AddLight(this->activeLight);

}
MainWindow::~MainWindow()
{
    delete ui;
}
// /mainwindow.cpp----------------------------------------------------------
