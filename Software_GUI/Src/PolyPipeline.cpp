
#include "../Inc/PolyPipeline.h"

//default constructor
Pipeline::PolyPipeline()
{

}

//constructor
Pipeline::Pipeline(vtkSmartPointer<vtkRenderer> theRenderer)
{
    //link renderer and set initial actor
    this->activeRenderer = theRenderer;
    this->activeRenderer->AddActor(this->activeActor);
}

//function to setup new pipeline
void Pipeline::setNewPipeline()
{
    this->refreshPipeline();

    //initial polydata
    this->finalPolydata = this->theObject->getPolydata();

    //declare mappers
    this->activePolyMapper = vtkSmartPointer<vtkPolyDataMapper>::New();

    //declare actors
    this->activeActor = vtkSmartPointer<vtkActor>::New();

    //update mappers
    this->mapperStage();

    //set mappers
    this->activeActor->SetMapper(this->activePolyMapper);

    //update actors
    this->actorStage();
    this->polyActorStage();

    //add actors to renderer
    this->activeRenderer->AddActor(this->activeActor);
    this->activeRenderer->AddActor(this->activePolyActor);
}

//function to update active pipeline
void Pipeline::updatePipeline()
{

    if(this->theObject->getObjectType()==3)
    {
        this->theObject->updateVTKModel();
    }
    else{
        this->theObject->updateObjectData();
    }

    //set initial source algorithm
    this->finalAlgorithm = this->theObject->getSource();

    //initial polydata
    this->finalPolydata = this->theObject->getPolydata();
    //use active filters
    this->filterStage();
    //update mappers
    this->mapperStage();
    //update actors
    this->actorStage();

}

//function to use pipeline filters
void Pipeline::filterStage()
{
    //reset factors
    this->polyDataUsed = 0;
    this->colorAffected = 0;

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

    //contour filter
    if(this->activeFilters[2])
    {
        this->initContourFilter();
        this->polyDataUsed = 1;
    }

    //tube filter
    if(this->activeFilters[5])
    {
        this->initTubeFilter();
    }
}

//function to update active mappers
void Pipeline::mapperStage()
{
    if(this->polyDataUsed)
    {
        this->activeMapper = vtkSmartPointer<vtkDataSetMapper>::New();
        this->activePolyMapper->SetInputData(this->finalPolydata);
    }
    else
    {
        this->activeMapper->SetInputConnection(this->finalAlgorithm);
        this->activePolyMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    }
    this->activeMapper->SetInputConnection(this->finalAlgorithm);
}

//function to update actor of poly data
void Pipeline::polyActorStage()
{
    if(this->polyDataUsed)
    {
        //define object state
        if(this->showWireframe)
        {
            this->activePolyActor->GetProperty()->SetRepresentationToWireframe();
        }
        else if(this->showPoints)
        {
            this->activePolyActor->GetProperty()->SetRepresentationToPoints();
        }
        else
        {
            this->activePolyActor->GetProperty()->SetRepresentationToSurface();
        }

        //set actor color only if object color is not affected otherwise
        if(this->colorAffected)
        {
            this->activePolyActor->GetProperty()->SetColor(1.0,
                    1.0,
                    1.0);
        }
        else
        {
            this->activePolyActor->GetProperty()->SetColor(0.0,
                    1.0,
                    0.0);
        }

        //smooth filter
        if(!this->activeFilters[3])
        {
            this->activePolyActor->GetProperty()->EdgeVisibilityOn();
        }
        else
        {
            this->activePolyActor->GetProperty()->EdgeVisibilityOff();
        }

        //sphere points filter
        if(this->activeFilters[4])
        {
            this->activePolyActor->GetProperty()->RenderPointsAsSpheresOn();
        }
        else
        {
            this->activePolyActor->GetProperty()->RenderPointsAsSpheresOff();
        }

        //let object be affected by light if required
        if(this->showLight)
        {
            this->activePolyActor->GetProperty()->LightingOn();
            this->light->SetIntensity( this->lightIntensity );
            this->activePolyActor->GetProperty()->SetSpecular(this->lightSpecular);
            this->activePolyActor->GetProperty()->SetSpecularPower(this->lightSpecular);
        }
        else
        {
            this->activePolyActor->GetProperty()->LightingOff();
        }
    }
}

//function to update actor of main data
void Pipeline::actorStage()
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
        //set actor color only if object color is not affected otherwise
        if(this->colorAffected)
        {
            this->activePolyActor->GetProperty()->SetColor(1.0,
                    1.0,
                    1.0);
        }
        else
        {
            this->activeActor->GetProperty()->SetColor((double)this->theObject->getColor().red()/255,
                    (double)this->theObject->getColor().green()/255,
                    (double)this->theObject->getColor().blue()/255);
        }
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
void Pipeline::initShrinkFilter()
{
    this->shrinkFilter->SetInputConnection(this->finalAlgorithm);
    this->shrinkFilter->SetShrinkFactor(this->shrinkFactor);
    this->shrinkFilter->Update();
    this->finalAlgorithm = this->shrinkFilter->GetOutputPort();
}

//function to apply clip filter
void Pipeline::initClipFilter()
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

