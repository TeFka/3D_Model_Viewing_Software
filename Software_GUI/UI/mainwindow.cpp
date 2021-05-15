// mainwindow.cpp-----------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"

//function to refresh the GUI and set all values to default
void MainWindow::refreshGUI()
{

    //disable GUI change to prevent updates
    this->allowGUIChange = 0;

    //refresh cell counts
    ui->cellMinShow->setRange(1, 1);
    ui->cellMaxShow->setRange(1, 1);
    ui->cellMinShow->setValue(1);
    ui->cellMaxShow->setValue(1);

    //uncheck all boxes
    ui->shrinkCheck->setCheckState(Qt::Unchecked);
    ui->clipCheck->setCheckState(Qt::Unchecked);
    ui->smoothCheck->setCheckState(Qt::Unchecked);
    ui->sphereCheck->setCheckState(Qt::Unchecked);
    ui->tubeCheck->setCheckState(Qt::Unchecked);
    ui->lightCheck->setCheckState(Qt::Unchecked);
    ui->curveCheck->setCheckState(Qt::Unchecked);
    ui->outlineCheck->setCheckState(Qt::Unchecked);

    ui->clipX->setCheckState(Qt::Unchecked);
    ui->clipY->setCheckState(Qt::Unchecked);
    ui->clipZ->setCheckState(Qt::Unchecked);

    ui->showInfo->setChecked(Qt::Unchecked);
    ui->actionDirectionAxes->setChecked(Qt::Unchecked);
    ui->actionCubeAxes->setChecked(Qt::Unchecked);
    ui->showNormals->setChecked(Qt::Unchecked);
    ui->actionAffine->setChecked(Qt::Unchecked);

    ui->lightCheck->setCheckState(Qt::Unchecked);

    //reset UI values
    ui->clipSlider->setValue(0);
    ui->clipNumBox->setValue(0);

    ui->shrinkFactor->setValue(1.0);
    ui->sphereFilterRad->setValue(10);
    ui->tubeFilterRad->setValue(10);

    ui->lightIntensitySlider->setValue(0);
    ui->lightSpecularSlider->setValue(0);

    ui->lightIntensityNumBox->setValue(0);
    ui->lightSpecularNumBox->setValue(0);

    ui->objOpacitySlider->setValue(1);
    ui->objOpacityNumBox->setValue(1.0);

    ui->solidRadioB->toggle();

    //enable GUI change
    this->allowGUIChange = 1;
    emit statusUpdateMessage( QString("Refreshed GUI"), 0 );
}

//function to refresh all object modifications and set all values to default
void MainWindow::refreshObjectGUI()
{
    //disable GUI change to prevent updates
    this->allowGUIChange = 0;

    //uncheck all boxes
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

    //reset UI values
    ui->clipSlider->setValue(0);
    ui->clipNumBox->setValue(0);

    ui->objOpacitySlider->setValue(1);
    ui->objOpacityNumBox->setValue(1.0);

    ui->solidRadioB->toggle();

     //enable GUI change
    this->allowGUIChange = 1;
    emit statusUpdateMessage( QString("Refreshed object modifications"), 0 );
}

//Function to open specified model file
void MainWindow::handleOpenButton()
{
    //get file name
    this->activeFileName = QFileDialog::getOpenFileName(this, tr("Open File"), "./", tr("Files(*.stl *.mod)"));
    QFileInfo fi(this->activeFileName);

    //check if it is required format
    if(fi.suffix()=="stl"||fi.suffix()=="mod"){

    //reset viewer
    this->resetViewer();
    emit statusUpdateMessage( QString("Opening file: ")+this->activeFileName, 0 );

    //load the file using object handler
    this->appHandler->getPipeline()->getObject()->getModelFromFile(this->activeFileName);

    //update amount of cells
    this->allowGUIChange = 0;
    ui->cellMinShow->setRange(this->appHandler->getPipeline()->getObject()->getMinActiveCell(), this->appHandler->getPipeline()->getObject()->getMaxActiveCell());
    ui->cellMaxShow->setRange(this->appHandler->getPipeline()->getObject()->getMinActiveCell(), this->appHandler->getPipeline()->getObject()->getMaxActiveCell());
    ui->cellMinShow->setValue(this->appHandler->getPipeline()->getObject()->getMinActiveCell());
    ui->cellMaxShow->setValue(this->appHandler->getPipeline()->getObject()->getMaxActiveCell());
    this->allowGUIChange = 1;

    //set new pipeline
    this->appHandler->viewNewObject();
    }
}

//function to save object data to file
void MainWindow::handleSaveModelButton()
{
    //check if the object type can be saved as MOD file
    if(this->appHandler->getPipeline()->getObject()->getObjectType()==2||this->appHandler->getPipeline()->getObject()->getObjectType()==3){
    this->activeFileName = QFileDialog::getSaveFileName(this, tr("Save File"), "./untitled.stl", tr("Types (*.stl *.mod)"));
    }
    else{
        this->activeFileName = QFileDialog::getSaveFileName(this, tr("Save File"), "./untitled.stl", tr("Types (*.stl)"));
    }
    emit statusUpdateMessage( QString("Saving to file: ")+this->activeFileName, 0 );

    //save the object data using object handler
    this->appHandler->getPipeline()->getObject()->saveModelToFile(this->activeFileName);
}

