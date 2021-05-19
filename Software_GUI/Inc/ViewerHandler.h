/*! \file ViewerHandler.h File Reference
    \author   Copyright: \n Code part: Danielius Zurlys (StudentID: 20130611)
                         \n Comments part: Danielius Zurlys and Chen Xu  (StudentID: 20187733)
    \brief  build a view part to make the interfacial is better.
*/
#ifndef VIEWERHANDLER_H_INCLUDED
#define VIEWERHANDLER_H_INCLUDED

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

#include "./DataPipeline.h"
#include "./PolyPipeline.h"


class ViewerHandler;

namespace affine{
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
}

/*! \class ViewerHandler
    \brief the major class to change the interface.
*/
class ViewerHandler
{

private:

    DataPipeline* theDataPipeline = new DataPipeline;
    PolyPipeline* thePolyPipeline = new PolyPipeline;


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
    vtkNew<affine::vtkAffineCallback> affineCallback;

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
    //! destructor
   ~ViewerHandler();
    /*! function to setup viewer handler
        \n Arguments:  vtkSmartPointer<vtkRenderWindow>, vtkSmartPointer<vtkRenderWindowInteractor> - viewer handler
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
    \n Arguments: Qcolor - background color
    */
    void changeBackgroundColor(QColor);
    /*! function to get active polydata pipeline
        \return: DataPipeline* - pointer of pipeline to be returned
    */
    DataPipeline* getDataPipeline();
    /*! function to get active data pipeline
        \return: PolyPipeline* - pointer of pipeline to be returned
    */
    PolyPipeline* getPolyPipeline();
    /*! function to allow showing of information text
        \n Arguments: int - information text
    */
    void enableInfo(int);
    /*! function to allow showing of direction
        \n Arguments: int - direction
    */
    void enableAxes(int);
    /*! function to allow showing of object normals
        \n Arguments: int - object normals
    */
    void enableNormals(int);
    /*! function to allow showing of cube axes
        \n Arguments: int - Cube axes
    */
    void enableCubeAxes(int);

    void enableOutline(int);
    /*! function to enable affine mode
        \n Arguments:  int - affine interaction
    */
    void enableAffineInteraction(int);
    /*! function to save the scene as png photo or STL file
        \n Arguments:  Qstring - Scene
    */
    void saveScene(QString);
    //! function to handle mouse doubleclick
};

#endif //! PIPELINEHANDLER_H_INCLUDED
