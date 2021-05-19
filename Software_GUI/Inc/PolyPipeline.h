/*! \file PolyPipeline.h File Reference
    \author   Copyright: \n Code part: Danielius Zurlys (StudentID: 20130611)
                         \n Comments part: Danielius Zurlys and Chen Xu  (StudentID: 20187733)
    \brief  build a polydata pipeline for VTK.
*/

#ifndef POLYPIPELINE_H_INCLUDED
#define POLYPIPELINE_H_INCLUDED

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

/*! \class PolyPipeline
    \brief  sub class of pipeline used to handle poly data
*/

class PolyPipeline : public Pipeline{

private:

    VTKObjectHandler* theObject = new VTKObjectHandler;

    vtkSmartPointer<vtkCurvatures> curvature = vtkSmartPointer<vtkCurvatures>::New();

    vtkSmartPointer<vtkPolyDataMapper> activePolyMapper = vtkSmartPointer<vtkPolyDataMapper>::New();

    vtkSmartPointer<vtkRenderer> activeRenderer = vtkSmartPointer<vtkRenderer>::New();

    vtkPolyData* finalPolydata = vtkPolyData::New();

    int colorAffected = 0;

    //! function to refresh pipeline
    void refreshPipeline();
    //! function to refresh pipeline
    void filterStage();
    //! function to update active mappers
    void mapperStage();
    //! function to update actor of main data
    void actorStage();
    //! function to apply contour filter
    void initContourFilter();
public:
    //! default constructor
    PolyPipeline();
    //! constructor
    PolyPipeline(vtkSmartPointer<vtkRenderer>);
    //! destructor
    ~PolyPipeline();
    //! function to setup lights
    void setLight();
    //! function to update active pipeline
    void updatePipeline();
    //! function to setup new pipeline
    void setNewPipeline();
    /*! function to get the active mapper
        \n Argument: vtkSmartPointer<vtkPolyDataMapper> - mapper smart pointer
    */
    vtkSmartPointer<vtkPolyDataMapper> getMapper();
    /*! function to get final polydata
    \return vtkPolyData* - polydata pointer
    */
    vtkPolyData* getPolydata(); //! have no any relative function on cpp file
    /*! function to set active mapper
    \n Argument: vvtkSmartPointer<vtkPolyDataMapper>  - mapper to set
    */
    void setMapper(vtkSmartPointer<vtkPolyDataMapper>);
    /*! function to set active polydata
    \n Arguments: vtkPolyData - polydata to set
    */
    void setPolydata(vtkPolyData*); //! have no any relative function on cpp file

};

#endif // POLYPIPELINE_H_INCLUDED
