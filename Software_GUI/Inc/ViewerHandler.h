#ifndef PIPELINEHANDLER_H_INCLUDED
#define PIPELINEHANDLER_H_INCLUDED

#include <string>
#include <math.h>
#include <QMainWindow>
#include <vtkSmartPointer.h>

#include <vtkCubeSource.h>
#include <vtkArrowSource.h>

#include <vtkAxesActor.h>
#include <vtkCubeAxesActor.h>

#include <vtkAffineRepresentation2D.h>
#include <vtkAffineWidget.h>

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

#include <vtkPCANormalEstimation.h>

#include <vtkTextActor.h>
#include <vtkTextProperty.h>

#include <vtkPNGWriter.h>
#include <vtkWindowToImageFilter.h>

#include <vtkTransform.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkRenderWindowInteractor.h>

#include "./Pipeline.h"

class ViewerHandler{

private:

    Pipeline* thePipeline = new Pipeline;

    vtkSmartPointer<vtkRenderer> activeRenderer = vtkSmartPointer<vtkRenderer>::New();

    vtkNew<vtkGenericOpenGLRenderWindow> OPENGLrenderWindow;
    vtkSmartPointer<vtkRenderWindow> activeRenderWindow;

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    vtkSmartPointer<vtkNamedColors> colorHandler = vtkSmartPointer<vtkNamedColors>::New();

    vtkSmartPointer<vtkTextActor> volumeTextActor = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> maxCellNumTextActor = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> weightTextActor = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> positionTextActor = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> pointsTextActor = vtkSmartPointer<vtkTextActor>::New();

    vtkNew<vtkAxesActor> axesActor;
    vtkNew<vtkActor> normalsActor;
    vtkNew<vtkCubeAxesActor> cubeAxesActor;

    vtkNew<vtkOrientationMarkerWidget> axesWidget;

    int showInfo = 0;

    int showAxes = 0;
    int axesExist = 0;
    int cubeAxesExist = 0;

    int showNormals = 0;
    int normalsExist = 0;
    int showCubeAxes = 0;

public:
    ViewerHandler();
    ViewerHandler(vtkSmartPointer<vtkRenderWindow>, vtkSmartPointer<vtkRenderWindowInteractor>);

    void setup(vtkSmartPointer<vtkRenderWindow>, vtkSmartPointer<vtkRenderWindowInteractor>);

    void refreshRender();

    void setText();
    void updateText();

    void setAxes();
    void updateCubeAxes();

    void viewNewObject();
    void updateViewer();
    void updateNormals();

    void updateAffineInteraction();

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
    void resetObject();
    void resetCamera();
    void changeBackgroundColor(QColor);

    Pipeline* getPipeline();

    void enableInfo(int);
    void enableAxes(int);
    void enableNormals(int);
    void enableCubeAxes(int);

    void saveScene(QString);
};

#endif // PIPELINEHANDLER_H_INCLUDED
