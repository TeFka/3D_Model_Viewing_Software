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

#include "../Inc/Model.h"
#include "./apphelp.h"
#include "./newshapechoice.h"

#include "./Pipeline.h"
#include "./VTKObjectHandler.h"

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
    Model activeVTKModel;

    vtkSmartPointer<vtkGeometryFilter> geometryFilter = vtkSmartPointer<vtkGeometryFilter>::New();
    vtkSmartPointer<vtkShrinkFilter> shrinkFilter = vtkSmartPointer<vtkShrinkFilter>::New();
    vtkSmartPointer<vtkClipDataSet> clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
    vtkSmartPointer<vtkContourFilter> contourFilter = vtkSmartPointer<vtkContourFilter>::New();
    vtkSmartPointer<vtkOutlineFilter> outlineFilter = vtkSmartPointer<vtkOutlineFilter>::New();
    vtkSmartPointer<vtkOutlineCornerFilter> outlineCornerFilter = vtkSmartPointer<vtkOutlineCornerFilter>::New();
    vtkSmartPointer<vtkSplineFilter> splineFilter = vtkSmartPointer<vtkSplineFilter>::New();

    vtkSmartPointer<vtkUnstructuredGrid> activeGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkDataSetMapper> activeMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkActor> activeActor = vtkSmartPointer<vtkActor>::New();

    Ui::MainWindow * ui;
    QString activeFileName;
    vtkSmartPointer<vtkSTLReader> activeReader = vtkSmartPointer<vtkSTLReader>::New();
    vtkSmartPointer<vtkNamedColors> activeColors = vtkSmartPointer<vtkNamedColors>::New();

    vtkSmartPointer<vtkRenderer> activeRenderer = vtkSmartPointer<vtkRenderer>::New();

    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderWindow> activeRenderWindow;

    vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();

    vtkSmartPointer<vtkMassProperties> objectParameters = vtkSmartPointer<vtkMassProperties>::New();

    vtkNew<vtkAxesActor> axes;

    QColor activeColor;
    std::vector<std::array<double,4>> separateCellColors;

    int objectType = 0;

    Vector3D objectDimensions;
    Vector3D objectPosition;

    double objectVolume = 0.0;
    double objectWeight = 0.0;

    int allowGUIChange = 1;
    //clip filter
    double clipOriginPart = 0.0;

    void refreshRender();
    void refreshGrid();
    void refreshGUI();
    void updateObject();

    void updateVTKModel();

    void updateText();

    void updateAxes(double=1.0, double=0.0, double=0.0, int=0);

    void updatePoints(vtkSmartPointer<vtkPoints>);

    void updateViewer();

    void makeMeasurement();

    void initFilter(int);

    vtkAlgorithmOutput* filterStage(vtkAlgorithmOutput*, int);

    void mapperStage(vtkAlgorithmOutput*);

    void drawHexahedron(Cell*,vtkSmartPointer<vtkUnstructuredGrid>);
    void drawTetrahedron(Cell*,vtkSmartPointer<vtkUnstructuredGrid>);
    void drawPyramid(Cell*,vtkSmartPointer<vtkUnstructuredGrid>);

    void displayHexahedron();
    void displayTetrahedron();
    void displayPyramid();
    void displaySphere();
    void displayDisk();
    void displayCone();
    void displayPlane();
    void displayPointCluster(int);
    void displayLine();
    void displayCylinder();

public slots:

    void handleUpdate();
    void changeClipValue(int);

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
