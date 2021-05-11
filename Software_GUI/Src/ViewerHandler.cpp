
#include"../Inc/ViewerHandler.h"

namespace {
void vtkAffineCallback::Execute(vtkObject*, unsigned long vtkNotUsed(event),
                                void*)
{
  this->AffineRep->GetTransform(this->Transform);
  this->Actor->SetUserTransform(this->Transform);
}
} // namespace


ViewerHandler::ViewerHandler()
{
    this->setText();
}

ViewerHandler::ViewerHandler(vtkSmartPointer<vtkRenderWindow> renderWindow, vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{

    this->activeRenderWindow = renderWindow;

    this->renderWindowInteractor = interactor;

    this->setupComponents();

}

void ViewerHandler::setup(vtkSmartPointer<vtkRenderWindow> renderWindow, vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{

    this->activeRenderWindow = renderWindow;

    this->renderWindowInteractor = interactor;

    this->setupComponents();
}

void ViewerHandler::setupComponents(){

    this->setText();
    this->activeRenderWindow->AddRenderer( this->activeRenderer );

    this->thePipeline->setRenderer(this->activeRenderer);
    this->thePipeline->setLight();

    this->setAxes();
    this->setAffineInteraction();
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
        this->pointsTextActor->SetInput (("Points: "+std::to_string(this->thePipeline->getObject()->getShownPointAmount())).data());

        if(this->thePipeline->getObject()->getVolume()<0.00001)
        {
            this->volumeTextActor->SetInput (("Volume: "+std::to_string(this->thePipeline->getObject()->getVolume()*1000000)+"cm3").data());
        }
        else
        {
            this->volumeTextActor->SetInput (("Volume: "+std::to_string(this->thePipeline->getObject()->getVolume())+"m3").data());
        }

        this->maxCellNumTextActor->SetInput (("Max Cells: "+std::to_string(this->thePipeline->getObject()->getCellAmount())).data());

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

//******************************* DO THIS
void ViewerHandler::setAxes()
{
    double rgba[4] {0.0, 0.0, 0.0, 0.0};
    this->colorHandler->GetColor("Green", rgba);
    this->axesWidget->SetOutlineColor(rgba[0], rgba[1], rgba[2]);
    this->axesWidget->SetOrientationMarker(this->axesActor);
    this->axesWidget->SetInteractor(this->renderWindowInteractor);
    this->axesWidget->SetViewport(0.0, 0.0, 0.4, 0.4);
    this->axesWidget->SetEnabled(0);
    this->axesWidget->InteractiveOn();
}

//******************************* DO THIS
void ViewerHandler::updateCubeAxes()
{
    if(this->showCubeAxes)
    {
        if(this->cubeAxesExist)
        {
            this->activeRenderer->RemoveActor(this->cubeAxesActor);
        }
        this->cubeAxesActor->SetUseTextActor3D(1);
        this->cubeAxesActor->SetBounds(this->thePipeline->getObject()->GetPolydata()->GetBounds());
        this->cubeAxesActor->SetCamera(this->activeRenderer->GetActiveCamera());
        this->cubeAxesActor->GetTitleTextProperty(0)->SetColor(this->colorHandler->GetColor3d("Red").GetData());
        this->cubeAxesActor->GetTitleTextProperty(0)->SetFontSize(48);
        this->cubeAxesActor->GetLabelTextProperty(0)->SetColor(this->colorHandler->GetColor3d("Red").GetData());

        this->cubeAxesActor->GetTitleTextProperty(1)->SetColor(this->colorHandler->GetColor3d("Green").GetData());
        this->cubeAxesActor->GetLabelTextProperty(1)->SetColor(this->colorHandler->GetColor3d("green").GetData());

        this->cubeAxesActor->GetTitleTextProperty(2)->SetColor(this->colorHandler->GetColor3d("Blue").GetData());
        this->cubeAxesActor->GetLabelTextProperty(2)->SetColor(this->colorHandler->GetColor3d("Blue").GetData());

        this->cubeAxesActor->DrawXGridlinesOn();
        this->cubeAxesActor->DrawYGridlinesOn();
        this->cubeAxesActor->DrawZGridlinesOn();
#if VTK_MAJOR_VERSION == 6
        this->cubeAxesActor->SetGridLineLocation(VTK_GRID_LINES_FURTHEST);
#endif
#if VTK_MAJOR_VERSION > 6
        this->cubeAxesActor->SetGridLineLocation(this->cubeAxesActor->VTK_GRID_LINES_FURTHEST);
#endif

        this->cubeAxesActor->XAxisMinorTickVisibilityOff();
        this->cubeAxesActor->YAxisMinorTickVisibilityOff();
        this->cubeAxesActor->ZAxisMinorTickVisibilityOff();

        this->cubeAxesActor->SetFlyModeToStaticEdges();
        this->activeRenderer->AddActor(this->cubeAxesActor);
        this->cubeAxesExist = 1;
    }
    else
    {
        if(this->cubeAxesExist)
        {
            this->activeRenderer->RemoveActor(this->cubeAxesActor);
            this->cubeAxesExist = 0;
        }
    }
}
void ViewerHandler::updateNormals()
{

    if(this->showNormals)
    {
        if(this->normalsExist)
        {
            this->activeRenderer->RemoveActor(this->normalsActor);
        }
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

        glyph3D->SetSourceConnection(arrow->GetOutputPort());
        glyph3D->SetInputData(normals->GetOutput());
        glyph3D->SetVectorModeToUseNormal();
        glyph3D->SetScaleModeToScaleByVector();
        glyph3D->SetScaleFactor(this->thePipeline->getObject()->getDimensionAverage()/2);
        glyph3D->OrientOn();
        glyph3D->Update();

        vtkNew<vtkPolyDataMapper> glyph3DMapper;
        glyph3DMapper->SetInputConnection(glyph3D->GetOutputPort());

        this->normalsActor->SetMapper(glyph3DMapper);
        this->normalsActor->GetProperty()->SetDiffuseColor(
            colorHandler->GetColor3d("red").GetData());

        this->activeRenderer->AddActor(this->normalsActor);

        this->normalsExist = 1;
    }
    else
    {
        if(this->normalsExist)
        {
            this->activeRenderer->RemoveActor(this->normalsActor);
            this->normalsExist = 0;
        }
    }

}

void ViewerHandler::setAffineInteraction()
{
    this->affineWidget->SetInteractor(this->renderWindowInteractor);
    this->affineWidget->CreateDefaultRepresentation();
    dynamic_cast<vtkAffineRepresentation2D*>(this->affineWidget->GetRepresentation())
    ->PlaceWidget(this->thePipeline->getActor()->GetBounds());

    this->affineCallback->Actor = this->thePipeline->getActor();
    this->affineCallback->AffineRep = dynamic_cast<vtkAffineRepresentation2D*>(
                                    this->affineWidget->GetRepresentation());

    this->affineWidget->AddObserver(vtkCommand::InteractionEvent, this->affineCallback);
    this->affineWidget->AddObserver(vtkCommand::EndInteractionEvent, this->affineCallback);
}

void ViewerHandler::updateAffineInteraction(){
    dynamic_cast<vtkAffineRepresentation2D*>(this->affineWidget->GetRepresentation())
    ->PlaceWidget(this->thePipeline->getActor()->GetBounds());

    this->affineCallback->Actor = this->thePipeline->getActor();
    this->affineCallback->AffineRep = dynamic_cast<vtkAffineRepresentation2D*>(
                                    this->affineWidget->GetRepresentation());
}

void ViewerHandler::viewNewObject()
{

    QColor theColor;
    theColor.setRed(255);
    theColor.setGreen(0);
    theColor.setBlue(0);
    this->thePipeline->getObject()->setColor(theColor);

    this->activeRenderer->SetBackground( this->colorHandler->GetColor3d("Silver").GetData() );
    this->thePipeline->setNewPipeline();

    this->updateText();
    this->updateAffineInteraction();

    this->resetCamera();
    this->refreshRender();
}

void ViewerHandler::updateViewer()
{
    this->thePipeline->updatePipeline();
    this->updateText();
    this->updateNormals();
    this->updateCubeAxes();
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

    this->setAffineInteraction();

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
    this->activeRenderer->GetActiveCamera()->SetViewUp(this->thePipeline->getObject()->getPosition().getx(),1.0,this->thePipeline->getObject()->getPosition().getz());

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
    this->activeRenderer->GetActiveCamera()->SetViewUp(this->thePipeline->getObject()->getPosition().getx(),1.0,this->thePipeline->getObject()->getPosition().getz());

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
    this->activeRenderer->GetActiveCamera()->SetViewUp(this->thePipeline->getObject()->getPosition().getx(),1.0,this->thePipeline->getObject()->getPosition().getz());

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
    this->activeRenderer->GetActiveCamera()->SetViewUp(this->thePipeline->getObject()->getPosition().getx(),1.0,this->thePipeline->getObject()->getPosition().getz());

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
    this->axesWidget->SetEnabled(value);
}

void ViewerHandler::enableNormals(int value)
{
    this->showNormals = value;
}

void ViewerHandler::enableCubeAxes(int value)
{
    this->showCubeAxes = value;
}

void ViewerHandler::enableAffineInteraction(int value)
{
    if(value){
        affineWidget->On();
    }
    else{
        affineWidget->Off();
    }
}

void ViewerHandler::saveScene(QString fileName)
{
    QFileInfo fi(fileName);

    if(fi.suffix()=="stl")
    {
        this->stlWriter->SetFileName(fileName.toLocal8Bit().data());
        this->stlWriter->SetInputConnection(this->thePipeline->getAlgorithm());
        this->stlWriter->Write();
    }
    else if(fi.suffix()=="png")
    {
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
