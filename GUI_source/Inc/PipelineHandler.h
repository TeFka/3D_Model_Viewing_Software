#ifndef PIPELINEHANDLER_H_INCLUDED
#define PIPELINEHANDLER_H_INCLUDED

#include "./Pipeline.h"

class PipelineHandler{

private:
    Pipeline thePipeline;

    vtkSmartPointer<vtkRenderer> activeRenderer = vtkSmartPointer<vtkRenderer>::New();

    vtkSmartPointer<vtkRenderer> activeRenderer = vtkSmartPointer<vtkRenderer>::New();

    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderWindow> activeRenderWindow;

    vtkAlgorithmOutput* finalAlgorithm;

    int objectType = 0;

    //clip filter
    double clipOriginPart = 0.0;

public:
    PipelineHandler();



    vtkSmartPointer<vtkActor> getActor();
    vtkSmartPointer<vtkUnstructuredGrid> getGrid();
    vtkAlgorithmOutput* getAlgorithmOutout();

};

#endif // PIPELINEHANDLER_H_INCLUDED
