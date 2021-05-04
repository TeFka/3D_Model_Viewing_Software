#ifndef VTKOBJECT_H_INCLUDED
#define VTKOBJECT_H_INCLUDED

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

#include <vtkAlgorithmOutput.h>

#include <vtkGlyph3DMapper.h>

#include <vtkIdList.h>

#include "../Inc/Model.h"

struct materialCellConnection{
    int minCellAssigned = 0;
    int maxCellAssigned = 0;
    Material theMaterial;
};

class VTKObjectHandler{

private:

    Model activeVTKModel;

    vtkSmartPointer<vtkSTLReader> activeReader = vtkSmartPointer<vtkSTLReader>::New();

    vtkSmartPointer<vtkUnstructuredGrid> activeGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkGeometryFilter> geometryFilter = vtkSmartPointer<vtkGeometryFilter>::New();

    vtkSmartPointer<vtkPoints> activePoints = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> activeCells = vtkSmartPointer<vtkCellArray>::New();
    vtkSmartPointer<vtkUnsignedCharArray> cellColorData = vtkSmartPointer<vtkUnsignedCharArray>::New();

    std::vector<materialCellConnection> materials;

    std::vector<std::array<double,3>> separateCellColors;
    QColor activeColor;

    vtkSmartPointer<vtkMassProperties> objectParameters = vtkSmartPointer<vtkMassProperties>::New();
    Vector3D objectDimensions;
    Vector3D objectPosition;

    int objectType = 0;

    double objectVolume = 0.0;
    double objectWeight = 0.0;

    double dimensionAverage = 0.0;

    int minActiveCell = 0;
    int maxActiveCell = 0;
    int cellAmount = 0;

    void refresh();

    vtkAlgorithmOutput* finalSourceAlgorithm = vtkAlgorithmOutput::New();

public:

    VTKObjectHandler();

    vtkAlgorithmOutput* getSource();
    vtkSmartPointer<vtkUnstructuredGrid> getGrid();
    vtkSmartPointer<vtkPoints> getPoints();
    vtkSmartPointer<vtkCellArray> getCells();

    QColor getColor();
    std::array<double,3> getCellColor(int);

    int getObjectType();
    double getVolume();
    double getWeight();

    Vector3D getPosition();
    Vector3D getDimensions();
    double getDimensionAverage();

    int getCellAmount();
    int getMinActiveCell();
    int getMaxActiveCell();

    void setColor(QColor);
    void setCellColor(int,double,double,double);
    void setMinActiveCell(int);
    void setMaxActiveCell(int);

    void updateVTKModel();
    void makeMeasurements();

    void drawHexahedron(Cell*);
    void drawTetrahedron(Cell*);
    void drawPyramid(Cell*);

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

    void getModelFromFile(QString);
    void saveModelToFile(QString);

    void changeColor(QColor);
    void resetColor();

};

#endif // VTKOBJECT_H_INCLUDED
