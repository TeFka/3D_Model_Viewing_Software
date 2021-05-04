
#include"../Inc/ViewerHandler.h"

ViewerHandler::ViewerHandler()
{
    this->setText();
}

ViewerHandler::ViewerHandler(vtkSmartPointer<vtkRenderWindow> renderWindow)
{
    this->setText();
    this->activeRenderWindow = renderWindow;
    this->activeRenderWindow->AddRenderer( this->activeRenderer );
    this->thePipeline->setRenderer(this->activeRenderer);
}

void ViewerHandler::setup(vtkSmartPointer<vtkRenderWindow> renderWindow)
{

    this->activeRenderWindow = renderWindow;
    this->activeRenderWindow->AddRenderer( this->activeRenderer );
    this->thePipeline->setRenderer(this->activeRenderer);
}

void ViewerHandler::refreshRender()
{
    this->activeRenderWindow->Render();
}

void ViewerHandler::setText()
{
    this->tempVolumeTextActor->SetInput ("");
    this->tempVolumeTextActor->SetPosition ( 10, 70 );
    this->tempVolumeTextActor->GetTextProperty()->SetFontSize ( 15 );
    this->tempVolumeTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
    this->activeRenderer->AddActor2D ( this->tempVolumeTextActor );

    this->tempMaxCellNumTextActor->SetInput ("");
    this->tempMaxCellNumTextActor->SetPosition ( 10, 50 );
    this->tempMaxCellNumTextActor->GetTextProperty()->SetFontSize ( 15 );
    this->tempMaxCellNumTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
    this->activeRenderer->AddActor2D ( this->tempMaxCellNumTextActor );

    this->tempWeightTextActor->SetInput ("");
    this->tempWeightTextActor->SetPosition ( 10, 30 );
    this->tempWeightTextActor->GetTextProperty()->SetFontSize ( 15 );
    this->tempWeightTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
    this->activeRenderer->AddActor2D ( this->tempWeightTextActor );

    this->tempPositionTextActor->SetInput ("");
    this->tempPositionTextActor->SetPosition ( 10, 10 );
    this->tempPositionTextActor->GetTextProperty()->SetFontSize ( 15 );
    this->tempPositionTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
    this->activeRenderer->AddActor2D ( this->tempPositionTextActor );
}

void ViewerHandler::updateText()
{
    if(this->showInfo)
    {
        if(this->thePipeline->getObject()->getVolume()<0.00001)
        {
            this->tempVolumeTextActor->SetInput (("Volume: "+std::to_string(this->thePipeline->getObject()->getVolume()*1000000)+"cm3").data());
        }
        else
        {
            this->tempVolumeTextActor->SetInput (("Volume: "+std::to_string(this->thePipeline->getObject()->getVolume())+"m3").data());
        }

        this->tempMaxCellNumTextActor->SetInput (("Max Cells: "+std::to_string(this->thePipeline->getObject()->getCellAmount())).data());

        if(this->thePipeline->getObject()->getWeight()<0.001)
        {
            this->tempWeightTextActor->SetInput (("Weight: "+std::to_string(this->thePipeline->getObject()->getWeight()*1000)+"g").data());
        }
        else
        {
            this->tempWeightTextActor->SetInput (("Weight: "+std::to_string(this->thePipeline->getObject()->getWeight())+"kg").data());
        }

        Vector3D objPos;

        this->tempPositionTextActor->SetInput (("Position: "+std::to_string(this->thePipeline->getObject()->getPosition().getx())+
                                                " "+std::to_string(this->thePipeline->getObject()->getPosition().gety())+
                                                " "+std::to_string(this->thePipeline->getObject()->getPosition().getz())).data());
    }
    else
    {
        this->tempVolumeTextActor->SetInput ("");
        this->tempMaxCellNumTextActor->SetInput ("");
        this->tempWeightTextActor->SetInput ("");
        this->tempPositionTextActor->SetInput ("");
    }
}

void ViewerHandler::updateAxes(double xOffset,double yOffset,double zOffset)
{
    if(this->showAxes)
    {
        if(this->axesExist){
        this->activeRenderer->RemoveActor(this->axes);
        }
        vtkSmartPointer<vtkTransform> uTransform = vtkSmartPointer<vtkTransform>::New();

        uTransform->Translate(this->thePipeline->getObject()->getPosition().getx()+(2*this->thePipeline->getObject()->getDimensionAverage()*xOffset),
                              this->thePipeline->getObject()->getPosition().gety()+(2*this->thePipeline->getObject()->getDimensionAverage()*yOffset),
                              this->thePipeline->getObject()->getPosition().getz()+(2*this->thePipeline->getObject()->getDimensionAverage()*zOffset));

        this->axes->SetUserTransform(uTransform);

        this->axes->SetTotalLength(this->thePipeline->getObject()->getDimensionAverage(),
                                   this->thePipeline->getObject()->getDimensionAverage(),
                                   this->thePipeline->getObject()->getDimensionAverage());
        this->activeRenderer->AddActor(this->axes);

        this->axesExist = 1;
    }
    else
    {
        if(this->axesExist){
        this->activeRenderer->RemoveActor(this->axes);
        this->axesExist = 0;
        }
    }
}

void ViewerHandler::viewNewObject(){

    QColor theColor;
    theColor.setRed(255);
    theColor.setGreen(0);
    theColor.setBlue(0);
    this->thePipeline->getObject()->setColor(theColor);

    this->activeRenderer->SetBackground( this->colorHandler->GetColor3d("Silver").GetData() );

    this->thePipeline->setNewPipeline();
    this->updateText();
    this->updateAxes();

    this->resetCamera();
    this->refreshRender();
}

void ViewerHandler::updateViewer()
{

    this->thePipeline->updatePipeline();

    this->updateText();
    this->updateAxes();
    this->refreshRender();
}

