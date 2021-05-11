// mainwindow.cpp-----------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::refreshGUI()
{

    this->appHandler->getPipeline()->getObject()->setMinActiveCell(1);
    this->appHandler->getPipeline()->getObject()->setMaxActiveCell(1);

    this->appHandler->getPipeline()->enableWireframe(0);
    this->appHandler->getPipeline()->enablePoints(0);

    this->appHandler->getPipeline()->enableClipX(0);
    this->appHandler->getPipeline()->enableClipY(0);
    this->appHandler->getPipeline()->enableClipZ(0);

    this->appHandler->getPipeline()->setShrinkFactor(0);
    this->appHandler->getPipeline()->setClipPart(0);

    ui->sphereFilterRad->setValue(0);
    ui->tubeFilterRad->setValue(0);

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
    ui->sphereCheck->setCheckState(Qt::Unchecked);
    ui->tubeCheck->setCheckState(Qt::Unchecked);
    ui->lightCheck->setCheckState(Qt::Unchecked);
    ui->curveCheck->setCheckState(Qt::Unchecked);

    ui->clipX->setCheckState(Qt::Unchecked);
    ui->clipY->setCheckState(Qt::Unchecked);
    ui->clipZ->setCheckState(Qt::Unchecked);
    ui->clipSlider->setValue(0);
    ui->clipNumBox->setValue(0);

    ui->showInfo->setChecked(Qt::Unchecked);
    ui->actionDirectionAxes->setChecked(Qt::Unchecked);
    ui->actionCubeAxes->setChecked(Qt::Unchecked);
    ui->showNormals->setChecked(Qt::Unchecked);
    ui->actionAffine->setChecked(Qt::Unchecked);

    ui->lightCheck->setCheckState(Qt::Unchecked);


    ui->lightIntensitySlider->setValue(0);
    ui->lightSpecularSlider->setValue(0);

    ui->lightIntensityNumBox->setValue(0);
    ui->lightSpecularNumBox->setValue(0);

    ui->objOpacitySlider->setValue(1);
    ui->objOpacityNumBox->setValue(1.0);

    ui->solidRadioB->toggle();

    this->allowGUIChange = 1;

}

void MainWindow::refreshObjectGUI()
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

    ui->sphereFilterRad->setValue(0);
    ui->tubeFilterRad->setValue(0);

    this->allowGUIChange = 0;

    ui->cellMinShow->setRange(1, 1);
    ui->cellMaxShow->setRange(1, 1);
    ui->cellMinShow->setValue(1);
    ui->cellMaxShow->setValue(1);
    ui->shrinkCheck->setCheckState(Qt::Unchecked);
    ui->clipCheck->setCheckState(Qt::Unchecked);
    ui->smoothCheck->setCheckState(Qt::Unchecked);
    ui->sphereCheck->setCheckState(Qt::Unchecked);
    ui->tubeCheck->setCheckState(Qt::Unchecked);
    ui->lightCheck->setCheckState(Qt::Unchecked);
    ui->curveCheck->setCheckState(Qt::Unchecked);

    ui->clipX->setCheckState(Qt::Unchecked);
    ui->clipY->setCheckState(Qt::Unchecked);
    ui->clipZ->setCheckState(Qt::Unchecked);
    ui->clipSlider->setValue(0);
    ui->clipNumBox->setValue(0);

    ui->objOpacitySlider->setValue(1);
    ui->objOpacityNumBox->setValue(1.0);

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
    this->appHandler->viewNewObject();

}


void MainWindow::handleSaveModelButton()
{
    this->activeFileName = QFileDialog::getSaveFileName(this, tr("Save File"), "./untitled.png", tr("Types (*.stl *.mod)"));

    this->appHandler->getPipeline()->getObject()->saveModelToFile(this->activeFileName);
}

void MainWindow::handleSaveSceneButton()
{
    this->activeFileName = QFileDialog::getSaveFileName(this, tr("Save File"), "./untitled.png", tr("Types (*.stl *.png)"));

    this->appHandler->saveScene(this->activeFileName);
}

void MainWindow::setCameraOrientationPosX()
{
    this->appHandler->setCameraOrientationPosX();

}
void MainWindow::setCameraOrientationNegX()
{
    this->appHandler->setCameraOrientationNegX();

}
void MainWindow::setCameraOrientationPosY()
{
    this->appHandler->setCameraOrientationPosY();

}
void MainWindow::setCameraOrientationNegY()
{
    this->appHandler->setCameraOrientationNegY();

}
void MainWindow::setCameraOrientationPosZ()
{
    this->appHandler->setCameraOrientationPosZ();

}
void MainWindow::setCameraOrientationNegZ()
{
    this->appHandler->setCameraOrientationNegZ();

}
void MainWindow::setCameraOrientationPosShift()
{
    this->appHandler->setCameraOrientationPosShift();

}
void MainWindow::setCameraOrientationNegShift()
{
    this->appHandler->setCameraOrientationNegShift();

}
void MainWindow::setCameraOrientationPosRotate()
{
    this->appHandler->setCameraOrientationPosRotate();

}
void MainWindow::setCameraOrientationNegRotate()
{
    this->appHandler->setCameraOrientationNegRotate();

}

