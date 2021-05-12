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

class ViewerHandler;

namespace
{
class vtkAffineCallback : public vtkCommand
{
public:
    static vtkAffineCallback* New()
    {
        return new vtkAffineCallback;
    }
    virtual void Execute(vtkObject* caller, unsigned long, void*);
    vtkAffineCallback() : Actor(0), AffineRep(0)
    {
        this->Transform = vtkTransform::New();
    }
    ~vtkAffineCallback()
    {
        this->Transform->Delete();
    }
    vtkActor* Actor;
    vtkAffineRepresentation2D* AffineRep;
    vtkTransform* Transform;
};
} // namespace

namespace
{
// Define interaction style
class MouseInteractorStyleDoubleClick : public vtkInteractorStyleTrackballCamera
{
public:
    static MouseInteractorStyleDoubleClick* New();
    vtkTypeMacro(MouseInteractorStyleDoubleClick,
                 vtkInteractorStyleTrackballCamera);

    MouseInteractorStyleDoubleClick() : NumberOfClicks(0), ResetPixelDistance(5)
    {
        this->PreviousPosition[0] = 0;
        this->PreviousPosition[1] = 0;
    }


    virtual void OnLeftButtonDown() override
    {
        this->NumberOfClicks++;
        int pickPosition[2];
        this->GetInteractor()->GetEventPosition(pickPosition);

        int xdist = pickPosition[0] - this->PreviousPosition[0];
        int ydist = pickPosition[1] - this->PreviousPosition[1];

        this->PreviousPosition[0] = pickPosition[0];
        this->PreviousPosition[1] = pickPosition[1];

        int moveDistance = (int)sqrt((double)(xdist * xdist + ydist * ydist));

        // Reset numClicks - If mouse moved further than resetPixelDistance
        if (moveDistance > this->ResetPixelDistance)
        {
            this->NumberOfClicks = 1;
        }

        if (this->NumberOfClicks == 2)
        {
            std::cout<<"yes"<<std::endl;
            this->NumberOfClicks = 0;
        }

        // forward events
        vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }

    void setupHandler(ViewerHandler*);

private:
    ViewerHandler* handler;
    unsigned int NumberOfClicks;
    int PreviousPosition[2];
    int ResetPixelDistance;
};
vtkStandardNewMacro(MouseInteractorStyleDoubleClick);
} // namespace

class ViewerHandler
{

private:

    Pipeline* thePipeline = new Pipeline;

    vtkSmartPointer<vtkRenderer> activeRenderer = vtkSmartPointer<vtkRenderer>::New();

    vtkNew<vtkGenericOpenGLRenderWindow> OPENGLrenderWindow;
    vtkSmartPointer<vtkRenderWindow> activeRenderWindow;

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    vtkSmartPointer<vtkNamedColors> colorHandler = vtkSmartPointer<vtkNamedColors>::New();
    vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New();

    vtkSmartPointer<vtkTextActor> volumeTextActor = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> maxCellNumTextActor = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> weightTextActor = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> positionTextActor = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> pointsTextActor = vtkSmartPointer<vtkTextActor>::New();

    vtkNew<vtkAxesActor> axesActor;
    vtkNew<vtkActor> normalsActor;
    vtkNew<vtkCubeAxesActor> cubeAxesActor;

    vtkNew<vtkOrientationMarkerWidget> axesWidget;
    vtkNew<vtkAffineWidget> affineWidget;
    vtkNew<vtkAffineCallback> affineCallback;

    vtkNew<MouseInteractorStyleDoubleClick> doubleClickInteratction;

    int showInfo = 0;

    int showAxes = 0;
    int axesExist = 0;
    int cubeAxesExist = 0;

    int showNormals = 0;
    int normalsExist = 0;
    int showCubeAxes = 0;

    void setupComponents();

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

    void setAffineInteraction();
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
    void enableAffineInteraction(int);

    void saveScene(QString);

    void mouseClick();
};

#endif // PIPELINEHANDLER_H_INCLUDED
