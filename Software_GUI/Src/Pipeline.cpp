
#include "../Inc/Pipeline.h"

//default constructor
Pipeline::Pipeline()
{

}

//constructor
Pipeline::Pipeline(vtkSmartPointer<vtkRenderer> theRenderer)
{
    //link renderer and set initial actor
    this->activeRenderer = theRenderer;
    this->activeRenderer->AddActor(this->activeActor);
}

//function to refresh pipeline
void Pipeline::refreshPipeline()
{
    //remove active actors
    this->activeRenderer->RemoveActor(this->activeActor);
    this->activeRenderer->RemoveActor(this->activePolyActor);
}

//function to setup lights
void Pipeline::setLight()
{
    //set light parameters
    this->light->SetLightTypeToCameraLight();

    this->light->SetPositional( true );
    this->light->SetConeAngle( 60 );
    this->light->SetDiffuseColor( 1, 1, 1 );
    this->light->SetAmbientColor( 1, 1, 1 );
    this->light->SetSpecularColor( 1, 1, 1 );
    this->light->SetIntensity( 1.0 );

    //add light to renderer
    this->activeRenderer->AddLight(this->light);

    //make light follow camera
    this->activeRenderer->SetLightFollowCamera(true);
}

//function to setup new pipeline
void Pipeline::setNewPipeline()
{
    this->refreshPipeline();

    //set initial source algorithm
    this->finalAlgorithm = this->theObject->getSource();

    //setup poly algorithm
    this->setPolyAlgorithm();

    //declare mappers
    this->activeMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    this->activePolyMapper = vtkSmartPointer<vtkPolyDataMapper>::New();

    //decare actors
    this->activeActor = vtkSmartPointer<vtkActor>::New();
    this->activePolyActor = vtkSmartPointer<vtkActor>::New();

    //update mappers
    this->mapperStage();

    //set mappers
    this->activeActor->SetMapper(this->activeMapper);
    this->activePolyActor->SetMapper(this->activePolyMapper);

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

    //set initial source algorithm
    this->finalAlgorithm = this->theObject->getSource();

    //setup poly algorithm
    this->setPolyAlgorithm();

    //update object geometry
    this->geometryStage();

    //use active filters
    this->filterStage();

    //update mappers
    this->mapperStage();
    //update actors
    this->actorStage();
    this->polyActorStage();
}

//function to setup poly algorithm
void Pipeline::setPolyAlgorithm()
{
    vtkNew<vtkTransformFilter> TFfilter;
    TFfilter->SetInputConnection(this->finalAlgorithm);

    vtkNew<vtkTriangleFilter> tri;
    tri->SetInputConnection(TFfilter->GetOutputPort());

    vtkNew<vtkCleanPolyData> cleaner;
    cleaner->SetInputConnection(tri->GetOutputPort());
    cleaner->SetTolerance(0.005);
    this->finalPolyAlgorithmOutput = cleaner->GetOutputPort();
    this->finalPolyAlgorithm = cleaner;
}

void Pipeline::geometryStage()
{

    if(this->allowWarpScalar)
    {
        vtkNew<vtkCleanPolyData> clean;
        clean->SetInputData(this->theObject->getPolydata());

        // Generate normals
        vtkNew<vtkPolyDataNormals> normals;
        normals->SetInputConnection(clean->GetOutputPort());
        normals->SplittingOff();

        // Warp using the normals
        surfaceWarp->SetInputConnection(normals->GetOutputPort());
        surfaceWarp->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS,
                                     vtkDataSetAttributes::NORMALS);
        surfaceWarp->SetScaleFactor(1.0);
        this->finalAlgorithm = surfaceWarp->GetOutputPort();
    }
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

    //curvature filter
    if(this->activeFilters[6])
    {
        this->initCurvatureFilter();
        this->polyDataUsed = 1;
        this->colorAffected = 1;
    }
}