//function to save photo of scene of object with effects
void MainWindow::handleSaveSceneButton()
{
    this->activeFileName = QFileDialog::getSaveFileName(this, tr("Save File"), "./untitled.png", tr("Types (*.stl *.png)"));
    emit statusUpdateMessage( QString("Saving to file: ")+this->activeFileName, 0 );

    //save scene data using viewer handler
    this->appHandler->saveScene(this->activeFileName);
}

//function to set camera orientation to positive X
void MainWindow::setCameraOrientationPosX()
{
    emit statusUpdateMessage( QString("Orienting camera to positive X axis"), 0 );
    this->appHandler->setCameraOrientationPosX();

}

//function to set camera orientation to negative X
void MainWindow::setCameraOrientationNegX()
{
    emit statusUpdateMessage( QString("Orienting camera to negative X axis"), 0 );
    this->appHandler->setCameraOrientationNegX();

}

//function to set camera orientation to positive Y
void MainWindow::setCameraOrientationPosY()
{
    emit statusUpdateMessage( QString("Orienting camera to positive Y axis"), 0 );
    this->appHandler->setCameraOrientationPosY();

}

//function to set camera orientation to negative Y
void MainWindow::setCameraOrientationNegY()
{
    emit statusUpdateMessage( QString("Orienting camera to negative Y axis"), 0 );
    this->appHandler->setCameraOrientationNegY();

}

//function to set camera orientation to positive Z
void MainWindow::setCameraOrientationPosZ()
{
    emit statusUpdateMessage( QString("Orienting camera to positive Z axis"), 0 );
    this->appHandler->setCameraOrientationPosZ();

}

//function to set camera orientation to negative Z
void MainWindow::setCameraOrientationNegZ()
{
    emit statusUpdateMessage( QString("Orienting camera to negative Z axis"), 0 );
    this->appHandler->setCameraOrientationNegZ();

}

//function to shift camera position by 90 degrees to the right
void MainWindow::setCameraOrientationPosShift()
{
    emit statusUpdateMessage( QString("Shifting Camera orientation to right"), 0 );
    this->appHandler->setCameraOrientationPosShift();

}

//function to shift camera position by 90 degrees to the right
void MainWindow::setCameraOrientationNegShift()
{
    emit statusUpdateMessage( QString("Shifting Camera orientation to left"), 0 );
    this->appHandler->setCameraOrientationNegShift();

}

//function to rotate camera by 90 degrees to the right
void MainWindow::setCameraOrientationPosRotate()
{
    emit statusUpdateMessage( QString("Rotating camera clockwise"), 0 );
    this->appHandler->setCameraOrientationPosRotate();

}

//function to rotate camera by 90 degrees to the right
void MainWindow::setCameraOrientationNegRotate()
{
    emit statusUpdateMessage( QString("Rotating camera anti-clockwise"), 0 );
    this->appHandler->setCameraOrientationNegRotate();

}

//function to reset viewer
void MainWindow::resetViewer()
{
    this->refreshGUI();
    this->appHandler->resetViewer();

}

//function to reset object
void MainWindow::resetObject()
{
    this->refreshObjectGUI();
    this->appHandler->resetObject();

}

//function to reset camera
void MainWindow::resetCamera()
{
    emit statusUpdateMessage( QString("Resetting camera"), 0 );
    this->appHandler->resetCamera();

}

//function to change backgroundcolor
void MainWindow::changeBackgroundColor()
{
    //pcik new color
    QColor color = QColorDialog::getColor(Qt::black, this, "Pick a color",  QColorDialog::DontUseNativeDialog);
    emit statusUpdateMessage( QString("Changing background color"), 0 );
    this->appHandler->changeBackgroundColor(color);

}

//function to change object color
void MainWindow::changeObjectColor()
{
    //pick new color
    QColor color = QColorDialog::getColor(Qt::black, this, "Pick a color",  QColorDialog::DontUseNativeDialog);
    emit statusUpdateMessage( QString("Changing object color"), 0 );
    this->appHandler->getPipeline()->getObject()->changeColor(color);
    this->appHandler->updateViewer();

}

//function to reset object color
void MainWindow::resetObjectColor()
{
    emit statusUpdateMessage( QString("Reseting object color"), 0 );
    this->appHandler->getPipeline()->getObject()->resetColor();
    this->appHandler->updateViewer();

}

//function to open help window
void MainWindow::handleHelpButton()
{
    AppHelp helpWindow;
    emit statusUpdateMessage( QString("Showing help"), 0 );
    helpWindow.runHelp();
}

