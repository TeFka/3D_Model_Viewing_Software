// mainwindow.cpp-----------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::refreshRender()
{
    this->activeRenderWindow->Render();
}

void MainWindow::refreshGUI()
{

    this->appHandler->getPipeline()->getObject()->setMinActiveCell(0);
    this->appHandler->getPipeline()->getObject()->setMaxActiveCell(0);

    this->appHandler->getPipeline()->enableWireframe(0);
    this->appHandler->getPipeline()->enablePoints(0);

    this->appHandler->getPipeline()->enableClipX(0);
    this->appHandler->getPipeline()->enableClipY(0);
    this->appHandler->getPipeline()->enableClipZ(0);

    this->appHandler->getPipeline()->setShrinkFactor(0);
    this->appHandler->getPipeline()->setClipPart(0);

    this->appHandler->enableInfo(0);
    this->appHandler->enableAxes(0);

    this->allowGUIChange = 0;

    ui->cellMinShow->setRange(1, 1);
    ui->cellMaxShow->setRange(1, 1);
    ui->cellMinShow->setValue(1);
    ui->cellMaxShow->setValue(1);
    ui->shrinkCheck->setCheckState(Qt::Unchecked);
    ui->clipCheck->setCheckState(Qt::Unchecked);
    ui->smoothCheck->setCheckState(Qt::Unchecked);
    ui->check2->setCheckState(Qt::Unchecked);
    ui->check3->setCheckState(Qt::Unchecked);
    ui->lightCheck->setCheckState(Qt::Unchecked);

    ui->clipX->setCheckState(Qt::Unchecked);
    ui->clipY->setCheckState(Qt::Unchecked);
    ui->clipZ->setCheckState(Qt::Unchecked);
    ui->clipSlider->setValue(0);

    ui->showInfo->setCheckState(Qt::Unchecked);
    ui->showAxes->setCheckState(Qt::Unchecked);
    ui->lightCheck->setCheckState(Qt::Unchecked);
    ui->lightIntensity->setValue(100);

    ui->solidRadioB->toggle();

    this->allowGUIChange = 1;

}

//Function of class Mainwindow, handleOpenButton()
//Function to get specified model file
// Arguments for handleOpenButton(): none(file chosen using getSaveFileName() function)
// return value: none (file is opened)
void MainWindow::handleOpenButton()
{
    this->refreshGUI();
    this->activeFileName = QFileDialog::getOpenFileName(this, tr("Open File"), "./", tr("Files(*.stl *.mod)"));
    this->appHandler->getPipeline()->getObject()->getModelFromFile(this->activeFileName);

    this->allowGUIChange = 0;
    ui->cellMinShow->setRange(this->appHandler->getPipeline()->getObject()->getMinActiveCell(), this->appHandler->getPipeline()->getObject()->getMaxActiveCell());
    ui->cellMaxShow->setRange(this->appHandler->getPipeline()->getObject()->getMinActiveCell(), this->appHandler->getPipeline()->getObject()->getMaxActiveCell());
    ui->cellMinShow->setValue(this->appHandler->getPipeline()->getObject()->getMinActiveCell());
    ui->cellMaxShow->setValue(this->appHandler->getPipeline()->getObject()->getMaxActiveCell());
    this->allowGUIChange = 1;
    std::cout<< ui->cellMinShow->value()<<"  "<<ui->cellMaxShow->value()<<std::endl;
    this->appHandler->viewNewObject();
    this->refreshRender();
}


void MainWindow::handleSaveButton()
{
    this->activeFileName = QFileDialog::getSaveFileName(this, tr("Save model (*.stl *.mod)"),"/theFile");

    this->appHandler->getPipeline()->getObject()->saveModelToFile(this->activeFileName);
}

void MainWindow::setCameraOrientationPosX()
{
    this->appHandler->setCameraOrientationPosX();
    this->refreshRender();
}
void MainWindow::setCameraOrientationNegX()
{
    this->appHandler->setCameraOrientationNegX();
    this->refreshRender();
}
void MainWindow::setCameraOrientationPosY()
{
    this->appHandler->setCameraOrientationPosY();
    this->refreshRender();
}
void MainWindow::setCameraOrientationNegY()
{
    this->appHandler->setCameraOrientationNegY();
    this->refreshRender();
}
void MainWindow::setCameraOrientationPosZ()
{
    this->appHandler->setCameraOrientationPosZ();
    this->refreshRender();
}
void MainWindow::setCameraOrientationNegZ()
{
    this->appHandler->setCameraOrientationNegZ();
    this->refreshRender();
}
void MainWindow::setCameraOrientationPosShift()
{
    this->appHandler->setCameraOrientationPosShift();
    this->refreshRender();
}
void MainWindow::setCameraOrientationNegShift()
{
    this->appHandler->setCameraOrientationNegShift();
    this->refreshRender();
}
void MainWindow::setCameraOrientationPosRotate()
{
    this->appHandler->setCameraOrientationPosRotate();
    this->refreshRender();
}
void MainWindow::setCameraOrientationNegRotate()
{
    this->appHandler->setCameraOrientationNegRotate();
    this->refreshRender();
}

