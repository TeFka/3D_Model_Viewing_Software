
#include"../Inc/ViewerHandler.h"

//setting up functions for affine mode operation
namespace
{
void vtkAffineCallback::Execute(vtkObject*, unsigned long vtkNotUsed(event),
                                void*)
{
    this->AffineRep->GetTransform(this->Transform);
    this->Actor->SetUserTransform(this->Transform);
}
} // namespace

//function to setup handler of mouse interactor for double clicking
void MouseInteractorStyleDoubleClick::setupHandler(ViewerHandler* hand)
{
    this->handler = hand;
}

//default constructor
ViewerHandler::ViewerHandler()
{
    //setup text operation
    this->setText();
}

//constructor
ViewerHandler::ViewerHandler(vtkSmartPointer<vtkRenderWindow> renderWindow, vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{
    //set render window and interactor
    this->activeRenderWindow = renderWindow;
    this->renderWindowInteractor = interactor;

    //setup other components
    this->setupComponents();

}

//function to setup viewer handler
void ViewerHandler::setup(vtkSmartPointer<vtkRenderWindow> renderWindow, vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{
    //set render window and interactor
    this->activeRenderWindow = renderWindow;
    this->renderWindowInteractor = interactor;

    //setup other components
    this->setupComponents();
}

//function to setup all components
void ViewerHandler::setupComponents()
{
    //setup text operation
    this->setText();

    //add renderer to render window
    this->activeRenderWindow->AddRenderer( this->activeRenderer );

    //assign renderer to pipeline
    this->thePipeline->setRenderer(this->activeRenderer);

    //setup light of pipeline
    this->thePipeline->setLight();

    //setup axes operation
    this->setAxes();

    //setup affine mode operation
    this->setAffineInteraction();

    //setup double clicking
    this->renderWindowInteractor->SetInteractorStyle(this->doubleClickInteratction);
    this->doubleClickInteratction->setupHandler(this);
}


//function to refresh rendering
void ViewerHandler::refreshRender()
{
    this->activeRenderWindow->Render();

}

//function to setup text operation
void ViewerHandler::setText()
{

    //setup parameters of text showing number of points
    this->pointsTextActor->SetInput ("");
    this->pointsTextActor->SetPosition ( 10, 110 );
    this->pointsTextActor->GetTextProperty()->SetFontSize ( 15 );
    this->pointsTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
    this->activeRenderer->AddActor2D ( this->pointsTextActor );

    //setup parameters of text showing object volume
    this->volumeTextActor->SetInput ("");
    this->volumeTextActor->SetPosition ( 10, 90 );
    this->volumeTextActor->GetTextProperty()->SetFontSize ( 15 );
    this->volumeTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
    this->activeRenderer->AddActor2D ( this->volumeTextActor );

    //setup parameters of text showing maximum number of cells
    this->maxCellNumTextActor->SetInput ("");
    this->maxCellNumTextActor->SetPosition ( 10, 70 );
    this->maxCellNumTextActor->GetTextProperty()->SetFontSize ( 15 );
    this->maxCellNumTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
    this->activeRenderer->AddActor2D ( this->maxCellNumTextActor );

    //setup parameters of text showing object weight
    this->weightTextActor->SetInput ("");
    this->weightTextActor->SetPosition ( 10, 50 );
    this->weightTextActor->GetTextProperty()->SetFontSize ( 15 );
    this->weightTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
    this->activeRenderer->AddActor2D ( this->weightTextActor );

    //setup parameters of text showing object position
    this->positionTextActor->SetInput ("");
    this->positionTextActor->SetPosition ( 10, 30 );
    this->positionTextActor->GetTextProperty()->SetFontSize ( 15 );
    this->positionTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
    this->activeRenderer->AddActor2D ( this->positionTextActor );

    //setup parameters of text showing object bounds
    this->boundTextActor->SetInput ("");
    this->boundTextActor->SetPosition ( 10, 10 );
    this->boundTextActor->GetTextProperty()->SetFontSize ( 15 );
    this->boundTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
    this->activeRenderer->AddActor2D ( this->boundTextActor );
}

//function to update shown text
void ViewerHandler::updateText()
{
    //check if text should be eshown
    if(this->showInfo)
    {
        //update value of text showing number of points
        this->pointsTextActor->SetInput (("Points: "+std::to_string(this->thePipeline->getObject()->getShownPointAmount())).data());

        //update value of text showing volume in m3 or cm3
        if(this->thePipeline->getObject()->getVolume()<0.00001)
        {
            this->volumeTextActor->SetInput (("Volume: "+std::to_string(this->thePipeline->getObject()->getVolume()*1000000)+"cm3").data());
        }
        else
        {
            this->volumeTextActor->SetInput (("Volume: "+std::to_string(this->thePipeline->getObject()->getVolume())+"m3").data());
        }

        //update value of text showing maximum number of cells
        this->maxCellNumTextActor->SetInput (("Max Cells: "+std::to_string(this->thePipeline->getObject()->getCellAmount())).data());

        //update value of text showing object weight in kg or g
        if(this->thePipeline->getObject()->getObjectType()==3)
        {
            if(this->thePipeline->getObject()->getWeight()<0.001)
            {
                this->weightTextActor->SetInput (("Weight: "+std::to_string(this->thePipeline->getObject()->getWeight()*1000)+"g").data());
            }
            else
            {
                this->weightTextActor->SetInput (("Weight: "+std::to_string(this->thePipeline->getObject()->getWeight())+"kg").data());
            }
        }
        else
        {
            this->weightTextActor->SetInput ("Weight: N/A");
        }

        //update value of text showing object position
        this->positionTextActor->SetInput (("Position: "+std::to_string(this->thePipeline->getObject()->getPosition().getx())+
                                            " "+std::to_string(this->thePipeline->getObject()->getPosition().gety())+
                                            " "+std::to_string(this->thePipeline->getObject()->getPosition().getz())).data());

        //update value of text showing object bounds
        this->boundTextActor->SetInput (("Bounds Dimensions: "+std::to_string(this->thePipeline->getObject()->getDimensions().getx())+
                                            " "+std::to_string(this->thePipeline->getObject()->getDimensions().gety())+
                                            " "+std::to_string(this->thePipeline->getObject()->getDimensions().getz())).data());
    }
    else
    {
        //set all text as empty
        this->volumeTextActor->SetInput ("");
        this->maxCellNumTextActor->SetInput ("");
        this->weightTextActor->SetInput ("");
        this->positionTextActor->SetInput ("");
        this->boundTextActor->SetInput ("");
        this->pointsTextActor->SetInput ("");
    }
}

//function to setup direction axes operation
void ViewerHandler::setAxes()
{
    double rgba[4] {0.0, 0.0, 0.0, 0.0};
    this->colorHandler->GetColor("Green", rgba);

    //set directional axes widget parameters
    this->axesWidget->SetOutlineColor(rgba[0], rgba[1], rgba[2]);
    this->axesWidget->SetOrientationMarker(this->axesActor);
    this->axesWidget->SetInteractor(this->renderWindowInteractor);
    this->axesWidget->SetViewport(0.0, 0.0, 0.4, 0.4);
    this->axesWidget->SetEnabled(0);
    this->axesWidget->InteractiveOn();
}

//function to setup cube axes operation
void ViewerHandler::updateCubeAxes()
{
    //check if cube axes should be shown
    if(this->showCubeAxes)
    {
        //refresh cube axes actor if it exists
        if(this->cubeAxesExist)
        {
            this->activeRenderer->RemoveActor(this->cubeAxesActor);
        }

        //set cube axes actor parameters
        this->cubeAxesActor->SetUseTextActor3D(1);
        this->cubeAxesActor->SetBounds(this->thePipeline->getObject()->getPolydata()->GetBounds());
        this->cubeAxesActor->SetCamera(this->activeRenderer->GetActiveCamera());

        //set color of each axis
        this->cubeAxesActor->GetTitleTextProperty(0)->SetColor(this->colorHandler->GetColor3d("Red").GetData());
        this->cubeAxesActor->GetTitleTextProperty(0)->SetFontSize(48);
        this->cubeAxesActor->GetLabelTextProperty(0)->SetColor(this->colorHandler->GetColor3d("Red").GetData());

        this->cubeAxesActor->GetTitleTextProperty(1)->SetColor(this->colorHandler->GetColor3d("Green").GetData());
        this->cubeAxesActor->GetLabelTextProperty(1)->SetColor(this->colorHandler->GetColor3d("green").GetData());

        this->cubeAxesActor->GetTitleTextProperty(2)->SetColor(this->colorHandler->GetColor3d("Blue").GetData());
        this->cubeAxesActor->GetLabelTextProperty(2)->SetColor(this->colorHandler->GetColor3d("Blue").GetData());

        //draw grid lines of all axes
        this->cubeAxesActor->DrawXGridlinesOn();
        this->cubeAxesActor->DrawYGridlinesOn();
        this->cubeAxesActor->DrawZGridlinesOn();
#if VTK_MAJOR_VERSION == 6
        this->cubeAxesActor->SetGridLineLocation(VTK_GRID_LINES_FURTHEST);
#endif
#if VTK_MAJOR_VERSION > 6
        this->cubeAxesActor->SetGridLineLocation(this->cubeAxesActor->VTK_GRID_LINES_FURTHEST);
#endif

        //turn off minor ticks
        this->cubeAxesActor->XAxisMinorTickVisibilityOff();
        this->cubeAxesActor->YAxisMinorTickVisibilityOff();
        this->cubeAxesActor->ZAxisMinorTickVisibilityOff();

        this->cubeAxesActor->SetFlyModeToStaticEdges();

        //add actor to renderer
        this->activeRenderer->AddActor(this->cubeAxesActor);
        this->cubeAxesExist = 1;
    }
    else
    {
        //remove actor if it should not be shown
        if(this->cubeAxesExist)
        {
            this->activeRenderer->RemoveActor(this->cubeAxesActor);
            this->cubeAxesExist = 0;
        }
    }
}

//function to update normals of object surface
void ViewerHandler::updateNormals()
{
    //check if normals should be shown
    if(this->showNormals)
    {
        //refresh normals actor if it exists
        if(this->normalsExist)
        {
            this->activeRenderer->RemoveActor(this->normalsActor);
        }

        //set normals parameters
        vtkNew<vtkPCANormalEstimation> normals;
        normals->SetInputConnection(this->thePipeline->getAlgorithm());
        normals->SetSampleSize(10);
        normals->SetNormalOrientationToGraphTraversal();
        normals->Update();


        vtkNew<vtkGlyph3D> glyph3D;

        // Source for the glyph filter
        vtkNew<vtkArrowSource> arrow;
        arrow->SetTipResolution(16);
        arrow->SetTipLength(0.3);
        arrow->SetTipRadius(0.1);

        //set arrow glyph parameters
        glyph3D->SetSourceConnection(arrow->GetOutputPort());
        glyph3D->SetInputData(normals->GetOutput());
        glyph3D->SetVectorModeToUseNormal();
        glyph3D->SetScaleModeToScaleByVector();
        glyph3D->SetScaleFactor(this->thePipeline->getObject()->getDimensionAverage()/2);
        glyph3D->OrientOn();
        glyph3D->Update();

        //set polydata
        vtkNew<vtkPolyDataMapper> glyph3DMapper;
        glyph3DMapper->SetInputConnection(glyph3D->GetOutputPort());

        this->normalsActor->SetMapper(glyph3DMapper);
        this->normalsActor->GetProperty()->SetDiffuseColor(
            colorHandler->GetColor3d("red").GetData());

        //add actor to renderer
        this->activeRenderer->AddActor(this->normalsActor);

        this->normalsExist = 1;
    }
    else
    {
        //remove actor if it should not be shown
        if(this->normalsExist)
        {
            this->activeRenderer->RemoveActor(this->normalsActor);
            this->normalsExist = 0;
        }
    }

}

//function to stup affine mode operation
void ViewerHandler::setAffineInteraction()
{
    //setup affine widget
    this->affineWidget->SetInteractor(this->renderWindowInteractor);
    this->affineWidget->CreateDefaultRepresentation();
    dynamic_cast<vtkAffineRepresentation2D*>(this->affineWidget->GetRepresentation())
    ->PlaceWidget(this->thePipeline->getActor()->GetBounds());

    //setup affine calback
    this->affineCallback->Actor = this->thePipeline->getActor();
    this->affineCallback->AffineRep = dynamic_cast<vtkAffineRepresentation2D*>(
                                          this->affineWidget->GetRepresentation());

    //add observers
    this->affineWidget->AddObserver(vtkCommand::InteractionEvent, this->affineCallback);
    this->affineWidget->AddObserver(vtkCommand::EndInteractionEvent, this->affineCallback);
}

//function to handle updates from affine mode
void ViewerHandler::updateAffineInteraction()
{
    dynamic_cast<vtkAffineRepresentation2D*>(this->affineWidget->GetRepresentation())
    ->PlaceWidget(this->thePipeline->getActor()->GetBounds());

    //update affine callback
    this->affineCallback->Actor = this->thePipeline->getActor();
    this->affineCallback->AffineRep = dynamic_cast<vtkAffineRepresentation2D*>(
                                          this->affineWidget->GetRepresentation());
}

//function to update outline of object
void ViewerHandler::updateOutline()
{
    // Create the outline
    if(this->showOutline)
    {
        if(this->outlineExist){
        this->activeRenderer->RemoveActor(this->outlineActor);
        }
        this->outline->SetInputConnection(this->thePipeline->getAlgorithm());

        vtkSmartPointer<vtkDataSetMapper> tempMapper = vtkSmartPointer<vtkDataSetMapper>::New();
        tempMapper->SetInputConnection(this->outline->GetOutputPort());

        this->outlineActor->SetMapper(tempMapper);

        QColor color = this->thePipeline->getObject()->getColor();
        this->outlineActor->GetProperty()->SetColor((double)color.red()/255,(double)color.green()/255,(double)color.blue()/255);

        this->activeRenderer->AddActor(this->outlineActor);
        this->outlineExist = 1;
    }
    else{
        if(this->outlineExist){
            this->activeRenderer->RemoveActor(this->outlineActor);
            this->outlineExist = 0;
        }
    }
}

//function to handle setup and viewing of new object
void ViewerHandler::viewNewObject()
{
    //set default color
    QColor theColor;
    theColor.setRed(255);
    theColor.setGreen(0);
    theColor.setBlue(0);
    this->thePipeline->getObject()->setColor(theColor);

    //reset background
    this->activeRenderer->SetBackground( this->colorHandler->GetColor3d("Silver").GetData() );

    // set new pipeline
    this->thePipeline->setNewPipeline();

    //update text
    this->updateText();

    //update affine mode
    this->updateAffineInteraction();
    this->resetCamera();
    this->refreshRender();
}

//function to update all additions of the scene
void ViewerHandler::updateComponents()
{
    this->updateText();
    this->updateNormals();
    this->updateCubeAxes();
    this->updateOutline();
}

//function to update viewer
void ViewerHandler::updateViewer()
{
    //update all aspects
    this->thePipeline->updatePipeline();
    this->updateComponents();
    this->refreshRender();
}

//function to reset viewer
void ViewerHandler::resetViewer()
{

//set cell amount to default
    this->thePipeline->getObject()->setMinActiveCell(1);
    this->thePipeline->getObject()->setMaxActiveCell(1);

//set values of all aspects to default
    this->thePipeline->enableWireframe(0);
    this->thePipeline->enablePoints(0);

    this->thePipeline->enableClipX(0);
    this->thePipeline->enableClipY(0);
    this->thePipeline->enableClipZ(0);

    this->thePipeline->setShrinkFactor(1.0);
    this->thePipeline->setClipPart(0);

    this->thePipeline->setTubeRad(10);
    this->thePipeline->setTubeSides(3);
    this->thePipeline->setSphereRad(10);

    this->thePipeline->getObject()->enableSurfaceWarp(0);
    this->thePipeline->getObject()->enableBendWarp(0);

    this->thePipeline->getObject()->setSurfaceWarpFactor(0);
    this->thePipeline->getObject()->setBendWarpFactor(0);
    this->thePipeline->getObject()->setBendWarpDimensions(1,1,1);

    this->showInfo = 0;
    this->showAxes = 0;
    this->showCubeAxes = 0;
    this->showNormals = 0;
    this->showOutline = 0;

    std::vector<int> filtersInUse = {0,0,0,0,0,0,0};
    this->thePipeline->setFilters(filtersInUse);

//set deault colors
    QColor theColor;
    theColor.setRed(255);
    theColor.setGreen(0);
    theColor.setBlue(0);
    this->thePipeline->getObject()->setColor(theColor);

    this->activeRenderer->SetBackground( this->colorHandler->GetColor3d("Silver").GetData() );

//display hexahedron
    this->thePipeline->getObject()->displayHexahedron();

//set new pipeline
    this->thePipeline->setNewPipeline();

//set new affine interaction
    this->setAffineInteraction();

//update pipeline to add changes
    this->updateViewer();

    this->resetCamera();
    this->refreshRender();
}

//function to reset just the object properties
void ViewerHandler::resetObject()
{

    //set all object properties to default values
    this->thePipeline->getObject()->setMinActiveCell(1);
    this->thePipeline->getObject()->setMaxActiveCell(1);

    this->thePipeline->enableWireframe(0);
    this->thePipeline->enablePoints(0);

    this->thePipeline->enableClipX(0);
    this->thePipeline->enableClipY(0);
    this->thePipeline->enableClipZ(0);

    this->thePipeline->setShrinkFactor(1.0);
    this->thePipeline->setClipPart(0);

    this->thePipeline->setTubeRad(10);
    this->thePipeline->setTubeSides(3);
    this->thePipeline->setSphereRad(10);

    this->thePipeline->getObject()->enableSurfaceWarp(0);
    this->thePipeline->getObject()->enableBendWarp(0);

    this->thePipeline->getObject()->setSurfaceWarpFactor(0);
    this->thePipeline->getObject()->setBendWarpFactor(0);
    this->thePipeline->getObject()->setBendWarpDimensions(1,1,1);

    std::vector<int> filtersInUse = {0,0,0,0,0,0,0};
    this->thePipeline->setFilters(filtersInUse);
    this->thePipeline->getObject()->resetColor();

    //set new pipeline
    this->thePipeline->setNewPipeline();

    this->refreshRender();
}

//function to reset camera
void ViewerHandler::resetCamera()
{
    //set all camera parameters to default
    this->activeRenderer->ResetCamera();
    this->activeRenderer->GetActiveCamera()->Azimuth(30);
    this->activeRenderer->GetActiveCamera()->Elevation(30);
    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

//function to set camera orientation to positive X
void ViewerHandler::setCameraOrientationPosX()
{
    //set new camera position and direction properties based on object
    this->activeRenderer->GetActiveCamera()->SetPosition(this->thePipeline->getObject()->getPosition().getx()-3*this->thePipeline->getObject()->getDimensionAverage(),
            this->thePipeline->getObject()->getPosition().gety(),
            this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetFocalPoint(this->thePipeline->getObject()->getPosition().getx(),this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetViewUp(this->thePipeline->getObject()->getPosition().getx(),1.0,this->thePipeline->getObject()->getPosition().getz());

    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

//function to set camera orientation to negative X
void ViewerHandler::setCameraOrientationNegX()
{
    //set new camera position and direction properties based on object
    this->activeRenderer->ResetCamera();
    this->activeRenderer->ResetCameraClippingRange();
    this->activeRenderer->GetActiveCamera()->SetPosition(this->thePipeline->getObject()->getPosition().getx()+3*this->thePipeline->getObject()->getDimensionAverage(),
            this->thePipeline->getObject()->getPosition().gety(),
            this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetFocalPoint(this->thePipeline->getObject()->getPosition().getx(),this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetViewUp(this->thePipeline->getObject()->getPosition().getx(),1.0,this->thePipeline->getObject()->getPosition().getz());

    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

//function to set camera orientation to positive Y
void ViewerHandler::setCameraOrientationPosY()
{
    //set new camera position and direction properties based on object
    this->activeRenderer->ResetCamera();
    this->activeRenderer->GetActiveCamera()->SetPosition(this->thePipeline->getObject()->getPosition().getx(),
            this->thePipeline->getObject()->getPosition().gety()-3*this->thePipeline->getObject()->getDimensionAverage(),
            this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetFocalPoint(this->thePipeline->getObject()->getPosition().getx(),this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetViewUp(1.0,this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());

    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

//function to set camera orientation to negative Y
void ViewerHandler::setCameraOrientationNegY()
{
    //set new camera position and direction properties based on object
    this->activeRenderer->ResetCamera();
    this->activeRenderer->GetActiveCamera()->SetPosition(this->thePipeline->getObject()->getPosition().getx(),
            this->thePipeline->getObject()->getPosition().gety()+3*this->thePipeline->getObject()->getDimensionAverage(),
            this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetFocalPoint(this->thePipeline->getObject()->getPosition().getx(),this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetViewUp(1.0,this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());

    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

//function to set camera orientation to positive Z
void ViewerHandler::setCameraOrientationPosZ()
{
    //set new camera position and direction properties based on object
    this->activeRenderer->ResetCamera();
    this->activeRenderer->GetActiveCamera()->SetPosition(this->thePipeline->getObject()->getPosition().getx(),
            this->thePipeline->getObject()->getPosition().gety(),
            this->thePipeline->getObject()->getPosition().getz()-3*this->thePipeline->getObject()->getDimensionAverage());
    this->activeRenderer->GetActiveCamera()->SetFocalPoint(this->thePipeline->getObject()->getPosition().getx(),this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetViewUp(this->thePipeline->getObject()->getPosition().getx(),1.0,this->thePipeline->getObject()->getPosition().getz());

    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

//function to set camera orientation to negative Z
void ViewerHandler::setCameraOrientationNegZ()
{
    //set new camera position and direction properties based on object
    this->activeRenderer->ResetCamera();
    this->activeRenderer->GetActiveCamera()->SetPosition(this->thePipeline->getObject()->getPosition().getx(),
            this->thePipeline->getObject()->getPosition().gety(),
            this->thePipeline->getObject()->getPosition().getz()+3*this->thePipeline->getObject()->getDimensionAverage());
    this->activeRenderer->GetActiveCamera()->SetFocalPoint(this->thePipeline->getObject()->getPosition().getx(),this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetViewUp(this->thePipeline->getObject()->getPosition().getx(),1.0,this->thePipeline->getObject()->getPosition().getz());

    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

//function to shift camera position by 90 degrees to the right
void ViewerHandler::setCameraOrientationPosShift()
{
    this->activeRenderer->GetActiveCamera()->Azimuth(90);
    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

//function to shift camera position by 90 degrees to the right
void ViewerHandler::setCameraOrientationNegShift()
{
    this->activeRenderer->GetActiveCamera()->Azimuth(-90);
    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

//function to rotate camera by 90 degrees to the right
void ViewerHandler::setCameraOrientationPosRotate()
{
    this->activeRenderer->GetActiveCamera()->Roll(-90.0);
    this->refreshRender();
}

//function to rotate camera by 90 degrees to the right
void ViewerHandler::setCameraOrientationNegRotate()
{
    this->activeRenderer->GetActiveCamera()->Roll(90.0);
    this->refreshRender();
}

//function to change background color
void ViewerHandler::changeBackgroundColor( QColor color)
{
    this->activeRenderer->SetBackground((double)color.red()/255,(double)color.green()/255,(double)color.blue()/255);
    this->refreshRender();
}

//function to get active pipeline
Pipeline* ViewerHandler::getPipeline()
{

    return this->thePipeline;
}

//function to allow showing of information text
void ViewerHandler::enableInfo(int value)
{
    this->showInfo = value;
}

//function to allow showing of direction
void ViewerHandler::enableAxes(int value)
{
    this->axesWidget->SetEnabled(value);
}

//function to allow showing of object normals
void ViewerHandler::enableNormals(int value)
{
    this->showNormals = value;
}

//function to allow showing of cube axes
void ViewerHandler::enableCubeAxes(int value)
{
    this->showCubeAxes = value;
}

//function to allow showing outline
void ViewerHandler::enableOutline(int value)
{
    this->showOutline = value;
}

//function to enable affine mode
void ViewerHandler::enableAffineInteraction(int value)
{
    if(value)
    {
        affineWidget->On();
    }
    else
    {
        affineWidget->Off();
    }
}

//function to save the scene as png photo or STL file
void ViewerHandler::saveScene(QString fileName)
{
    QFileInfo fi(fileName);

    if(fi.suffix()=="stl")
    {
        //save final algorithm of the scene as STL file
        this->stlWriter->SetFileName(fileName.toLocal8Bit().data());
        this->stlWriter->SetInputConnection(this->thePipeline->getAlgorithm());
        this->stlWriter->Write();
    }
    else if(fi.suffix()=="png")
    {
        //save scene as a png picture
        this->activeRenderWindow->Render();

        vtkNew<vtkWindowToImageFilter> windowToImageFilter;
        windowToImageFilter->SetInput(this->activeRenderWindow);
#if VTK_MAJOR_VERSION >= 8 || VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION >= 90
        windowToImageFilter->SetScale(2); // image quality
#else
        windowToImageFilter->SetMagnification(2); // image quality
#endif
        windowToImageFilter->SetInputBufferTypeToRGBA(); // also record the alpha
        // (transparency) channel
        windowToImageFilter->ReadFrontBufferOff();       // read from the back buffer
        windowToImageFilter->Update();

        vtkNew<vtkPNGWriter> writer;
        writer->SetFileName(fileName.toLocal8Bit().data());
        writer->SetInputConnection(windowToImageFilter->GetOutputPort());
        writer->Write();

        this->activeRenderer->ResetCamera();
        this->activeRenderWindow->Render();
    }
}

//function to handle mouse doubleclick
void ViewerHandler::mouseClick()
{
    std::cout<<"Clicked"<<std::endl;
}
