
#include "../Inc/DataPipeline.h"

//default constructor
DataPipeline::DataPipeline()
{
    for(int i = 0;i<6;i++){
    this->activeFilters.push_back(0);
    }
}

//constructor
DataPipeline::DataPipeline(vtkSmartPointer<vtkRenderer> theRenderer)
{
    for(int i = 0;i<6;i++){
    this->activeFilters.push_back(0);
    }
    //link renderer and set initial actor
    this->activeRenderer = theRenderer;
    this->activeRenderer->AddActor(this->activeActor);
}

//default destructor
DataPipeline::~DataPipeline()
{

}

//function to refresh pipeline
void DataPipeline::refreshPipeline()
{
    //remove active actors
    this->activeRenderer->RemoveActor(this->activeActor);

    //set initial source algorithm
    this->finalAlgorithm = this->theObject->getSource();

    //declare mapper
    this->activeMapper = vtkSmartPointer<vtkDataSetMapper>::New();

    //declare actor
    this->activeActor = vtkSmartPointer<vtkActor>::New();
}

//function to setup new pipeline
void DataPipeline::setNewPipeline()
{
    this->refreshPipeline();

    //update mappers
    this->mapperStage();

    //set mappers
    this->activeActor->SetMapper(this->activeMapper);

    //update actors
    this->actorStage();

    //add actors to renderer
    this->activeRenderer->AddActor(this->activeActor);
}

//function to update active pipeline
void DataPipeline::updatePipeline()
{

    if(this->theObject->getObjectType()==3)
    {
        this->theObject->updateVTKModel();
    }
    else
    {
        this->theObject->updateObjectData();
    }

    //set initial source algorithm
    this->finalAlgorithm = this->theObject->getSource();

    //use active filters
    this->filterStage();
    //update mappers
    this->mapperStage();
    //update actors
    this->actorStage();

}

//function to use pipeline filters
void DataPipeline::filterStage()
{
    //shrink filter
    if(this->activeFilters[0])
    {
        this->initShrinkFilter();
    }

    //clip filter
    if(this->activeFilters[1])
    {

        this->initClipFilter();

    }

    //tube filter
    if(this->activeFilters[5])
    {
        this->initTubeFilter();
    }
}

//function to update active mappers
void DataPipeline::mapperStage()
{
    this->activeMapper->SetInputConnection(this->finalAlgorithm);
}

//function to update actor of main data
void DataPipeline::actorStage()
{
    //define object state
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

    //add actor color only if it is not VTK object
    if(this->theObject->getObjectType()<3)
    {
        this->activeActor->GetProperty()->SetColor((double)this->theObject->getColor().red()/255,
                (double)this->theObject->getColor().green()/255,
                (double)this->theObject->getColor().blue()/255);
    }

    //smooth filter
    if(this->activeFilters[3])
    {
        this->activeActor->GetProperty()->EdgeVisibilityOff();
    }
    else
    {
        this->activeActor->GetProperty()->EdgeVisibilityOn();
    }

    //sphere points filter
    if(this->activeFilters[4])
    {
        this->activeActor->GetProperty()->SetRepresentationToPoints();
        this->activeActor->GetProperty()->RenderPointsAsSpheresOn();
        this->activeActor->GetProperty()->SetPointSize(sphereFilterRadius);
    }
    else
    {
        this->activeActor->GetProperty()->RenderPointsAsSpheresOff();
        this->activeActor->GetProperty()->SetPointSize(1);
    }

    //let object be affected by light if required
    if(this->showLight)
    {
        this->activeActor->GetProperty()->LightingOn();
        this->light->SetIntensity( this->lightIntensity );
        this->activeActor->GetProperty()->SetSpecular(this->lightSpecular);
        this->activeActor->GetProperty()->SetSpecularPower(this->lightSpecular);
    }
    else
    {
        this->activeActor->GetProperty()->LightingOff();
    }

}

//function to apply shrink filter
void DataPipeline::initShrinkFilter()
{
    this->shrinkFilter->SetInputConnection(this->finalAlgorithm);
    this->shrinkFilter->SetShrinkFactor(this->shrinkFactor);
    this->shrinkFilter->Update();
    this->finalAlgorithm = this->shrinkFilter->GetOutputPort();
}

//function to apply clip filter
void DataPipeline::initClipFilter()
{
    this->clipFilter->SetInputConnection(this->finalAlgorithm);

    vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New();
    double originX = ((float)this->clipX)*(this->theObject->getPosition().getx()+(this->theObject->getDimensions().getx()*(this->clipPart-0.5)));
    double originY = ((float)this->clipY)*(this->theObject->getPosition().gety()+(this->theObject->getDimensions().gety()*(this->clipPart-0.5)));
    double originZ = ((float)this->clipZ)*(this->theObject->getPosition().getz()+(this->theObject->getDimensions().getz()*(this->clipPart-0.5)));
    planeLeft->SetOrigin(originX, originY, originZ);
    planeLeft->SetNormal((float)this->clipX, (float)this->clipY, (float)this->clipZ);
    this->clipFilter->SetClipFunction( planeLeft.Get() );
    this->finalAlgorithm = this->clipFilter->GetOutputPort();
}

//function to apply tube filter
void DataPipeline::initTubeFilter()
{
    vtkSmartPointer<vtkExtractEdges> edges = vtkSmartPointer<vtkExtractEdges>::New();
    edges->SetInputConnection(this->finalAlgorithm);
    this->tubeFilter->SetInputConnection(edges->GetOutputPort());
    this->tubeFilter->SetRadius((double)tubeFilterRadius*this->theObject->getDimensionAverage()/100);
    this->tubeFilter->SetVaryRadiusToVaryRadiusOff();
    this->tubeFilter->SetNumberOfSides(this->tubeSides);
    this->finalAlgorithm = this->tubeFilter->GetOutputPort();
}

//function to get active mapper
vtkSmartPointer<vtkDataSetMapper> DataPipeline::getMapper()
{
    return this->activeMapper;
}

//function to get final algorithm
vtkAlgorithmOutput* DataPipeline::getAlgorithm()
{
    return this->finalAlgorithm;
}

//function to set active mapper
void DataPipeline::setMapper(vtkSmartPointer<vtkDataSetMapper> theMapper)
{
    this->activeMapper = theMapper;
}

//function to set final algorithm
void DataPipeline::setAlgorithm(vtkAlgorithmOutput* theAlgorithm)
{
    this->finalAlgorithm = theAlgorithm;
}

//function to set shrink factor
void DataPipeline::setShrinkFactor(double newVal)
{
    this->shrinkFactor = newVal;
}

//function to set radius of tube filter tubes
void DataPipeline::setTubeRad(double newVal)
{
    this->tubeFilterRadius = newVal;
}

//function to set number of tube filter tube sides
void DataPipeline::setTubeSides(int newVal)
{
    if(newVal<3)
    {
        this->tubeSides = 3;
    }
    else
    {
        this->tubeSides = newVal;
    }
}

//function to set radius of sphere points filter spheres
void DataPipeline::setSphereRad(double newVal)
{
    this->sphereFilterRadius = newVal;
}

//function to set the value for part of object that is clipped with clip filter
void DataPipeline::setClipPart(double newVal)
{
    this->clipPart = newVal;
}

//function enable clip filter to clip on x axis
void DataPipeline::enableClipX(int newVal)
{
    this->clipX = newVal;
}

//function enable clip filter to clip on y axis
void DataPipeline::enableClipY(int newVal)
{
    this->clipY = newVal;
}

//function enable clip filter to clip on z axis
void DataPipeline::enableClipZ(int newVal)
{
    this->clipZ = newVal;
}

