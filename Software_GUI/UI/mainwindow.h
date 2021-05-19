
/*! \file mainwindow.h File Reference
    \author   Copyright: \n Code part: Danielius Zurlys (StudentID: 20130611)
                         \n Comments part: Danielius Zurlys  (StudentID: 20130611)
    \brief Create a window that will manage software operation
*/

// mainwindow.h---------------------------------------------------------------
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <string>
#include <math.h>
#include <QMainWindow>
#include <QCoreApplication>
#include <vtkSmartPointer.h>

#include <vtkConeSource.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkCylinderSource.h>
#include <vtkDiskSource.h>
#include <vtkLineSource.h>
#include <vtkPlaneSource.h>
#include <vtkPointSource.h>

#include <vtkAxesActor.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkCellData.h>

#include <vtkSTLReader.h>
#include <vtkSTLWriter.h>

#include <vtkDataSetMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkHexahedron.h>
#include <vtkTetra.h>
#include <vtkPyramid.h>
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
#include <vtkPlane.h>
#include <vtkClipDataSet.h>
#include <vtkShrinkFilter.h>
#include <vtkGeometryFilter.h>
#include <vtkContourFilter.h>
#include <vtkOutlineFilter.h>
#include <vtkOutlineCornerFilter.h>
#include <vtkSplineFilter.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <vtkTextActor.h>
#include <vtkTextProperty.h>

#include <vtkMassProperties.h>

#include <vtkTransform.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkGlyph3DMapper.h>

#include "../../Model_Library/Inc/Model.h"
#include "./apphelp.h"
#include "./newshapechoice.h"

#include "../Inc/ViewerHandler.h"

namespace Ui
{
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget * parent = 0);
//MainWindow();
    ~MainWindow();
private:

    ViewerHandler* appHandler = new ViewerHandler;

    Ui::MainWindow* ui;

    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderWindow> activeRenderWindow = vtkSmartPointer<vtkRenderWindow>::New();

    vtkSmartPointer<vtkRenderer> activeRenderer = vtkSmartPointer<vtkRenderer>::New();

    QString activeFileName;

    int allowGUIChange = 1;

    /*! function to refresh rendering
        \return none
    */
    void refreshRender();

    /*! function to refresh active GUI and set all components to default
        \return none
    */
    void refreshGUI();

    /*! function to refresh all active GUI components that are related to object modification
        \return none
    */
    void refreshObjectGUI();

public slots:

    /*! function to handle change of GUI components that control object initial geometry
        \return none
    */
    void handleGeometryUpdate();

    /*! function to handle general changes of GUI.
        \return none
    */
    void handleUpdate();

    /*! function to handle change of GUI sliders.
        \return none
    */
    void handleSliderUpdate();

    /*! function to handle change of chosen filters.
        \return none
    */
    void handleFilterUpdate();

    /*! function to handle change of chosen minimum amount of shown cells
        \return none
    */
    void handleMinCellChange();

    /*! function to handle change of chosen maximum amount of shown cells
        \return none
    */
    void handleMaxCellChange();

    /*! function to handle opening and retrieving of models from files
        \return none
    */
    void handleOpenButton();

    /*! function to handle saving of model geometry
        \return none
    */
    void handleSaveModelButton();

    /*! function to handle saving of model with all effects
        \return none
    */
    void handleSaveSceneButton();

    /*! function to handle opening ov helper window
        \return none
    */
    void handleHelpButton();

    /*! function to handle choice of a new object
        \return none
    */
    void handleNewButton();

    /*! function to change camera orientation to positive X axis
        \return none
    */
    void setCameraOrientationPosX();
    /*! function to change camera orientation to negative X axis
        \return none
    */
    void setCameraOrientationNegX();
    /*! function to change camera orientation to positive Y axis
        \return none
    */
    void setCameraOrientationPosY();
    /*! function to change camera orientation to negative Y axis
        \return none
    */
    void setCameraOrientationNegY();
    /*! function to change camera orientation to positive XZ axis
        \return none
    */
    void setCameraOrientationPosZ();
    /*! function to change camera orientation to negative XZ axis
        \return none
    */
    void setCameraOrientationNegZ();
    /*! function to change camera orientation to the right
        \return none
    */
    void setCameraOrientationPosShift();
    /*! function to change camera orientation to the left
        \return none
    */
    void setCameraOrientationNegShift();

    /*! function to rotate camera orientation to the right
        \return none
    */
    void setCameraOrientationPosRotate();

    /*! function to rotate camera orientation to the left
        \return none
    */
    void setCameraOrientationNegRotate();
    /*! function to reset model and all viewer components
        \return none
    */
    void resetViewer();
    /*! function to reset all model modifications
        \return none
    */
    void resetObject();
    /*! function to reset camera orientation to default
        \return none
    */
    void resetCamera();
    /*! function to change background color
        \return none
    */
    void changeBackgroundColor();

    /*! function to change model color
        \return none
    */
    void changeObjectColor();

    /*! function to reset model color to default
        \return none
    */
    void resetObjectColor();

signals:

    /*! function to update status message
        \return none
    */
    void statusUpdateMessage( const QString & message, int timeout );
};


#endif // MAINWINDOW_H
//mainwindow.h----------------------------------------------------------------
