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

#include <vtkExtractEdges.h>

#include <vtkIdList.h>

#include "./VTKObjectHandler.h"



class Pipeline{


private:

    VTKObjectHandler* theObject = new VTKObjectHandler;

    vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();

    vtkSmartPointer<vtkShrinkFilter> shrinkFilter = vtkSmartPointer<vtkShrinkFilter>::New();
    vtkSmartPointer<vtkClipDataSet> clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
    vtkSmartPointer<vtkContourFilter> contourFilter = vtkSmartPointer<vtkContourFilter>::New();
    vtkSmartPointer<vtkSplineFilter> splineFilter = vtkSmartPointer<vtkSplineFilter>::New();
    vtkSmartPointer<vtkTubeFilter> tubeFilter = vtkSmartPointer<vtkTubeFilter>::New();;

    vtkSmartPointer<vtkActor> activeActor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> activePolyActor = vtkSmartPointer<vtkActor>::New();
    QColor actorColor;

    vtkSmartPointer<vtkDataSetMapper> activeMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkPolyDataMapper> activePolyMapper = vtkSmartPointer<vtkPolyDataMapper>::New();

    vtkSmartPointer<vtkRenderer> activeRenderer = vtkSmartPointer<vtkRenderer>::New();

    vtkAlgorithmOutput* finalAlgorithm = vtkAlgorithmOutput::New();

    std::vector<int> activeFilters = {0,0,0,0,0,0,0};

    int polyDataUsed = 0;
    double shrinkFactor = 0;
    int clipX = 0;
    int clipY = 0;
    int clipZ = 0;
    double clipPart = 0;

    int showWireframe = 0;
    int showPoints = 0;

    int showLight = 0;
    double lightIntensity = 1.0;
    double lightSpecular = 0.0;

    int actorSetupRequired = 0;

    void refreshPipeline();
    void filterStage();
    void mapperStage();
    void polyActorStage();
    void actorStage();

    void initShrinkFilter();
    void initClipFilter();
    void initContourFilter();
    void initTubeFilter();
    void initCurvatureFilter();

public:
    Pipeline();
    Pipeline(vtkSmartPointer<vtkRenderer>);

    void setLight();

    void updatePipeline();

    void setNewPipeline();

    VTKObjectHandler* getObject();
    vtkSmartPointer<vtkActor> getActor();
    vtkSmartPointer<vtkDataSetMapper> getMapper();
    vtkAlgorithmOutput* getAlgorithm();
    vtkPolyData* GetPolydata();

    vtkSmartPointer<vtkRenderer> getRenderer();

    void setActor(vtkSmartPointer<vtkActor>);
    void setMapper(vtkSmartPointer<vtkDataSetMapper>);
    void setAlgorithm(vtkAlgorithmOutput*);

    void setRenderer(vtkSmartPointer<vtkRenderer>);

    void setFilters(std::vector<int>);

    void enableWireframe(int);
    void enablePoints(int);
    void enableLight(int);

    void enableClipX(int);
    void enableClipY(int);
    void enableClipZ(int);

    void setShrinkFactor(double);
    void setClipPart(double);
    void setLightIntensity(double);
    void setLightSpecular(double);
    void setOpacity(double);

};

#endif // PIPELINEINFO_H_INCLUDED
