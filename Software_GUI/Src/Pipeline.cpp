
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
    this->activeRenderer->RemoveActor(this->activePolyActor);
}

void Pipeline::setLight()
{
    this->light->SetLightTypeToCameraLight();

    this->light->SetPositional( true );
    this->light->SetConeAngle( 60 );
    this->light->SetDiffuseColor( 1, 1, 1 );
    this->light->SetAmbientColor( 1, 1, 1 );
    this->light->SetSpecularColor( 1, 1, 1 );
    this->light->SetIntensity( 1.0 );

    this->activeRenderer->AddLight(this->light);

    this->activeRenderer->SetLightFollowCamera(true);
}

void Pipeline::setNewPipeline()
{
    this->refreshPipeline();
    this->finalAlgorithm = this->theObject->getSource();
    this->activeMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    this->activePolyMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    this->activeActor = vtkSmartPointer<vtkActor>::New();
    this->activePolyActor = vtkSmartPointer<vtkActor>::New();

    this->mapperStage();
    this->activeActor->SetMapper(this->activeMapper);
    this->activePolyActor->SetMapper(this->activePolyMapper);
    this->actorSetupRequired = 1;
    this->actorStage();
    this->activeRenderer->AddActor(this->activeActor);
    this->activeRenderer->AddActor(this->activePolyActor);
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
        this->initShrinkFilter();
    }
    if(this->activeFilters[1])
    {

        this->initClipFilter();

    }
    if(this->activeFilters[2])
    {
        this->initContourFilter();
        this->polyDataUsed = 1;
    }
    else
    {
        this->polyDataUsed = 0;
    }
    if(this->activeFilters[5])
    {
        this->initTubeFilter();
    }
    if(this->activeFilters[6])
    {
        this->initCurvatureFilter();
    }

}

void Pipeline::mapperStage()
{
    if(this->polyDataUsed)
    {
        this->activePolyMapper->SetInputConnection(this->finalAlgorithm);
        this->activeMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    }
    else
    {
        this->activeMapper->SetInputConnection(this->finalAlgorithm);
        this->activePolyMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    }
}

void Pipeline::polyActorStage()
{
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

    if(this->theObject->getObjectType()<3)
    {
        this->activePolyActor->GetProperty()->SetColor((double)this->theObject->getColor().red()/255,
                (double)this->theObject->getColor().green()/255,
                (double)this->theObject->getColor().blue()/255);

    }
    if(!this->activeFilters[3])
    {
        this->activePolyActor->GetProperty()->EdgeVisibilityOn();
    }
    else
    {
        this->activePolyActor->GetProperty()->EdgeVisibilityOff();
    }

    if(this->activeFilters[4])
    {
        this->activePolyActor->GetProperty()->RenderPointsAsSpheresOn();
    }
    else
    {
        this->activePolyActor->GetProperty()->RenderPointsAsSpheresOff();
    }

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
    if(this->activeFilters[3])
    {
        this->activeActor->GetProperty()->EdgeVisibilityOff();
    }
    else
    {
        this->activeActor->GetProperty()->EdgeVisibilityOn();
    }

    if(this->activeFilters[4])
    {
        this->activeActor->GetProperty()->RenderPointsAsSpheresOn();
        this->activeActor->GetProperty()->SetPointSize(this->theObject->getDimensionAverage()*0.1);
    }
    else
    {
        this->activeActor->GetProperty()->RenderPointsAsSpheresOff();
        this->activeActor->GetProperty()->SetPointSize(1);
    }

    if(this->showLight)
    {
        this->activeActor->GetProperty()->LightingOn();
        this->light->SetIntensity( this->lightIntensity );
        this->activeActor->GetProperty()->SetSpecular(this->lightSpecular);
        this->activeActor->GetProperty()->SetSpecularPower(this->lightSpecular*100);
    }
    else
    {
        this->activeActor->GetProperty()->LightingOff();
    }

}

void Pipeline::initShrinkFilter()
{
    this->shrinkFilter->SetInputConnection(this->finalAlgorithm);
    this->shrinkFilter->SetShrinkFactor(this->shrinkFactor);
    this->shrinkFilter->Update();
    this->finalAlgorithm = this->shrinkFilter->GetOutputPort();
}
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
void Pipeline::initContourFilter()
{
    this->contourFilter->SetInputConnection(this->finalAlgorithm);
    this->contourFilter->SetNumberOfContours(1);
    this->contourFilter->SetValue(0, 10.0);
    vtkNew<vtkCompositeDataGeometryFilter> geomFilter2;
    geomFilter2->SetInputConnection(this->contourFilter->GetOutputPort());
    this->finalAlgorithm = geomFilter2->GetOutputPort();
}

void Pipeline::initTubeFilter()
{
    vtkSmartPointer<vtkExtractEdges> edges = vtkSmartPointer<vtkExtractEdges>::New();
    edges->SetInputConnection(this->finalAlgorithm);
    this->tubeFilter->SetInputConnection(edges->GetOutputPort());
    this->tubeFilter->SetRadius(this->theObject->getDimensionAverage()*0.03);
    this->tubeFilter->SetVaryRadiusToVaryRadiusOff();
    this->tubeFilter->SetNumberOfSides(40);
    this->finalAlgorithm = this->tubeFilter->GetOutputPort();
}

void Pipeline::initCurvatureFilter()
{
    /*
    this->shrinkFilter->SetInputConnection(this->finalAlgorithm);
    std::vector<vtkSmartPointer<vtkCurvatures>> curvatures;
    for (auto idx = 0; idx < sources.size(); ++idx)
    {
        curvatures.push_back(vtkSmartPointer<vtkCurvatures>::New());
        if (idx % 2 == 0)
        {
            curvatures[idx]->SetCurvatureTypeToGaussian();
        }
        else
        {
            curvatures[idx]->SetCurvatureTypeToMean();
        }
    }
    this->finalAlgorithm = this->shrinkFilter->GetOutputPort();
    */
}

VTKObjectHandler* Pipeline::getObject()
{
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

void Pipeline::setLightIntensity(double newVal)
{
    this->lightIntensity = newVal;
}

void Pipeline::setLightSpecular(double newVal)
{
    this->lightSpecular = newVal;
}

void Pipeline::setOpacity(double newVal)
{
    this->activeActor->GetProperty()->SetOpacity(newVal);
}

void Pipeline::enableWireframe(int newVal)
{
    this->showWireframe = newVal;
}

void Pipeline::enablePoints(int newVal)
{
    this->showPoints = newVal;
}

void Pipeline::enableLight(int newVal)
{
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

