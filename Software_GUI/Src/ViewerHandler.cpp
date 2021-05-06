
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
    this->pointsTextActor->SetInput ("");
    this->pointsTextActor->SetPosition ( 10, 90 );
    this->pointsTextActor->GetTextProperty()->SetFontSize ( 15 );
    this->pointsTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
    this->activeRenderer->AddActor2D ( this->pointsTextActor );

    this->volumeTextActor->SetInput ("");
    this->volumeTextActor->SetPosition ( 10, 70 );
    this->volumeTextActor->GetTextProperty()->SetFontSize ( 15 );
    this->volumeTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
    this->activeRenderer->AddActor2D ( this->volumeTextActor );

    this->maxCellNumTextActor->SetInput ("");
    this->maxCellNumTextActor->SetPosition ( 10, 50 );
    this->maxCellNumTextActor->GetTextProperty()->SetFontSize ( 15 );
    this->maxCellNumTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
    this->activeRenderer->AddActor2D ( this->maxCellNumTextActor );

    this->weightTextActor->SetInput ("");
    this->weightTextActor->SetPosition ( 10, 30 );
    this->weightTextActor->GetTextProperty()->SetFontSize ( 15 );
    this->weightTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
    this->activeRenderer->AddActor2D ( this->weightTextActor );

    this->positionTextActor->SetInput ("");
    this->positionTextActor->SetPosition ( 10, 10 );
    this->positionTextActor->GetTextProperty()->SetFontSize ( 15 );
    this->positionTextActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
    this->activeRenderer->AddActor2D ( this->positionTextActor );
}

void ViewerHandler::updateText()
{
    if(this->showInfo)
    {
        this->pointsTextActor->SetInput (("Points: "+std::to_string(this->thePipeline->getObject()->getPoints()->GetNumberOfPoints())).data());

        if(this->thePipeline->getObject()->getVolume()<0.00001)
        {
            this->volumeTextActor->SetInput (("Volume: "+std::to_string(this->thePipeline->getObject()->getVolume()*1000000)+"cm3").data());
        }
        else
        {
            this->volumeTextActor->SetInput (("Volume: "+std::to_string(this->thePipeline->getObject()->getVolume())+"m3").data());
        }

        this->maxCellNumTextActor->SetInput (("Max Cells: "+std::to_string(this->thePipeline->getObject()->getCellAmount())).data());

        if(this->thePipeline->getObject()->getWeight()<0.001)
        {
            this->weightTextActor->SetInput (("Weight: "+std::to_string(this->thePipeline->getObject()->getWeight()*1000)+"g").data());
        }
        else
        {
            this->weightTextActor->SetInput (("Weight: "+std::to_string(this->thePipeline->getObject()->getWeight())+"kg").data());
        }

        Vector3D objPos;

        this->positionTextActor->SetInput (("Position: "+std::to_string(this->thePipeline->getObject()->getPosition().getx())+
                                                " "+std::to_string(this->thePipeline->getObject()->getPosition().gety())+
                                                " "+std::to_string(this->thePipeline->getObject()->getPosition().getz())).data());
    }
    else
    {
        this->volumeTextActor->SetInput ("");
        this->maxCellNumTextActor->SetInput ("");
        this->weightTextActor->SetInput ("");
        this->positionTextActor->SetInput ("");
        this->pointsTextActor->SetInput ("");
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

void ViewerHandler::resetObject()
{
    this->thePipeline->getObject()->resetColor();

    this->thePipeline->setNewPipeline();

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
