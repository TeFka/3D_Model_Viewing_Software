// mainwindow.h---------------------------------------------------------------
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <string>
#include <math.h>
#include <QMainWindow>
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

#include "../Model_Library/Inc/Model.h"
#include "./apphelp.h"
#include "./newshapechoice.h"

#include "./Inc/ViewerHandler.h"

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

    void refreshRender();
    void refreshGUI();

public slots:

    void handleUpdate();
    void handleFilterUpdate();
    void handleMinCellChange();
    void handleMaxCellChange();

    void handleOpenButton();
    void handleSaveButton();
    void handleHelpButton();
    void handleNewButton();

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
    void changeBackgroundColor();
    void changeObjectColor();
    void resetObjectColor();

signals:
    void statusUpdateMessage( const QString & message, int timeout );
};
#endif // MAINWINDOW_H
//mainwindow.h----------------------------------------------------------------
