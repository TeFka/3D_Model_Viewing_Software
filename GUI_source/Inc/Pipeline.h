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
#include <vtkOutlineFilter.h>
#include <vtkOutlineCornerFilter.h>
#include <vtkSplineFilter.h>

#include <vtkIdList.h>

#include "../Inc/Model.h"

#include "./VTKObjectHandler.h"



class Pipeline{


private:

    VTKObjectHandler* theObject = new VTKObjectHandler;

    vtkSmartPointer<vtkShrinkFilter> shrinkFilter = vtkSmartPointer<vtkShrinkFilter>::New();
    vtkSmartPointer<vtkClipDataSet> clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
    vtkSmartPointer<vtkContourFilter> contourFilter = vtkSmartPointer<vtkContourFilter>::New();
    vtkSmartPointer<vtkOutlineFilter> outlineFilter = vtkSmartPointer<vtkOutlineFilter>::New();
    vtkSmartPointer<vtkOutlineCornerFilter> outlineCornerFilter = vtkSmartPointer<vtkOutlineCornerFilter>::New();
    vtkSmartPointer<vtkSplineFilter> splineFilter = vtkSmartPointer<vtkSplineFilter>::New();

    vtkSmartPointer<vtkActor> activeActor = vtkSmartPointer<vtkActor>::New();
    QColor actorColor;

    vtkSmartPointer<vtkDataSetMapper> activeMapper = vtkSmartPointer<vtkDataSetMapper>::New();

    vtkSmartPointer<vtkRenderer> activeRenderer = vtkSmartPointer<vtkRenderer>::New();

    vtkAlgorithmOutput* finalAlgorithm;

    std::vector<int> activeFilters = {0,0,0,0,0,0};

    double shrinkFactor = 0;
    int clipX = 0;
    int clipY = 0;
    int clipZ = 0;
    double clipPart = 0;

    int showWireframe = 0;
    int showPoints = 0;

    int showLight = 0;

    int actorSetupRequired = 0;

    void refreshPipeline();
    void filterStage();
    void mapperStage();
    void actorStage();

    void initShrinkFilter();
    void initClipFilter();
    void initContourFilter();

public:
    Pipeline();
    Pipeline(vtkSmartPointer<vtkRenderer>);

    void updatePipeline();

    void setNewPipeline();

    VTKObjectHandler* getObject();
    vtkSmartPointer<vtkActor> getActor();
    vtkSmartPointer<vtkDataSetMapper> getMapper();
    vtkAlgorithmOutput* getAlgorithm();

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

};

#endif // PIPELINEINFO_H_INCLUDED
