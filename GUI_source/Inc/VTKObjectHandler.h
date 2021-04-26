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

class VTKObjectHandler{

private:
    vtkSmartPointer<vtkPoints> activePoints = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();

    QColor activeColor;
    std::vector<std::array<double,4>> separateCellColors;

    Vector3D objectDimensions;
    Vector3D objectPosition;
    double objectVolume = 0.0;
    double objectWeight = 0.0;

    void updateVTKModel();

public:
    void makeMeasurement();

    void updateObject();

    void drawHexahedron(Cell*,vtkSmartPointer<vtkUnstructuredGrid>);
    void drawTetrahedron(Cell*,vtkSmartPointer<vtkUnstructuredGrid>);
    void drawPyramid(Cell*,vtkSmartPointer<vtkUnstructuredGrid>);
}

#endif // VTKOBJECT_H_INCLUDED
