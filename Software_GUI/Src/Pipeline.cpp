
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

//function to set active actor
void Pipeline::setActor(vtkSmartPointer<vtkActor> theActor)
{
    this->activeActor = theActor;
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

