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

    vtkSmartPointer<vtkClipDataSet> clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
    vtkSmartPointer<vtkShrinkFilter> shrinkFilter = vtkSmartPointer<vtkShrinkFilter>::New();
    bool clipFilterON = false;
    bool shrinkFilterON = false;

    int objectType = 0;

    MouseInteractor mouseInteractor();

    void refreshRender();
    void refreshGrid();

    void initClipFilter();
    void initShrinkFilter();

    void filterStage();

public slots:

    void handleShrinkFilter();
    void handleClipFilter();

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