void MainWindow::resetViewer()
{
    this->refreshGUI();
    this->appHandler->resetViewer();

}

void MainWindow::resetObject()
{
    this->refreshObjectGUI();
    this->appHandler->resetObject();

}

void MainWindow::resetCamera()
{
    this->appHandler->resetCamera();

}
void MainWindow::changeBackgroundColor()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Pick a color",  QColorDialog::DontUseNativeDialog);

    this->appHandler->changeBackgroundColor(color);

}
void MainWindow::changeObjectColor()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Pick a color",  QColorDialog::DontUseNativeDialog);

    this->appHandler->getPipeline()->getObject()->changeColor(color);
    this->appHandler->updateViewer();

}
void MainWindow::resetObjectColor()
{
    this->appHandler->getPipeline()->getObject()->resetColor();
    this->appHandler->updateViewer();

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
    case 11:
    {
        this->appHandler->getPipeline()->getObject()->displayEarth();
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

}

void MainWindow::applyCurveFilter(){

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

    }
}

void MainWindow::handleFilterUpdate()
{
    std::vector<int> filtersInUse = {ui->shrinkCheck->isChecked(),ui->clipCheck->isChecked(),0,
    ui->smoothCheck->isChecked(),ui->sphereCheck->isChecked(),ui->tubeCheck->isChecked(),ui->curveCheck->isChecked()};
    this->appHandler->getPipeline()->setFilters(filtersInUse);
    this->appHandler->updateViewer();

}

void MainWindow::handleUpdate()
{
    if(this->allowGUIChange)
    {

        this->appHandler->getPipeline()->enableWireframe(ui->wireRadioB->isChecked());
        this->appHandler->getPipeline()->enablePoints(ui->pointsRadioB->isChecked());
        this->appHandler->getPipeline()->enableLight(ui->lightCheck->isChecked());

        this->appHandler->getPipeline()->enableClipX(ui->clipX->isChecked());
        this->appHandler->getPipeline()->enableClipY(ui->clipY->isChecked());
        this->appHandler->getPipeline()->enableClipZ(ui->clipZ->isChecked());

        this->appHandler->getPipeline()->setShrinkFactor(ui->shrinkFactor->value());
        this->appHandler->getPipeline()->setTubeRad(ui->tubeFilterRad->value());
        this->appHandler->getPipeline()->setSphereRad(ui->sphereFilterRad->value());

        this->appHandler->getPipeline()->setClipPart((double)ui->clipNumBox->value()/100);
        this->appHandler->getPipeline()->setLightIntensity((double)ui->lightIntensityNumBox->value()/100);
        this->appHandler->getPipeline()->setLightSpecular((double)ui->lightSpecularNumBox->value()/100);
        this->appHandler->getPipeline()->setOpacity(ui->objOpacityNumBox->value());

        this->allowGUIChange = 0;
        ui->clipSlider->setValue(ui->clipNumBox->value());
        ui->lightIntensitySlider->setValue(ui->lightIntensityNumBox->value());
        ui->lightSpecularSlider->setValue(ui->lightSpecularNumBox->value());
        ui->objOpacitySlider->setValue(ui->objOpacityNumBox->value()*100);
        this->allowGUIChange = 1;

        this->appHandler->enableInfo(ui->showInfo->isChecked());
        this->appHandler->enableAxes(ui->actionDirectionAxes->isChecked());
        this->appHandler->enableCubeAxes(ui->actionCubeAxes->isChecked());
        this->appHandler->enableNormals(ui->showNormals->isChecked());

        this->appHandler->enableAffineInteraction(ui->actionAffine->isChecked());

        this->appHandler->updateViewer();

    }
}

