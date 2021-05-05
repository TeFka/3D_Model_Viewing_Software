#ifndef PIPELINEHANDLER_H_INCLUDED
#define PIPELINEHANDLER_H_INCLUDED

#include <string>
#include <math.h>
#include <QMainWindow>
#include <vtkSmartPointer.h>

#include <vtkCubeSource.h>

#include <vtkAxesActor.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>

#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkLookupTable.h>
#include <vtkPoints.h>
#include <vtkNew.h>
#include <vtkLight.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QFileDialog.h>
#include <QSlider>
#include <QAbstractSlider>
#include <vtkUnstructuredGrid.h>
#include <QColorDialog>
#include <vtkInteractorStyleTrackballCamera.h>

#include <vtkTextActor.h>
#include <vtkTextProperty.h>

#include <vtkTransform.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkRenderWindowInteractor.h>

#include "./Pipeline.h"

class ViewerHandler{

private:

    Pipeline* thePipeline = new Pipeline;

    vtkSmartPointer<vtkRenderer> activeRenderer = vtkSmartPointer<vtkRenderer>::New();

    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderWindow> activeRenderWindow;

    vtkSmartPointer<vtkNamedColors> colorHandler = vtkSmartPointer<vtkNamedColors>::New();

    vtkSmartPointer<vtkTextActor> tempVolumeTextActor = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> tempMaxCellNumTextActor = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> tempWeightTextActor = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> tempPositionTextActor = vtkSmartPointer<vtkTextActor>::New();

    vtkNew<vtkAxesActor> axes;

    int showInfo = 0;
    int showAxes = 0;
    int axesExist = 0;

public:
    ViewerHandler();
    ViewerHandler(vtkSmartPointer<vtkRenderWindow>);

    void setup(vtkSmartPointer<vtkRenderWindow>);

    void refreshRender();

    void setText();
    void updateText();
    void updateAxes(double=1.0, double=0.0, double=0.0);

    void viewNewObject();
    void updateViewer();

    void setCameraOrientationPosX();
    void setCameraOrientationNegX();
    void setCameraOrientationPosY();
    void setCameraOrientationNegY();
    void setCameraOrientationPosZ();
    void setCameraOrientationNegZ();
    void setCameraOrientationPosShift();
    void setCameraOrientationNegShift();
    void setCameraOrientationPosRotate();
    void setCameraOrientationNegRotate();

    void resetViewer();
    void resetCamera();
    void changeBackgroundColor(QColor);

    Pipeline* getPipeline();

    void enableInfo(int);
    void enableAxes(int);

};

#endif // PIPELINEHANDLER_H_INCLUDED