void MainWindow::resetViewer()
{
    this->refreshGUI();
    this->appHandler->resetViewer();
    this->refreshRender();
}

void MainWindow::resetObject()
{
    this->refreshGUI();
    this->appHandler->resetObject();
    this->refreshRender();
}

void MainWindow::resetCamera()
{
    this->appHandler->resetCamera();
    this->refreshRender();
}
void MainWindow::changeBackgroundColor()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Pick a color",  QColorDialog::DontUseNativeDialog);

    this->appHandler->changeBackgroundColor(color);
    this->refreshRender();
}
void MainWindow::changeObjectColor()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Pick a color",  QColorDialog::DontUseNativeDialog);

    this->appHandler->getPipeline()->getObject()->changeColor(color);
    this->appHandler->updateViewer();
    this->refreshRender();
}
void MainWindow::resetObjectColor()
{
    this->appHandler->getPipeline()->getObject()->resetColor();
    this->appHandler->updateViewer();
    this->refreshRender();
}


void MainWindow::handleHelpButton()
{
    AppHelp helpWindow;
    helpWindow.runHelp();
}

void MainWindow::handleNewButton()
{
    this->refreshGUI();
    int chosenShape = 0;
    NewShapeChoice choiceWindow;
    choiceWindow.runChoice(chosenShape);
    switch(chosenShape)
    {
    case 1:
    {
        this->appHandler->getPipeline()->getObject()->displayHexahedron();
        break;
    }
    case 2:
    {
        this->appHandler->getPipeline()->getObject()->displayTetrahedron();
        break;
    }
    case 3:
    {
        this->appHandler->getPipeline()->getObject()->displayPyramid();
        break;
    }
    case 4:
    {
        this->appHandler->getPipeline()->getObject()->displaySphere();
        break;
    }
    case 5:
    {
        this->appHandler->getPipeline()->getObject()->displayDisk();
        break;
    }
    case 6:
    {
        this->appHandler->getPipeline()->getObject()->displayCone();
        break;
    }
    case 7:
    {
        this->appHandler->getPipeline()->getObject()->displayPlane();
        break;
    }
    case 8:
    {
        this->appHandler->getPipeline()->getObject()->displayPointCluster(500);
        break;
    }
    case 9:
    {
        this->appHandler->getPipeline()->getObject()->displayLine();
        break;
    }
    case 10:
    {
        this->appHandler->getPipeline()->getObject()->displayCylinder();
        break;
    }
    }

    this->allowGUIChange = 0;
    ui->cellMinShow->setRange(1, 1);
    ui->cellMaxShow->setRange(1, 1);
    ui->cellMinShow->setValue(1);
    ui->cellMaxShow->setValue(1);
    this->allowGUIChange = 1;

    this->appHandler->viewNewObject();
    this->refreshRender();
}

void MainWindow::handleMinCellChange()
{
    if(this->allowGUIChange)
    {
        if(ui->cellMinShow->value()>ui->cellMaxShow->value())
        {
            ui->cellMinShow->setValue(ui->cellMaxShow->value());
        }
        this->appHandler->getPipeline()->getObject()->setMinActiveCell(ui->cellMinShow->value());
        this->appHandler->getPipeline()->getObject()->setMaxActiveCell(ui->cellMaxShow->value());

        this->appHandler->updateViewer();
        this->refreshRender();
    }
}

void MainWindow::handleMaxCellChange()
{
    if(this->allowGUIChange)
    {
        if(ui->cellMaxShow->value()<ui->cellMinShow->value())
        {
            ui->cellMaxShow->setValue(ui->cellMinShow->value());
        }
        this->appHandler->getPipeline()->getObject()->setMinActiveCell(ui->cellMinShow->value());
        this->appHandler->getPipeline()->getObject()->setMaxActiveCell(ui->cellMaxShow->value());

        this->appHandler->updateViewer();
        this->refreshRender();
    }
}

void MainWindow::handleFilterUpdate()
{
    std::vector<int> filtersInUse = {ui->shrinkCheck->isChecked(),ui->clipCheck->isChecked(),ui->contourCheck->isChecked(),ui->smoothCheck->isChecked(),0,0};
    this->appHandler->getPipeline()->setFilters(filtersInUse);
    this->appHandler->updateViewer();
    this->refreshRender();

}