void MainWindow::handleSliderUpdate()
{
    if(this->allowGUIChange)
    {

        this->appHandler->getPipeline()->setClipPart((double)ui->clipSlider->value()/100);

        this->appHandler->getPipeline()->setLightIntensity((double)ui->lightIntensitySlider->value()/100);
        this->appHandler->getPipeline()->setLightSpecular((double)ui->lightSpecularSlider->value()/100);
        this->appHandler->getPipeline()->setOpacity((double)ui->objOpacitySlider->value()/100);

        this->allowGUIChange = 0;
            ui->clipNumBox->setValue(ui->clipSlider->value());
            ui->lightIntensityNumBox->setValue(ui->lightIntensitySlider->value());
            ui->lightSpecularNumBox->setValue(ui->lightSpecularSlider->value());
            ui->objOpacityNumBox->setValue((double)ui->objOpacitySlider->value()/100);
        this->allowGUIChange = 1;

        this->appHandler->updateViewer();

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
    connect( ui->actionSaveModel, &QAction::triggered, this, &MainWindow::handleSaveModelButton);
    connect( ui->actionSaveScene, &QAction::triggered, this, &MainWindow::handleSaveSceneButton);

    connect( ui->actionFullScreen, &QAction::triggered, this, &MainWindow::showFullScreen);
    connect( ui->actionBorderedScreen, &QAction::triggered, this, &MainWindow::showNormal);
    connect( ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    connect(ui->showInfo, SIGNAL(toggled(bool)), this, SLOT(handleUpdate()));
    connect(ui->actionDirectionAxes, SIGNAL(toggled(bool)), this, SLOT(handleUpdate()));
    connect(ui->actionCubeAxes, SIGNAL(toggled(bool)), this, SLOT(handleUpdate()));
    connect(ui->showNormals, SIGNAL(toggled(bool)), this, SLOT(handleUpdate()));

    connect( ui->actionResetViewer, &QAction::triggered, this, &MainWindow::resetViewer );
    connect( ui->actionResetObject, &QAction::triggered, this, &MainWindow::resetObject );
    connect( ui->actionResetCamera, &QAction::triggered, this, &MainWindow::resetCamera );
    connect( ui->actionResetObjColor, &QAction::triggered, this, &MainWindow::resetObjectColor );

    connect(ui->actionAffine, SIGNAL(toggled(bool)), this, SLOT(handleUpdate()));

    //buttons
    connect( ui->backgroundColor, &QPushButton::released, this, &MainWindow::changeBackgroundColor );
    connect( ui->objectColor, &QPushButton::released, this, &MainWindow::changeObjectColor );


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
    connect(ui->clipSlider, SIGNAL(valueChanged(int)), this, SLOT(handleSliderUpdate()));
    connect(ui->lightIntensitySlider, SIGNAL(valueChanged(int)), this, SLOT(handleSliderUpdate()));
    connect(ui->lightSpecularSlider, SIGNAL(valueChanged(int)), this, SLOT(handleSliderUpdate()));
    connect(ui->objOpacitySlider, SIGNAL(valueChanged(int)), this, SLOT(handleSliderUpdate()));

//check boxes
    connect(ui->shrinkCheck, SIGNAL(stateChanged(int)), this, SLOT(handleFilterUpdate()));
    connect(ui->clipCheck, SIGNAL(stateChanged(int)), this, SLOT(handleFilterUpdate()));
    connect(ui->smoothCheck, SIGNAL(stateChanged(int)), this, SLOT(handleFilterUpdate()));
    connect(ui->tubeCheck, SIGNAL(stateChanged(int)), this, SLOT(handleFilterUpdate()));
    connect(ui->sphereCheck, SIGNAL(stateChanged(int)), this, SLOT(handleFilterUpdate()));
    connect(ui->curveCheck, SIGNAL(stateChanged(int)), this, SLOT(applyCurveFilter()));

    connect(ui->clipX, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->clipY, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->clipZ, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));

    connect(ui->lightCheck, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));

//spin boxes
    connect(ui->shrinkFactor, SIGNAL(valueChanged(double)), this, SLOT(handleUpdate()));
    connect(ui->sphereFilterRad, SIGNAL(valueChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->tubeFilterRad, SIGNAL(valueChanged(int)), this, SLOT(handleUpdate()));

    connect(ui->cellMinShow, SIGNAL(valueChanged(int)), this, SLOT(handleMinCellChange()));
    connect(ui->cellMaxShow, SIGNAL(valueChanged(int)), this, SLOT(handleMaxCellChange()));

    connect(ui->clipNumBox, SIGNAL(valueChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->lightIntensityNumBox, SIGNAL(valueChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->lightSpecularNumBox, SIGNAL(valueChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->objOpacityNumBox, SIGNAL(valueChanged(double)), this, SLOT(handleUpdate()));

//radio buttons
    connect(ui->solidRadioB, SIGNAL(clicked()), this, SLOT(handleUpdate()));
    connect(ui->wireRadioB, SIGNAL(clicked()), this, SLOT(handleUpdate()));
    connect(ui->pointsRadioB, SIGNAL(clicked()), this, SLOT(handleUpdate()));

// creator

    this->appHandler->setup(ui->qvtkWidget->GetRenderWindow(), ui->qvtkWidget->GetRenderWindow()->GetInteractor());
    this->appHandler->resetViewer();
}
MainWindow::~MainWindow()
{
    delete ui;
}
// /mainwindow.cpp----------------------------------------------------------