void ViewerHandler::resetViewer()
{
    QColor theColor;
    theColor.setRed(255);
    theColor.setGreen(0);
    theColor.setBlue(0);
    this->thePipeline->getObject()->setColor(theColor);

    this->thePipeline->getObject()->displayHexahedron();

    this->thePipeline->setNewPipeline();


    this->activeRenderer->SetBackground( this->colorHandler->GetColor3d("Silver").GetData() );

    this->resetCamera();
    this->refreshRender();
}

void ViewerHandler::resetCamera()
{
    this->activeRenderer->ResetCamera();
    this->activeRenderer->GetActiveCamera()->Azimuth(30);
    this->activeRenderer->GetActiveCamera()->Elevation(30);
    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

void ViewerHandler::setCameraOrientationPosX()
{
    this->activeRenderer->GetActiveCamera()->SetPosition(this->thePipeline->getObject()->getPosition().getx()+3*this->thePipeline->getObject()->getDimensionAverage(),
            this->thePipeline->getObject()->getPosition().gety(),
            this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetFocalPoint(this->thePipeline->getObject()->getPosition().getx(),this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetViewUp(this->thePipeline->getObject()->getPosition().getx(),this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());
    this->updateAxes(0.0,0.0,-1.0);

    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}
void ViewerHandler::setCameraOrientationNegX()
{
    this->activeRenderer->ResetCamera();
    this->activeRenderer->ResetCameraClippingRange();
    this->activeRenderer->GetActiveCamera()->SetPosition(this->thePipeline->getObject()->getPosition().getx()-3*this->thePipeline->getObject()->getDimensionAverage(),
            this->thePipeline->getObject()->getPosition().gety(),
            this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetFocalPoint(this->thePipeline->getObject()->getPosition().getx(),this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetViewUp(this->thePipeline->getObject()->getPosition().getx(),this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());
    this->updateAxes(0.0,0.0,1.0);

    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}
void ViewerHandler::setCameraOrientationPosY()
{
    this->activeRenderer->ResetCamera();
    this->activeRenderer->GetActiveCamera()->SetPosition(this->thePipeline->getObject()->getPosition().getx(),
            this->thePipeline->getObject()->getPosition().gety()+3*this->thePipeline->getObject()->getDimensionAverage(),
            this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetFocalPoint(this->thePipeline->getObject()->getPosition().getx(),this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetViewUp(1.0,this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());

    this->updateAxes(1.0,0.0,-1.0);

    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

void ViewerHandler::setCameraOrientationNegY()
{
    this->activeRenderer->ResetCamera();
    this->activeRenderer->GetActiveCamera()->SetPosition(this->thePipeline->getObject()->getPosition().getx(),
            this->thePipeline->getObject()->getPosition().gety()-3*this->thePipeline->getObject()->getDimensionAverage(),
            this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetFocalPoint(this->thePipeline->getObject()->getPosition().getx(),this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetViewUp(1.0,this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());

    this->updateAxes(-1.0,0.0,0.0);

    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}
void ViewerHandler::setCameraOrientationPosZ()
{
    this->activeRenderer->ResetCamera();
    this->activeRenderer->GetActiveCamera()->SetPosition(this->thePipeline->getObject()->getPosition().getx(),
            this->thePipeline->getObject()->getPosition().gety(),
            this->thePipeline->getObject()->getPosition().getz()+3*this->thePipeline->getObject()->getDimensionAverage());
    this->activeRenderer->GetActiveCamera()->SetFocalPoint(this->thePipeline->getObject()->getPosition().getx(),this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetViewUp(this->thePipeline->getObject()->getPosition().getx(),this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());
    this->updateAxes(1.0,0.0,1.0);

    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}
void ViewerHandler::setCameraOrientationNegZ()
{
    this->activeRenderer->ResetCamera();
    this->activeRenderer->GetActiveCamera()->SetPosition(this->thePipeline->getObject()->getPosition().getx(),
            this->thePipeline->getObject()->getPosition().gety(),
            this->thePipeline->getObject()->getPosition().getz()-3*this->thePipeline->getObject()->getDimensionAverage());
    this->activeRenderer->GetActiveCamera()->SetFocalPoint(this->thePipeline->getObject()->getPosition().getx(),this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());
    this->activeRenderer->GetActiveCamera()->SetViewUp(this->thePipeline->getObject()->getPosition().getx(),this->thePipeline->getObject()->getPosition().gety(),this->thePipeline->getObject()->getPosition().getz());
    this->updateAxes(-1.0,0.0,0.0);

    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

void ViewerHandler::setCameraOrientationPosShift()
{
    this->activeRenderer->GetActiveCamera()->Azimuth(90);
    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

void ViewerHandler::setCameraOrientationNegShift()
{
    this->activeRenderer->GetActiveCamera()->Azimuth(-90);
    this->activeRenderer->ResetCameraClippingRange();
    this->refreshRender();
}

void ViewerHandler::setCameraOrientationPosRotate()
{
    this->activeRenderer->GetActiveCamera()->Roll(-90.0);
    this->refreshRender();
}

void ViewerHandler::setCameraOrientationNegRotate()
{
    this->activeRenderer->GetActiveCamera()->Roll(90.0);
    this->refreshRender();
}

void ViewerHandler::changeBackgroundColor( QColor color)
{
    this->activeRenderer->SetBackground((double)color.red()/255,(double)color.green()/255,(double)color.blue()/255);
    this->refreshRender();
}

Pipeline* ViewerHandler::getPipeline()
{

    return this->thePipeline;
}

void ViewerHandler::enableInfo(int value)
{
    this->showInfo = value;
}
void ViewerHandler::enableAxes(int value)
{
    this->showAxes = value;
}