//function to update active mappers
void Pipeline::mapperStage()
{
    if(this->polyDataUsed)
    {
        this->activeMapper = vtkSmartPointer<vtkDataSetMapper>::New();
        this->activePolyMapper->SetInputConnection(this->finalPolyAlgorithmOutput);
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
    double originX = ((float)this->clipX)*(this->theObject->getPosition().getx()+(this->theObject->getDimensions().getx()*(this->clipPart)));
    double originY = ((float)this->clipY)*(this->theObject->getPosition().gety()+(this->theObject->getDimensions().gety()*(this->clipPart)));
    double originZ = ((float)this->clipZ)*(this->theObject->getPosition().getz()+(this->theObject->getDimensions().getz()*(this->clipPart)));
    planeLeft->SetOrigin(originX, originY, originZ);
    planeLeft->SetNormal((float)this->clipX, (float)this->clipY, (float)this->clipZ);
    this->clipFilter->SetClipFunction( planeLeft.Get() );
    this->finalAlgorithm = this->clipFilter->GetOutputPort();
}

//function to apply contour filter
void Pipeline::initContourFilter()
{
    /*
    // Create a plane to cut
    vtkNew<vtkPlane> plane;
    plane->SetOrigin(inputPolyData->GetCenter());
    plane->SetNormal(1, 1, 1);

    double minBound[3];
    minBound[0] = inputPolyData->GetBounds()[0];
    minBound[1] = inputPolyData->GetBounds()[2];
    minBound[2] = inputPolyData->GetBounds()[4];

    double maxBound[3];
    maxBound[0] = inputPolyData->GetBounds()[1];
    maxBound[1] = inputPolyData->GetBounds()[3];
    maxBound[2] = inputPolyData->GetBounds()[5];

    double center[3];
    center[0] = inputPolyData->GetCenter()[0];
    center[1] = inputPolyData->GetCenter()[1];
    center[2] = inputPolyData->GetCenter()[2];

    double distanceMin = sqrt(vtkMath::Distance2BetweenPoints(minBound, center));
    double distanceMax = sqrt(vtkMath::Distance2BetweenPoints(maxBound, center));

    // Create cutter
    vtkNew<vtkCutter> cutter;
    cutter->SetCutFunction(plane);
    cutter->SetInputData(inputPolyData);

    cutter->GenerateValues(20, -distanceMin, distanceMax);
    vtkNew<vtkPolyDataMapper> cutterMapper;
    cutterMapper->SetInputConnection(cutter->GetOutputPort());
    cutterMapper->ScalarVisibilityOff();

    // Create plane actor
    vtkNew<vtkActor> planeActor;
    planeActor->GetProperty()->SetColor(
      colors->GetColor3d("Deep_pink").GetData());
    planeActor->GetProperty()->SetLineWidth(5);
    planeActor->SetMapper(cutterMapper);
    */
    this->contourFilter->SetInputConnection(this->finalPolyAlgorithmOutput);
    this->contourFilter->SetNumberOfContours(1);
    this->contourFilter->SetValue(0, 10.0);
    vtkNew<vtkCompositeDataGeometryFilter> geomFilter2;
    geomFilter2->SetInputConnection(this->contourFilter->GetOutputPort());
    this->finalPolyAlgorithmOutput = geomFilter2->GetOutputPort();
}

//function to apply tube filter
void Pipeline::initTubeFilter()
{
    vtkSmartPointer<vtkExtractEdges> edges = vtkSmartPointer<vtkExtractEdges>::New();
    edges->SetInputConnection(this->finalAlgorithm);
    this->tubeFilter->SetInputConnection(edges->GetOutputPort());
    this->tubeFilter->SetRadius((double)tubeFilterRadius*this->theObject->getDimensionAverage()/100);
    this->tubeFilter->SetVaryRadiusToVaryRadiusOff();
    this->tubeFilter->SetNumberOfSides(40);
    this->finalAlgorithm = this->tubeFilter->GetOutputPort();
}

//function to apply curvature filter
void Pipeline::initCurvatureFilter()
{

    // Colour transfer function.
    vtkNew<vtkColorTransferFunction> ctf;
    ctf->SetColorSpaceToDiverging();
    ctf->AddRGBPoint(0.0, this->colorHandler->GetColor3d("MidnightBlue").GetRed(),
                     this->colorHandler->GetColor3d("MidnightBlue").GetGreen(),
                     this->colorHandler->GetColor3d("MidnightBlue").GetBlue());
    ctf->AddRGBPoint(1.0, this->colorHandler->GetColor3d("DarkOrange").GetRed(),
                     this->colorHandler->GetColor3d("DarkOrange").GetGreen(),
                     this->colorHandler->GetColor3d("DarkOrange").GetBlue());
    // Lookup table.
    vtkNew<vtkLookupTable> lut;
    lut->SetNumberOfColors(256);
    for (auto i = 0; i < lut->GetNumberOfColors(); ++i)
    {
        std::array<double, 4> color;
        ctf->GetColor(double(i) / lut->GetNumberOfColors(), color.data());
        color[3] = 1.0;
        lut->SetTableValue(i, color.data());
    }
    lut->SetRange(-10, 10);
    lut->Build();
    this->curvature->SetCurvatureTypeToGaussian();
    this->curvature->Update();
    //this->curvature->SetCurvatureTypeToMean();

// Link the pipeline together.
    std::cout<<"b3"<<std::endl;
    this->curvature->SetInputConnection(this->finalPolyAlgorithm->GetOutputPort());
    std::cout<<"b4"<<std::endl;
    this->finalPolyAlgorithmOutput = this->curvature->GetOutputPort();
    std::cout<<"b5"<<std::endl;
    this->activePolyMapper->SetLookupTable(lut);
    this->activePolyMapper->SetUseLookupTableScalarRange(1);
    std::cout<<"b6"<<std::endl;
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

void Pipeline::enableScalarWarp(int newVal)
{
    this->allowWarpScalar = newVal;
}

