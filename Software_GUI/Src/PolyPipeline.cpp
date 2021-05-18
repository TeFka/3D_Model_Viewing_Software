
#include "../Inc/PolyPipeline.h"

//default constructor
PolyPipeline::PolyPipeline()
{
    for(int i = 0;i<1;i++){
    this->activeFilters.push_back(0);
    }
}

//constructor
PolyPipeline::PolyPipeline(vtkSmartPointer<vtkRenderer> theRenderer)
{
    for(int i = 0;i<1;i++){
    this->activeFilters.push_back(0);
    }
    //link renderer and set initial actor
    this->activeRenderer = theRenderer;
    this->activeRenderer->AddActor(this->activeActor);
}

//function to refresh pipeline
void PolyPipeline::refreshPipeline()
{
    //remove active actors
    this->activeRenderer->RemoveActor(this->activeActor);

    //set initial source algorithm
    this->finalPolydata = this->theObject->getPolydata();

    //declare mapper
    this->activePolyMapper = vtkSmartPointer<vtkPolyDataMapper>::New();

    //declare actor
    this->activeActor = vtkSmartPointer<vtkActor>::New();
}

//function to setup new pipeline
void PolyPipeline::setNewPipeline()
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

    //add actors to renderer
    this->activeRenderer->AddActor(this->activeActor);
}

//function to update active pipeline
void PolyPipeline::updatePipeline()
{

    if(this->theObject->getObjectType()==3)
    {
        this->theObject->updateVTKModel();
    }
    else{
        this->theObject->updateObjectData();
    }

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
void PolyPipeline::filterStage()
{

    //contour filter
    if(this->activeFilters[2])
    {
        this->initContourFilter();
    }
}

//function to update active mappers
void PolyPipeline::mapperStage()
{
    this->activePolyMapper->SetInputData(this->finalPolydata);
}

//function to update actor of poly data
void PolyPipeline::actorStage()
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

        //set actor color only if object color is not affected otherwise
        if(this->colorAffected)
        {
            this->activeActor->GetProperty()->SetColor(1.0,
                    1.0,
                    1.0);
        }
        else
        {
            this->activeActor->GetProperty()->SetColor(0.0,
                    1.0,
                    0.0);
        }

        //smooth filter
        if(!this->activeFilters[3])
        {
            this->activeActor->GetProperty()->EdgeVisibilityOn();
        }
        else
        {
            this->activeActor->GetProperty()->EdgeVisibilityOff();
        }

        //sphere points filter
        if(this->activeFilters[4])
        {
            this->activeActor->GetProperty()->RenderPointsAsSpheresOn();
        }
        else
        {
            this->activeActor->GetProperty()->RenderPointsAsSpheresOff();
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

//function to apply contour filter
void PolyPipeline::initContourFilter()
{
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
    cutter->GenerateValues(20, -distanceMin, distanceMax);
    this->finalPolydata = cutter->GetOutput();
    this->activePolyMapper->ScalarVisibilityOff();

}

//function to get object handler
vtkPolyData* PolyPipeline::getPolydata()
{
    return this->finalPolydata;
}

//function to get object handler
void PolyPipeline::setPolydata(vtkPolyData* newData)
{
    this->finalPolydata = newData;
}

//function to get active mapper
vtkSmartPointer<vtkPolyDataMapper> PolyPipeline::getMapper()
{
    return this->activePolyMapper;
}

//function to set active mapper
void PolyPipeline::setMapper(vtkSmartPointer<vtkPolyDataMapper> theMapper)
{
    this->activePolyMapper = theMapper;
}
