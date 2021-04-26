#ifndef PIPELINEINFO_H_INCLUDED
#define PIPELINEINFO_H_INCLUDED

#include "./VTKObject.h"

class Pipeline{


private:
    vtkSmartPointer<vtkActor> activeActor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkUnstructuredGrid> activeGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkSTLReader> activeReader = vtkSmartPointer<vtkSTLReader>::New();
    vtkSmartPointer<vtkNamedColors> activeColors = vtkSmartPointer<vtkNamedColors>::New();

    vtkSmartPointer<vtkRenderer> activeRenderer = vtkSmartPointer<vtkRenderer>::New();

    vtkSmartPointer<vtkRenderer> activeRenderer = vtkSmartPointer<vtkRenderer>::New();

    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderWindow> activeRenderWindow;

    vtkAlgorithmOutput* finalAlgorithm;

    int objectType = 0;

    //clip filter
    double clipOriginPart = 0.0;

public:
    Pipeline();
    Pipeline(vtkSmartPointer<vtkRenderer>);

    void refreshPipeline();
    void defineSource();
    void filterStage();
    void mapperStage();
    void actorStage();

    vtkSmartPointer<vtkActor> getActor();
    vtkSmartPointer<vtkUnstructuredGrid> getGrid();
    vtkAlgorithmOutput* getAlgorithmOutout();

};

#endif // PIPELINEINFO_H_INCLUDED
