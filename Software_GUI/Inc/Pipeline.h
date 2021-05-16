/*! \file Pipeline.h File Reference
    \author   Copyright: \n Code part: Danielius Zurlys (StudentID: 20130611)
                         \n Comments part: Danielius Zurlys and Chen Xu  (StudentID: 20187733)
    \brief  build a pipeline part for VTK.
*/
#ifndef PIPELINEINFO_H_INCLUDED
#define PIPELINEINFO_H_INCLUDED

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


private:

    VTKObjectHandler* theObject = new VTKObjectHandler;

    vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();

    vtkSmartPointer<vtkShrinkFilter> shrinkFilter = vtkSmartPointer<vtkShrinkFilter>::New();
    vtkSmartPointer<vtkClipDataSet> clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
    vtkSmartPointer<vtkContourFilter> contourFilter = vtkSmartPointer<vtkContourFilter>::New();
    vtkSmartPointer<vtkSplineFilter> splineFilter = vtkSmartPointer<vtkSplineFilter>::New();
    vtkSmartPointer<vtkTubeFilter> tubeFilter = vtkSmartPointer<vtkTubeFilter>::New();
    vtkSmartPointer<vtkCurvatures> curvature = vtkSmartPointer<vtkCurvatures>::New();

    vtkSmartPointer<vtkNamedColors> colorHandler = vtkSmartPointer<vtkNamedColors>::New();

    vtkSmartPointer<vtkActor> activeActor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> activePolyActor = vtkSmartPointer<vtkActor>::New();
    QColor actorColor;

    vtkSmartPointer<vtkDataSetMapper> activeMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkPolyDataMapper> activePolyMapper = vtkSmartPointer<vtkPolyDataMapper>::New();

    vtkSmartPointer<vtkRenderer> activeRenderer = vtkSmartPointer<vtkRenderer>::New();

    vtkAlgorithmOutput* finalAlgorithm = vtkAlgorithmOutput::New();
    vtkPolyData* finalPolydata = vtkPolyData::New();

    std::vector<int> activeFilters = {0,0,0,0,0,0,0};

    int polyDataUsed = 0;

    int colorAffected = 0;
    double shrinkFactor = 0;

    int tubeFilterRadius = 0;
    int tubeSides = 1;

    int sphereFilterRadius = 0;

    int clipX = 0;
    int clipY = 0;
    int clipZ = 0;
    double clipPart = 0;

    int showWireframe = 0;
    int showPoints = 0;

    int showLight = 0;
    double lightIntensity = 1.0;
    double lightSpecular = 0.0;
    //! function to refresh pipeline
    void refreshPipeline();
    //! function to use pipeline filters
    void filterStage();
    //! function to update active mappers
    void mapperStage();
    //! function to update actor of poly data
    void polyActorStage();
    //! function to update actor of main data
    void actorStage();
    //! function to apply shrink filter
    void initShrinkFilter();
    //! function to apply clip filter
    void initClipFilter();
    //! function to apply contour filter
    void initContourFilter();
    //! function to apply tube filter
    void initTubeFilter();
    //! function to apply curvature filter
    void initCurvatureFilter();

public:
    //! default constructor
    Pipeline();
    //! constructor
    Pipeline(vtkSmartPointer<vtkRenderer>);
    //! function to setup lights
    void setLight();
    //! function to update active pipeline
    void updatePipeline();
    //! function to setup new pipeline
    void setNewPipeline();
    /*! function to get object handler
        \n Arguement: VTKObjectHandler - getObject()
    */
    VTKObjectHandler* getObject();
    /*! function to get active actor
     \n Arguement: vtkSmartPointer<vtkActor> - getActor()
    */
    vtkSmartPointer<vtkActor> getActor();
    /*! function to get active mapper
    \n Arguement: vtkSmartPointer<vtkDataSetMapper> - getMapper()
    */
    vtkSmartPointer<vtkDataSetMapper> getMapper();
    /*! function to get final algorithm
    \return vtkAlgorithmOutput - getAlgorithm()
    */
    vtkAlgorithmOutput* getAlgorithm();
    /*! function to get ploydata
    \return vtkPolyData - GetPolydata()
    */
    vtkPolyData* GetPolydata(); //! have no any relative function on cpp file
    /*! function to get active renderer
    \n Arguement: vtkSmartPointer<vtkRenderer>  - getRenderer()
    */
    vtkSmartPointer<vtkRenderer> getRenderer();
    /*! function to set active Actor
    \return vtkSmartPointer<vtkActor> - set a actor
    */
    void setActor(vtkSmartPointer<vtkActor>);
    /*! function to set active Mapper
    \n Arguments: vtkSmartPointer<vtkDataSetMapper> - set a mapper
    */
    void setMapper(vtkSmartPointer<vtkDataSetMapper>);
    /*! function to set active Algorithm
    \n Arguments: vtkAlgorithmOutput - set a Algorithm
    */
    void setAlgorithm(vtkAlgorithmOutput*);
    /*! function to set active Renderer
    \n Arguments: vtkSmartPointer<vtkRenderer> - set a Renderer
    */
    void setRenderer(vtkSmartPointer<vtkRenderer>);
    /*! function to set active Filters
    \n Arguments: std::vector<int> - set filters
    */
    void setFilters(std::vector<int>);
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
    /*! function enable clip filter to clip on x axis
    \n Arguments: int - enable to clip on x axis
    */
    void enableClipX(int);
    /*! function enable clip filter to clip on y axis
    \n Arguments: int - enable to clip on y axis
    */
    void enableClipY(int);
    /*! function enable clip filter to clip on z axis
    \n Arguments: int - enable to clip on z axis
    */
    void enableClipZ(int);
    /*! function to set shrink factor
    \n Arguments: double - set shrink factor
    */
    void setShrinkFactor(double);
    /*! function to set radius of sphere points filter spheres
    \n Arguments: double - set radius of sphere
    */
    void setSphereRad(double);
    /*! function to set radius of tube filter tubes
    \n Arguments: double - set radius of tube
    */
    void setTubeRad(double);
    /*! function to set number of tube filter tube sides
    \n Arguments: double - set radius of tube
    */
    void setTubeSides(int);
    /*! function to set the value for part of object that is clipped with clip filter
    \n Arguments: double - set clipped with
    */
    void setClipPart(double);
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

#endif //! PIPELINEINFO_H_INCLUDED
