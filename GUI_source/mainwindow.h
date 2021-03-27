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
#include <vtkCellData.h>
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

#include <vtkTextActor.h>
#include <vtkTextProperty.h>

#include <vtkMassProperties.h>

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

    int activeFilters[6] = {0,0,0,0,0,0};

    //vtkSmartPointer<vtkActor> activeActor = vtkSmartPointer<vtkActor>::New();
    //vtkSmartPointer<vtkDataSetMapper> activeMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    //vtkSmartPointer<vtkUnstructuredGrid> activeGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    //vtkSmartPointer<vtkPoints> gridPoints = vtkSmartPointer<vtkPoints>::New();

    vtkSmartPointer<vtkUnsignedCharArray> cellData = vtkSmartPointer<vtkUnsignedCharArray>::New();

    //text editing
    //vtkSmartPointer<vtkTextActor> volumeTextActor = vtkSmartPointer<vtkTextActor>::New();
    //vtkSmartPointer<vtkTextActor> cellNumTextActor = vtkSmartPointer<vtkTextActor>::New();
    //vtkSmartPointer<vtkTextActor> weightTextActor = vtkSmartPointer<vtkTextActor>::New();
    //vtkSmartPointer<vtkTextActor> positionTextActor = vtkSmartPointer<vtkTextActor>::New();

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

    //vtkSmartPointer<vtkMassProperties> objectParameters = vtkSmartPointer<vtkMassProperties>::New();

    int objectType = 0;

    double objectVolume = 0.0;
    double weight = 0.0;

    void refreshRender();
    void refreshGrid();
    void updateObject();

    void updateText();

    void initFilter(int);

    vtkAlgorithmOutput* filterStage(vtkAlgorithmOutput*, int);
    vtkSmartPointer<vtkDataSetMapper> mapperGridStage(vtkSmartPointer<vtkUnstructuredGrid>);
    vtkSmartPointer<vtkDataSetMapper> mapperStage(vtkAlgorithmOutput*);

    void drawHexahedron(Cell*,vtkSmartPointer<vtkUnstructuredGrid>);
    void drawTetrahedron(Cell*,vtkSmartPointer<vtkUnstructuredGrid>);
    void drawPyramid(Cell*,vtkSmartPointer<vtkUnstructuredGrid>);

public slots:

    void handleGeometryFilter();
    void handleShrinkFilter();
    void handleClipFilter();
    void handleContourFilter();
    void handleOutlineFilter();
    void handleOutlineCornerFilter();
    void handleSplineFilter();

    void changeShrinkFilterValue(int);

    //void changeClipFilterAxis();
    //void changeClipFilterCutOff();

    void setMinCellShow(int);
    void setMaxCellShow(int);

    void handleOpenButton();

    void changeLight(int);

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
