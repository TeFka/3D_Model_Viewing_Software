#ifndef POLYPIPELINE_H_INCLUDED
#define POLYPIPELINE_H_INCLUDED

/*! \file PolyPipeline.h File Reference
    \author   Copyright: \n Code part: Danielius Zurlys (StudentID: 20130611)
                         \n Comments part: Danielius Zurlys and Chen Xu  (StudentID: 20187733)
    \brief  build a pipeline part for VTK.
*/

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

/*! \class PolyPipeline
    \brief  sub class of pipeline used to handle poly data
*/

class Polypipeline : public Pipeline{

    VTKObjectHandler* theObject = new VTKObjectHandler;

    vtkSmartPointer<vtkCurvatures> curvature = vtkSmartPointer<vtkCurvatures>::New();

    vtkSmartPointer<vtkPolyDataMapper> activePolyMapper = vtkSmartPointer<vtkPolyDataMapper>::New();

    vtkSmartPointer<vtkRenderer> activeRenderer = vtkSmartPointer<vtkRenderer>::New();

    vtkPolyData* finalPolydata = vtkPolyData::New();

    std::vector<int> activeFilters = {0};

    //! function to refresh pipeline
    void filterStage();
    //! function to update active mappers
    void mapperStage();
    //! function to apply contour filter
    void initContourFilter();
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
        \n Argument: VTKObjectHandler - getObject()
    */

    vtkSmartPointer<vtkPolyDataMapper> getMapper();
    /*! function to get final algorithm
    \return vtkAlgorithmOutput - getAlgorithm()
    */
    vtkPolyData* setPolydata(); //! have no any relative function on cpp file
    /*! function to get active renderer
    \n Arguement: vtkSmartPointer<vtkRenderer>  - getRenderer()
    */
    void setMapper(vtkSmartPointer<vtkPolyDataMapper>);
    /*! function to set active Algorithm
    \n Arguments: vtkAlgorithmOutput - set a Algorithm
    */
    void setPolydata(vtkPolyData*); //! have no any relative function on cpp file
    /*! function to get active renderer
    \n Arguement: vtkSmartPointer<vtkRenderer>  - getRenderer()
    */
    void setFilters(std::vector<int>);
    /*! function to enable object wireframe state
    \n Arguments: int - enable wireframe
    */
};

#endif // POLYPIPELINE_H_INCLUDED
