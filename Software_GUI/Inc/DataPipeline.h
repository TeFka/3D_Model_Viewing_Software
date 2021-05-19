
/*! \file DataPipeline.h File Reference
    \author   Copyright: \n Code part: Danielius Zurlys (StudentID: 20130611)
                         \n Comments part: Danielius Zurlys and Chen Xu (StudentID: 20187733)
    \brief  build a dataset pipeline for VTK.
*/

#ifndef DATAPIPELINE_H_INCLUDED
#define DATAPIPELINE_H_INCLUDED

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

#include "./Pipeline.h"

/*! \class DataPipeline
    \brief sub class of pipeline used to handle dataset object
*/

class DataPipeline : public Pipeline{


private:

    vtkSmartPointer<vtkShrinkFilter> shrinkFilter = vtkSmartPointer<vtkShrinkFilter>::New();
    vtkSmartPointer<vtkClipDataSet> clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
    vtkSmartPointer<vtkSplineFilter> splineFilter = vtkSmartPointer<vtkSplineFilter>::New();
    vtkSmartPointer<vtkTubeFilter> tubeFilter = vtkSmartPointer<vtkTubeFilter>::New();

    vtkSmartPointer<vtkDataSetMapper> activeMapper = vtkSmartPointer<vtkDataSetMapper>::New();


    vtkAlgorithmOutput* finalAlgorithm = vtkAlgorithmOutput::New();

    double shrinkFactor = 0;

    int tubeFilterRadius = 0;
    int tubeSides = 1;

    int sphereFilterRadius = 0;

    int clipX = 0;
    int clipY = 0;
    int clipZ = 0;
    double clipPart = 0;

    //! function to refresh pipeline
    void refreshPipeline();
    //! function to use pipeline filters
    void filterStage();
    //! function to update active mappers
    void mapperStage();
    //! function to update actor of main data
    void actorStage();
    //! function to apply shrink filter
    void initShrinkFilter();
    //! function to apply clip filter
    void initClipFilter();
    //! function to apply tube filter
    void initTubeFilter();

public:
    //! default constructor
    DataPipeline();
    //! constructor
    DataPipeline(vtkSmartPointer<vtkRenderer>);
    //! destructor
    ~DataPipeline();
    //! function to setup lights
    void updatePipeline();
    //! function to setup new pipeline
    void setNewPipeline();
    /*! function to get active mapper
    \return vtkSmartPointer<vtkDataSetMapper> - getMapper()
    */
    vtkSmartPointer<vtkDataSetMapper> getMapper();
    /*! function to get final algorithm
    \return vtkAlgorithmOutput - getAlgorithm()
    */
    vtkAlgorithmOutput* getAlgorithm();
    /*! function to set active Mapper
    \n Arguments: vtkSmartPointer<vtkDataSetMapper> - set a mapper
    */
    void setMapper(vtkSmartPointer<vtkDataSetMapper>);
    /*! function to set active Algorithm
    \n Arguments: vtkAlgorithmOutput - set a Algorithm
    */
    void setAlgorithm(vtkAlgorithmOutput*);

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
};

#endif // DATAPIPELINE_H_INCLUDED
