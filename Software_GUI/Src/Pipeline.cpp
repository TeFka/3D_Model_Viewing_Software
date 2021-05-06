
#include "../Inc/Pipeline.h"

Pipeline::Pipeline()
{

}

Pipeline::Pipeline(vtkSmartPointer<vtkRenderer> theRenderer)
{
    this->activeRenderer = theRenderer;
    this->activeRenderer->AddActor(this->activeActor);
}

void Pipeline::refreshPipeline()
{
    this->activeRenderer->RemoveActor(this->activeActor);

}

void Pipeline::setNewPipeline()
{
    this->refreshPipeline();
    this->finalAlgorithm = this->theObject->getSource();
    this->activeMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    this->activeActor = vtkSmartPointer<vtkActor>::New();

    this->mapperStage();
    this->activeActor->SetMapper(this->activeMapper);
    this->actorSetupRequired = 1;
    this->actorStage();
    this->activeRenderer->AddActor(this->activeActor);
}

void Pipeline::updatePipeline()
{
    if(this->theObject->getObjectType()==3)
    {
        this->theObject->updateVTKModel();
    }
    this->finalAlgorithm = this->theObject->getSource();
    this->filterStage();
    this->mapperStage();
    this->actorStage();
}

void Pipeline::filterStage()
{

    if(this->activeFilters[0])
    {
        this->shrinkFilter->SetInputConnection(this->finalAlgorithm);
        this->initShrinkFilter();
        this->finalAlgorithm = this->shrinkFilter->GetOutputPort();
    }
    if(this->activeFilters[1])
    {
        this->clipFilter->SetInputConnection(this->finalAlgorithm);
        this->initClipFilter();
        this->finalAlgorithm = this->clipFilter->GetOutputPort();
    }
    if(this->activeFilters[2])
    {
        this->contourFilter->SetInputConnection(this->finalAlgorithm);
        this->initContourFilter();
        this->finalAlgorithm = this->contourFilter->GetOutputPort();
    }
}

void Pipeline::mapperStage()
{
    this->activeMapper->SetInputConnection(this->finalAlgorithm);
}

void Pipeline::actorStage()
{
    if(this->showWireframe)
    {
        this->activeActor->GetProperty()->SetRepresentationToWireframe();
    }
    else if(this->showPoints)
    {
        this->activeActor->GetProperty()->SetRepresentationToPoints();
    }
    else
    {
        this->activeActor->GetProperty()->SetRepresentationToSurface();
    }

    if(this->theObject->getObjectType()<3)
    {
        this->activeActor->GetProperty()->SetColor((double)this->theObject->getColor().red()/255,
                (double)this->theObject->getColor().green()/255,
                (double)this->theObject->getColor().blue()/255);

    }
    if(!this->activeFilters[3]){
    this->activeActor->GetProperty()->EdgeVisibilityOn();
    }

    if(!this->showLight){
        this->activeActor->GetProperty()->LightingOff();
    }

}

void Pipeline::initShrinkFilter()
{
    this->shrinkFilter->SetShrinkFactor(this->shrinkFactor);
    this->shrinkFilter->Update();
}
void Pipeline::initClipFilter()
{
    vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New();
    double originX = ((float)this->clipX)*(this->theObject->getPosition().getx()+(this->theObject->getDimensions().getx()*(this->clipPart)));
    double originY = ((float)this->clipY)*(this->theObject->getPosition().gety()+(this->theObject->getDimensions().gety()*(this->clipPart)));
    double originZ = ((float)this->clipZ)*(this->theObject->getPosition().getz()+(this->theObject->getDimensions().getz()*(this->clipPart)));
    planeLeft->SetOrigin(originX, originY, originZ);
    planeLeft->SetNormal((float)this->clipX, (float)this->clipY, (float)this->clipZ);
    this->clipFilter->SetClipFunction( planeLeft.Get() );
}
void Pipeline::initContourFilter()
{
    contourFilter->SetValue(0, 0.0);
}

VTKObjectHandler* Pipeline::getObject(){
    return this->theObject;
}

vtkSmartPointer<vtkActor> Pipeline::getActor()
{
    return this->activeActor;
}
vtkSmartPointer<vtkDataSetMapper> Pipeline::getMapper()
{
    return this->activeMapper;
}
vtkAlgorithmOutput* Pipeline::getAlgorithm()
{
    return this->finalAlgorithm;
}

void Pipeline::setActor(vtkSmartPointer<vtkActor> theActor)
{
    this->activeActor = theActor;
}
void Pipeline::setMapper(vtkSmartPointer<vtkDataSetMapper> theMapper)
{
    this->activeMapper = theMapper;
}
void Pipeline::setAlgorithm(vtkAlgorithmOutput* theAlgorithm)
{
    this->finalAlgorithm = theAlgorithm;
}

vtkSmartPointer<vtkRenderer> Pipeline::getRenderer()
{
    return this->activeRenderer;
}

void Pipeline::setRenderer(vtkSmartPointer<vtkRenderer> theRenderer)
{
    this->activeRenderer = theRenderer;
}

void Pipeline::setFilters(std::vector<int> filters)
{
    for(int i = 0; i<filters.size(); i++)
    {
        if(i<this->activeFilters.size())
        {
            this->activeFilters[i] = filters[i];
        }
    }
}

void Pipeline::setShrinkFactor(double newVal)
{
    this->shrinkFactor = newVal;
}

void Pipeline::setClipPart(double newVal)
{
    this->clipPart = newVal;
}

void Pipeline::enableWireframe(int newVal)
{
    this->showWireframe = newVal;
}

void Pipeline::enablePoints(int newVal)
{
    this->showPoints = newVal;
}

void Pipeline::enableLight(int newVal){
    this->showLight = newVal;
}

void Pipeline::enableClipX(int newVal)
{
    this->clipX = newVal;
}

void Pipeline::enableClipY(int newVal)
{
    this->clipY = newVal;
}

void Pipeline::enableClipZ(int newVal)
{
    this->clipZ = newVal;
}