void MainWindow::handleUpdate()
{
    if(this->allowGUIChange)
    {

        this->appHandler->getPipeline()->enableWireframe(ui->wireRadioB->isChecked());
        this->appHandler->getPipeline()->enablePoints(ui->pointsRadioB->isChecked());

        this->appHandler->getPipeline()->enableClipX(ui->clipX->isChecked());
        this->appHandler->getPipeline()->enableClipY(ui->clipY->isChecked());
        this->appHandler->getPipeline()->enableClipZ(ui->clipZ->isChecked());

        this->appHandler->getPipeline()->setShrinkFactor(ui->shrinkFactor->value());
        this->appHandler->getPipeline()->setClipPart(ui->clipSlider->value());

        this->appHandler->enableInfo(ui->showInfo->isChecked());
        this->appHandler->enableAxes(ui->showAxes->isChecked());

        this->appHandler->updateViewer();
        this->refreshRender();
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
    connect( ui->actionSave, &QAction::triggered, this, &MainWindow::handleSaveButton);
    connect( ui->actionFullScreen, &QAction::triggered, this, &MainWindow::showFullScreen);
    connect( ui->actionBorderedScreen, &QAction::triggered, this, &MainWindow::showNormal);
    connect( ui->actionExit, &QAction::triggered, this, &MainWindow::close);


    connect( ui->resetViewer, &QPushButton::released, this, &MainWindow::resetViewer );
    connect( ui->resetCamera, &QPushButton::released, this, &MainWindow::resetCamera );
    connect( ui->backgroundColor, &QPushButton::released, this, &MainWindow::changeBackgroundColor );
    connect( ui->objectColor, &QPushButton::released, this, &MainWindow::changeObjectColor );
    connect( ui->resetObjColor, &QPushButton::released, this, &MainWindow::resetObjectColor );

    //camera
    connect( ui->orientationXPos, &QPushButton::released, this, &MainWindow:: setCameraOrientationPosX);
    connect( ui->orientationXNeg, &QPushButton::released, this, &MainWindow::setCameraOrientationNegX );
    connect( ui->orientationYPos, &QPushButton::released, this, &MainWindow:: setCameraOrientationPosY);
    connect( ui->orientationYNeg, &QPushButton::released, this, &MainWindow::setCameraOrientationNegY);
    connect( ui->orientationZPos, &QPushButton::released, this, &MainWindow:: setCameraOrientationPosZ);
    connect( ui->orientationZNeg, &QPushButton::released, this, &MainWindow::setCameraOrientationNegZ );
    connect( ui->shift90Pos, &QPushButton::released, this, &MainWindow:: setCameraOrientationPosShift);
    connect( ui->shift90Neg, &QPushButton::released, this, &MainWindow::setCameraOrientationNegShift );
    connect( ui->rotat90Pos, &QPushButton::released, this, &MainWindow:: setCameraOrientationPosRotate);
    connect( ui->rotat90Neg, &QPushButton::released, this, &MainWindow::setCameraOrientationNegRotate );

//slider control
    connect(ui->clipSlider, SIGNAL(valueChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->lightIntensity, SIGNAL(valueChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->lightSpecular, SIGNAL(valueChanged(int)), this, SLOT(handleUpdate()));

//check boxes
    connect(ui->shrinkCheck, SIGNAL(stateChanged(int)), this, SLOT(handleFilterUpdate()));
    connect(ui->clipCheck, SIGNAL(stateChanged(int)), this, SLOT(handleFilterUpdate()));
    connect(ui->contourCheck, SIGNAL(stateChanged(int)), this, SLOT(handleFilterUpdate()));

    connect(ui->clipX, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->clipY, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->clipZ, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));

    connect(ui->showInfo, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->showAxes, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->lightCheck, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));

//spin boxes
    connect(ui->shrinkFactor, SIGNAL(valueChanged(double)), this, SLOT(handleUpdate()));

    connect(ui->cellMinShow, SIGNAL(valueChanged(int)), this, SLOT(handleMinCellChange()));
    connect(ui->cellMaxShow, SIGNAL(valueChanged(int)), this, SLOT(handleMaxCellChange()));

//radio buttons
    connect(ui->solidRadioB, SIGNAL(clicked()), this, SLOT(handleUpdate()));
    connect(ui->wireRadioB, SIGNAL(clicked()), this, SLOT(handleUpdate()));
    connect(ui->pointsRadioB, SIGNAL(clicked()), this, SLOT(handleUpdate()));

// creator

    ui->qvtkWidget->SetRenderWindow( this->renderWindow );

    this->appHandler->setup(ui->qvtkWidget->GetRenderWindow());
    this->appHandler->resetViewer();
}
MainWindow::~MainWindow()
{
    delete ui;
}
// /mainwindow.cpp----------------------------------------------------------