//function to apply contour filter
void Pipeline::initContourFilter()
{
    std::cout<<"yes1"<<std::endl;
    // Create a plane to cut
    vtkNew<vtkPlane> plane;
    plane->SetOrigin(this->finalPolydata->GetCenter());
    plane->SetNormal(1, 1, 1);

    double minBound[3];
    minBound[0] = this->finalPolydata->GetBounds()[0];
    minBound[1] = this->finalPolydata->GetBounds()[2];
    minBound[2] = this->finalPolydata->GetBounds()[4];

    double maxBound[3];
    maxBound[0] = this->finalPolydata->GetBounds()[1];
    maxBound[1] = this->finalPolydata->GetBounds()[3];
    maxBound[2] = this->finalPolydata->GetBounds()[5];

    double center[3];
    center[0] = this->finalPolydata->GetCenter()[0];
    center[1] = this->finalPolydata->GetCenter()[1];
    center[2] = this->finalPolydata->GetCenter()[2];

    double distanceMin = sqrt(vtkMath::Distance2BetweenPoints(minBound, center));
    double distanceMax = sqrt(vtkMath::Distance2BetweenPoints(maxBound, center));

    // Create cutter
    vtkNew<vtkCutter> cutter;
    cutter->SetInputData(this->finalPolydata);
    cutter->SetCutFunction(plane);
    std::cout<<"yes2"<<std::endl;
    cutter->GenerateValues(20, -distanceMin, distanceMax);
    this->finalPolydata = cutter->GetOutput();
   this->activePolyMapper->ScalarVisibilityOff();
    std::cout<<"yes3"<<std::endl;

}

//function to apply tube filter
void Pipeline::initTubeFilter()
{
    vtkSmartPointer<vtkExtractEdges> edges = vtkSmartPointer<vtkExtractEdges>::New();
    edges->SetInputConnection(this->finalAlgorithm);
    this->tubeFilter->SetInputConnection(edges->GetOutputPort());
    this->tubeFilter->SetRadius((double)tubeFilterRadius*this->theObject->getDimensionAverage()/100);
    this->tubeFilter->SetVaryRadiusToVaryRadiusOff();
    this->tubeFilter->SetNumberOfSides(this->tubeSides);
    this->finalAlgorithm = this->tubeFilter->GetOutputPort();
}

//function to get object handler
VTKObjectHandler* Pipeline::getObject()
{
    return this->theObject;
}

//function to get active actor
vtkSmartPointer<vtkActor> Pipeline::getActor()
{
    return this->activeActor;
}

//function to get active mapper
vtkSmartPointer<vtkDataSetMapper> Pipeline::getMapper()
{
    return this->activeMapper;
}

//function to get final algorithm
vtkAlgorithmOutput* Pipeline::getAlgorithm()
{
    return this->finalAlgorithm;
}

//function to set active actor
void Pipeline::setActor(vtkSmartPointer<vtkActor> theActor)
{
    this->activeActor = theActor;
}

//function to set active mapper
void Pipeline::setMapper(vtkSmartPointer<vtkDataSetMapper> theMapper)
{
    this->activeMapper = theMapper;
}

//function to set final algorithm
void Pipeline::setAlgorithm(vtkAlgorithmOutput* theAlgorithm)
{
    this->finalAlgorithm = theAlgorithm;
}

//function to get active renderer
vtkSmartPointer<vtkRenderer> Pipeline::getRenderer()
{
    return this->activeRenderer;
}

//function to set active renderer
void Pipeline::setRenderer(vtkSmartPointer<vtkRenderer> theRenderer)
{
    this->activeRenderer = theRenderer;
}

//function to set active filters
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

//function to set shrink factor
void Pipeline::setShrinkFactor(double newVal)
{
    this->shrinkFactor = newVal;
}

//function to set radius of tube filter tubes
void Pipeline::setTubeRad(double newVal)
{
    this->tubeFilterRadius = newVal;
}

//function to set number of tube filter tube sides
 void Pipeline::setTubeSides(int newVal){
    if(newVal<3){
        this->tubeSides = 3;
    }
    else{
        this->tubeSides = newVal;
    }
 }

//function to set radius of sphere points filter spheres
void Pipeline::setSphereRad(double newVal)
{
    this->sphereFilterRadius = newVal;
}

//function to set the value for part of object that is clipped with clip filter
void Pipeline::setClipPart(double newVal)
{
    this->clipPart = newVal;
}

//function to set light intensity
void Pipeline::setLightIntensity(double newVal)
{
    this->lightIntensity = newVal;
}

//function to set light specular value
void Pipeline::setLightSpecular(double newVal)
{
    this->lightSpecular = newVal;
}

//function to set object opacity
void Pipeline::setOpacity(double newVal)
{
    this->activeActor->GetProperty()->SetOpacity(newVal);
}

//function to enable object wireframe state
void Pipeline::enableWireframe(int newVal)
{
    this->showWireframe = newVal;
}

//function to enable object points state
void Pipeline::enablePoints(int newVal)
{
    this->showPoints = newVal;
}

//function to make object require and be affected by light
void Pipeline::enableLight(int newVal)
{
    this->showLight = newVal;
}

//function enable clip filter to clip on x axis
void Pipeline::enableClipX(int newVal)
{
    this->clipX = newVal;
}

//function enable clip filter to clip on y axis
void Pipeline::enableClipY(int newVal)
{
    this->clipY = newVal;
}

//function enable clip filter to clip on z axis
void Pipeline::enableClipZ(int newVal)
{
    this->clipZ = newVal;
}

