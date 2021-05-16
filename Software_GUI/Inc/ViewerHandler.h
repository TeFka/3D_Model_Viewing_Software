/*! \file ViewerHandler.h File Reference
    \author   Copyright: \n Code part: Danielius Zurlys (StudentID: 20130611)
                         \n Comments part: Danielius Zurlys and Chen Xu  (StudentID: 20187733)
    \brief  build a view part to make the interfacial is better.
*/
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

#include <vtkOutlineFilter.h>

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
/*! \class vtkAffineCallback
    \brief  build a view part to make the interfacial is better.
*/
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
/*! \class MouseInteractorStyleDoubleClick
    \brief setup handler of mouse interactor for double clicking

*/
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




/*! \class ViewerHandler
    \brief the major class to change the interface.
*/
class ViewerHandler
{

private:

    Pipeline* thePipeline = new Pipeline;

    vtkSmartPointer<vtkRenderer> activeRenderer = vtkSmartPointer<vtkRenderer>::New();

    vtkNew<vtkGenericOpenGLRenderWindow> OPENGLrenderWindow;
    vtkSmartPointer<vtkRenderWindow> activeRenderWindow;

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    vtkSmartPointer<vtkOutlineFilter> outline = vtkSmartPointer<vtkOutlineFilter>::New();

    vtkSmartPointer<vtkNamedColors> colorHandler = vtkSmartPointer<vtkNamedColors>::New();
    vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New();

    vtkSmartPointer<vtkTextActor> volumeTextActor = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> maxCellNumTextActor = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> weightTextActor = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> positionTextActor = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> pointsTextActor = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> boundTextActor = vtkSmartPointer<vtkTextActor>::New();

    vtkNew<vtkAxesActor> axesActor;
    vtkNew<vtkActor> normalsActor;
    vtkNew<vtkCubeAxesActor> cubeAxesActor;
    vtkNew<vtkActor> outlineActor;

    vtkNew<vtkOrientationMarkerWidget> axesWidget;
    vtkNew<vtkAffineWidget> affineWidget;
    vtkNew<vtkAffineCallback> affineCallback;

    vtkNew<MouseInteractorStyleDoubleClick> doubleClickInteratction;

    int showInfo = 0;

    int showAxes = 0;
    int axesExist = 0;
    int cubeAxesExist = 0;
    int outlineExist = 0;

    int showNormals = 0;
    int normalsExist = 0;
    int showCubeAxes = 0;
    int showOutline = 0;

    //! setup text operation
    void setText();

    //! function to update shown text
    void updateText();

    //! function to setup direction axes operation
    void setAxes();

    //! function to setup cube axes operation
    void updateCubeAxes();

    //! function to update normals of object surface
    void updateNormals();


    void updateOutline();


    void updateComponents();

    //! setup other components
    void setupComponents();

public:
    //! default constructor
    ViewerHandler();
    //! constructor
    ViewerHandler(vtkSmartPointer<vtkRenderWindow>, vtkSmartPointer<vtkRenderWindowInteractor>);
    /*! function to setup viewer handler
        \return  vtkSmartPointer<vtkRenderWindow>, vtkSmartPointer<vtkRenderWindowInteractor> - viewer handler
    */
    void setup(vtkSmartPointer<vtkRenderWindow>, vtkSmartPointer<vtkRenderWindowInteractor>);
    //! function to refresh rendering
    void refreshRender();
    //! function to handle setup and viewing of new object
    void viewNewObject();
    //! function to update viewer
    void updateViewer();
    //! setup affine mode operation
    void setAffineInteraction();
    //! function to handle updates from affine mode
    void updateAffineInteraction();
    //! function to set camera orientation to positive X
    void setCameraOrientationPosX();
    //! function to set camera orientation to negative X
    void setCameraOrientationNegX();
    //! function to set camera orientation to positive Y
    void setCameraOrientationPosY();
    //! function to set camera orientation to negative Y
    void setCameraOrientationNegY();
    //! function to set camera orientation to positive Z
    void setCameraOrientationPosZ();
    //! function to set camera orientation to negative Z
    void setCameraOrientationNegZ();
    //! function to shift camera position by 90 degrees to the right
    void setCameraOrientationPosShift();
    //! function to rotate camera by 90 degrees to the right
    void setCameraOrientationNegShift();
    //! function to rotate camera by 90 degrees to the right
    void setCameraOrientationPosRotate();
    //! function to rotate camera by 90 degrees to the right
    void setCameraOrientationNegRotate();
    //! function to reset viewer
    void resetViewer();
    //! function to reset just the object properties
    void resetObject();
    //! function to reset camera
    void resetCamera();
    /*! function to change background color
    \return Qcolor - background color
    */
    void changeBackgroundColor(QColor);
    /*! function to get active pipeline
        \n Arguement: Pipeline - getPipeline()
    */
    Pipeline* getPipeline();
    /*! function to allow showing of information text
        \return int - information text
    */
    void enableInfo(int);
    /*! function to allow showing of direction
        \return int - direction
    */
    void enableAxes(int);
    /*! function to allow showing of object normals
        \return int - object normals
    */
    void enableNormals(int);
    /*! function to allow showing of cube axes
        \return int - Cube axes
    */
    void enableCubeAxes(int);

    void enableOutline(int);
    /*! function to enable affine mode
        \return  int - affine interaction
    */
    void enableAffineInteraction(int);
    /*! function to save the scene as png photo or STL file
        \return Qstring - Scene
    */
    void saveScene(QString);
    //! function to handle mouse doubleclick
    void mouseClick();
};

#endif //! PIPELINEHANDLER_H_INCLUDED