//function to choose and load new object
void MainWindow::handleNewButton()
{
    int chosenShape = 0;
    NewShapeChoice choiceWindow;
    choiceWindow.runChoice(chosenShape);

    //check if a choice was made
    if(chosenShape>0){
        emit statusUpdateMessage( QString("Loading new object"), 0 );
        this->resetViewer();
    }

    //create object based on choice
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

    //update cell amount
    this->allowGUIChange = 0;
    ui->cellMinShow->setRange(1, 1);
    ui->cellMaxShow->setRange(1, 1);
    ui->cellMinShow->setValue(1);
    ui->cellMaxShow->setValue(1);
    this->allowGUIChange = 1;

    //set new object viewing
    this->appHandler->viewNewObject();

}

//function to apply cure filter
void MainWindow::applyCurveFilter(){
    this->handleFilterUpdate();
}

//function to set minimum cell to be shown
void MainWindow::handleMinCellChange()
{
    emit statusUpdateMessage( QString("Change smallest cell shown"), 0 );

    //check if update is allowed
    if(this->allowGUIChange)
    {
        //check if minimum cell is not more than maximum cell
        if(ui->cellMinShow->value()>ui->cellMaxShow->value())
        {
            ui->cellMinShow->setValue(ui->cellMaxShow->value());
        }
        this->appHandler->getPipeline()->getObject()->setMinActiveCell(ui->cellMinShow->value());
        this->appHandler->getPipeline()->getObject()->setMaxActiveCell(ui->cellMaxShow->value());

        this->appHandler->updateViewer();

    }
}

//function to set maximum cell to be shown
void MainWindow::handleMaxCellChange()
{
    emit statusUpdateMessage( QString("Change highest cell shown"), 0 );

    //check if update is allowed
    if(this->allowGUIChange)
    {
        //check if maximum cell is not less than maximum cell
        if(ui->cellMaxShow->value()<ui->cellMinShow->value())
        {
            ui->cellMaxShow->setValue(ui->cellMinShow->value());
        }
        this->appHandler->getPipeline()->getObject()->setMinActiveCell(ui->cellMinShow->value());
        this->appHandler->getPipeline()->getObject()->setMaxActiveCell(ui->cellMaxShow->value());

        this->appHandler->updateViewer();

    }
}

//function to set active filters in the pipeline
void MainWindow::handleFilterUpdate()
{
    emit statusUpdateMessage( QString("Update filters"), 0 );
    std::vector<int> filtersInUse = {ui->shrinkCheck->isChecked(),ui->clipCheck->isChecked(),0,
    ui->smoothCheck->isChecked(),ui->sphereCheck->isChecked(),ui->tubeCheck->isChecked(),0};
    this->appHandler->getPipeline()->setFilters(filtersInUse);
    this->appHandler->updateViewer();

}

//function to update software variables based on GUI choices
void MainWindow::handleUpdate()
{
    //check if update is allowed
    if(this->allowGUIChange)
    {
        emit statusUpdateMessage( QString("Update"), 0 );

        //set all variables based on GUI component values
        this->appHandler->getPipeline()->enableWireframe(ui->wireRadioB->isChecked());
        this->appHandler->getPipeline()->enablePoints(ui->pointsRadioB->isChecked());
        this->appHandler->getPipeline()->enableLight(ui->lightCheck->isChecked());

        this->appHandler->getPipeline()->enableClipX(ui->clipX->isChecked());
        this->appHandler->getPipeline()->enableClipY(ui->clipY->isChecked());
        this->appHandler->getPipeline()->enableClipZ(ui->clipZ->isChecked());

        this->appHandler->getPipeline()->enableScalarWarp(ui->scalarWarp->isChecked());

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
        this->appHandler->enableOutline(ui->outlineCheck->isChecked());

        this->appHandler->enableAffineInteraction(ui->actionAffine->isChecked());

        this->appHandler->updateViewer();

    }
}

//function to update system variables based on slider variables
void MainWindow::handleSliderUpdate()
{
    //check if update is allowed
    if(this->allowGUIChange)
    {
        emit statusUpdateMessage( QString("Update"), 0 );

        //set all variables based on GUI slider values
        this->appHandler->getPipeline()->setClipPart((double)ui->clipSlider->value()/100);

        this->appHandler->getPipeline()->setLightIntensity((double)ui->lightIntensitySlider->value()/100);
        this->appHandler->getPipeline()->setLightSpecular((double)ui->lightSpecularSlider->value()/100);
        this->appHandler->getPipeline()->setOpacity((double)ui->objOpacitySlider->value()/100);

        //update number boxes based on slider values
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

//Create connection to buttons
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
    connect(ui->outlineCheck, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));

    connect(ui->clipX, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->clipY, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));
    connect(ui->clipZ, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));

    connect(ui->lightCheck, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));

    connect(ui->scalarWarp, SIGNAL(stateChanged(int)), this, SLOT(handleUpdate()));

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

//message box
    connect( this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage );

// setup viewer
    this->appHandler->setup(ui->qvtkWidget->GetRenderWindow(), ui->qvtkWidget->GetRenderWindow()->GetInteractor());
    this->appHandler->resetViewer();
}
MainWindow::~MainWindow()
{
    delete ui;
}
// /mainwindow.cpp----------------------------------------------------------
