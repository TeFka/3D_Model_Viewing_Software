// mainwindow.h---------------------------------------------------------------
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkDataSetMapper.h>
#include <vtkHexahedron.h>
#include <vtkTetra.h>
#include <vtkPyramid.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
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

#include "../Inc/Model.h"

class MouseInteractor : public vtkInteractorStyleTrackballCamera
{
private:

public:
    static MouseInteractor* New();

    virtual void OnLeftButtonDown()
    {

        // Forward events
        vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }

    virtual void OnRightButtonDown()
    {
        // Forward events
        vtkInteractorStyleTrackballCamera::OnRightButtonDown();
    }

    virtual void OnMouseWheelForward()
    {
        // Forward events
        vtkInteractorStyleTrackballCamera::OnMouseWheelForward();
    }

    virtual void OnMouseWheelBackward()
    {
        // Forward events
        vtkInteractorStyleTrackballCamera::OnMouseWheelBackward();
    }

};

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

    int activeFilters[7] = {0,0,0,0,0,0,0};

    std::vector<vtkSmartPointer<vtkUnstructuredGrid>> uGrids;
    std::vector<vtkSmartPointer<vtkDataSetMapper>> mappers;
    std::vector<vtkSmartPointer<vtkActor>> actors;

    Ui::MainWindow * ui;
    QString activeFileName;
    vtkSmartPointer<vtkSTLReader> activeReader = vtkSmartPointer<vtkSTLReader>::New();
    vtkSmartPointer<vtkNamedColors> activeColors = vtkSmartPointer<vtkNamedColors>::New();

    vtkSmartPointer<vtkRenderer> activeRenderer = vtkSmartPointer<vtkRenderer>::New();

    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderWindow> activeRenderWindow;

    vtkSmartPointer<vtkLight> activeLight = vtkSmartPointer<vtkLight>::New();
    vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
    std::vector<std::array<double, 3>> pointCoordinates;

    bool clipFilterON = false;
    bool shrinkFilterON = false;

    int objectType = 0;

    MouseInteractor mouseInteractor();

    void refreshRender();
    void refreshGrid();

    void initFilter(int);

    vtkAlgorithmOutput* filterStage(vtkAlgorithmOutput*, int);
    vtkSmartPointer<vtkDataSetMapper> mapperStage(vtkSmartPointer<vtkUnstructuredGrid>);
    vtkSmartPointer<vtkDataSetMapper> mapperStage(vtkAlgorithmOutput*);

public slots:

    void handleFilter(int);

    void handleOpenButton();
    void changeLight(int);
    vtkSmartPointer<vtkUnstructuredGrid> drawHexahedron(Cell*);
    vtkSmartPointer<vtkUnstructuredGrid> drawTetrahedron(Cell*);
    vtkSmartPointer<vtkUnstructuredGrid> drawPyramid(Cell*);

    void displayHexahedron();
    void displayTetrahedron();
    void displayPyramid();

    void resetViewer();
    void resetCamera();
    void changeBackgroundColor();
    void changeObjectColor();

signals:
    void statusUpdateMessage( const QString & message, int timeout );
};
#endif // MAINWINDOW_H
//mainwindow.h----------------------------------------------------------------
