/*! \file Pipeline.h File Reference
    \author   Copyright: \n Code part: Danielius Zurlys (StudentID: 20130611)
                         \n Comments part: Danielius Zurlys and Chen Xu  (StudentID: 20187733)
    \brief  build a pipeline part for VTK.
*/
#ifndef PIPELINE_H_INCLUDED
#define PIPELINE_H_INCLUDED

#include <math.h>
#include <QMainWindow>
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>

#include <vtkDataSetMapper.h>
#include <vtkRenderer.h>
#include <vtkNew.h>

#include <vtkClipDataSet.h>
#include <vtkShrinkFilter.h>
#include <vtkGeometryFilter.h>
#include <vtkContourFilter.h>
#include <vtkSplineFilter.h>
#include <vtkTubeFilter.h>
#include <vtkCompositeDataGeometryFilter.h>
#include <vtkTriangleFilter.h>

#include <vtkCutter.h>

#include <vtkCleanPolyData.h>
#include <vtkPolyDataNormals.h>
#include <vtkColorTransferFunction.h>
#include <vtkCurvatures.h>
#include <vtkLookupTable.h>
#include <vtkTransformFilter.h>

#include <vtkExtractEdges.h>

#include <vtkIdList.h>

#include "./VTKObjectHandler.h"

/*! \class Pipeline
    \brief  class to handle VTK pipeline operation
*/
class Pipeline{


protected:

    VTKObjectHandler* theObject = new VTKObjectHandler;

    vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();

    vtkSmartPointer<vtkNamedColors> colorHandler = vtkSmartPointer<vtkNamedColors>::New();

    QColor actorColor;

    vtkSmartPointer<vtkActor> activeActor = vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkRenderer> activeRenderer = vtkSmartPointer<vtkRenderer>::New();

    std::vector<int> activeFilters;

    int showWireframe = 0;
    int showPoints = 0;

    int showLight = 0;
    double lightIntensity = 1.0;
    double lightSpecular = 0.0;

public:
    //! default constructor
    Pipeline();
    //! constructor
    Pipeline(vtkSmartPointer<vtkRenderer>);
    //! function to setup lights
    void setLight();
    /*! function to get object handler
        \return VTKObjectHandler - getObject()
    */
    VTKObjectHandler* getObject();
    /*! function to get active actor
     \return vtkSmartPointer<vtkActor> - getActor()
    */
    vtkSmartPointer<vtkActor> getActor();
    /*! function to get active Renderer
    \return vtkSmartPointer<vtkRenderer> - received Renderer
    */
    vtkSmartPointer<vtkRenderer> getRenderer();

    /*! function to set active filters
    \n Arguments: std::vector<int> - array of 1 or 0 to be set to filters
    */
    void setFilters(std::vector<int>);
    /*! function to set active Actor
    \return vtkSmartPointer<vtkActor> - set a actor
    */
    void setActor(vtkSmartPointer<vtkActor>);
    /*! function to set active Renderer
    \n Arguments: vtkSmartPointer<vtkRenderer> - set a Renderer
    */
    void setRenderer(vtkSmartPointer<vtkRenderer>);
    /*! function to enable object wireframe state
    \n Arguments: int - enable wireframe
    */
    void enableWireframe(int);
    /*! function to enable object points state
    \n Arguments: int - enable points
    */
    void enablePoints(int);
    /*! function to make object require and be affected by light
    \n Arguments: int - enable a light
    */
    void enableLight(int);
    /*! function to set light intensity
    \n Arguments: double - set light intensity
    \return none
    */
    void setLightIntensity(double);
    /*! function to set light specular value
    \n Arguments: double - set light specular value
    */
    void setLightSpecular(double);
    /*! function to set object opacity
    \n Arguments: double - set object opacity
    */
    void setOpacity(double);

};

#endif //! PIPELINE_H_INCLUDED
