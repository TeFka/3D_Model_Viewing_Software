/*! \file VTKObjectHandler.h File Reference
    \author   Copyright: \n Code part: Danielius Zurlys (StudentID: 20130611)
                         \n Comments part: Chen xu  (StudentID: 20187733)
    \brief build the functions to gain and change the variables of specified objects.
*/
#ifndef VTKOBJECT_H_INCLUDED
#define VTKOBJECT_H_INCLUDED

#include <iostream>
#include <string>
#include <array>
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
#include <vtkEarthSource.h>

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

#include "../Model_Library/Inc/Model.h"

/*! \class VTKObjectHandler
    \brief the major functions to achieve gaining and changing the variables of objects
*/
class VTKObjectHandler{

private:

    Model activeVTKModel;

    vtkSmartPointer<vtkSTLReader> activeReader = vtkSmartPointer<vtkSTLReader>::New();

    vtkSmartPointer<vtkUnstructuredGrid> activeGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkGeometryFilter> geometryFilter = vtkSmartPointer<vtkGeometryFilter>::New();

    vtkSmartPointer<vtkPoints> activePoints = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> activeCells = vtkSmartPointer<vtkCellArray>::New();
    vtkSmartPointer<vtkUnsignedCharArray> cellColorData = vtkSmartPointer<vtkUnsignedCharArray>::New();

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
    int shownPoints = 0;

    void refresh();

    vtkAlgorithmOutput* finalSourceAlgorithm = vtkAlgorithmOutput::New();
    vtkPolyData* finalPolyData = vtkPolyData::New();

public:

    VTKObjectHandler();  //! Destructor

    /*! Function getSource() \n
        Function to make connection between the source and output.
        \n Arguments:none
        \return  vtkAlgorithmOutput - Source
    */
    vtkAlgorithmOutput* getSource();

    /*! Function GetPolydata() \n
        Function to Retrieve an instance of this class from an information object.
        \n Arguments:none
        \return  vtkPolyData - Polydata
    */
    vtkPolyData* GetPolydata();

   /*! Function getGrid() \n
        Function to get Grid from the specified object.
        \n Arguments: none
        \return  vtkSmartPointer<vtkUnstructuredGrid> - Grid
    */
    vtkSmartPointer<vtkUnstructuredGrid> getGrid();

    /*! Function getPoints() \n
        Function to get pointers from the polydata.
        \n Arguments:none
        \return vtkSmartPointer<vtkPoints> - Points
    */
    vtkSmartPointer<vtkPoints> getPoints();

    /*! Function getCells() \n
        Function to get cells from the specified object.
        \n Arguments:none
        \return vtkSmartPointer<vtkCellArray> - Cells
    */
    vtkSmartPointer<vtkCellArray> getCells();

    /*! Function getShownPointAmount() \n
        Function to get amount of point from the specified object and show it.
        \n Arguments:none
        \return   int - the amount of point
    */
    int getShownPointAmount();

    /*! Function getColor() \n
        Function to get color from the specified object.
        \n Arguments:none
        \return  QColor - color of the object
    */
    QColor getColor();

    /*! Function getCellColor() \n
        Function to get color of cell from the specified object.
        \n Arguments: int - index of cell
        \return  std::array<double,3> - cell color
    */
    std::array<double,3> getCellColor(int);

    /*! Function getObjectType() \n
        Function to get type of the specified object.
        \n Arguments:none
        \return  int - object type
    */
    int getObjectType();

    /*! Function getVolume() \n
        Function to get volume of the specified object.
        \n Arguments:none
        \return   double - object Volume
    */
    double getVolume();

    /*! Function getWeight() \n
        Function to get weight of the specified object.
        \n Arguments:none
        \return   double - object Weight
    */
    double getWeight();

    /*! Function getPosition() \n
        Function to get a vector as the position from the specified object.
        \n Arguments:none
        \return   Vector3D - object Position
    */
    Vector3D getPosition();

    /*! Function getDimensions() \n
        Function to get a vector as the Dimensions from the specified object.
        \n Arguments:none
        \return   Vector3D - object Dimensions
    */
    Vector3D getDimensions();

     /*! Function getDimensionAverage() \n
         Function to get average Dimensions of the specified object.
         \n Arguments:none
         \return   double - average dimension of object
    */
    double getDimensionAverage();

    /*!  Function getCellAmount() \n
         Function to get amount of cell of the specified object.
         \n Arguments:none
         \return   double - the amount of cell
    */
    int getCellAmount();

    /*! Function getMinActiveCell() \n
        Function to get min cell of the specified object.
        \n Arguments:none
        \return   int - the min cell
    */
    int getMinActiveCell();

    /*! Function getMaxActiveCell() \n
        Function to get max cell of the specified object and show it.
        \n Arguments:none
        \return   int - the max cell
    */
    int getMaxActiveCell();

    /*! Function setColor(QColor) \n
        Function to get color of specified object with the QColor.
        \n Arguments: QColor -
        \return   void - color
    */
    void setColor(QColor);

     /*! Function setCellColor(int,double,double,double) \n
         Function to set cell color of specified object with specific variables.
         \n Arguments: int,double,double,double - the specific variables
         \return   void - cell color
    */
    void setCellColor(int,double,double,double);

     /*! Function setMinActiveCell(int) \n
         Function to set min cell of specified object with specific variables.
         \n Arguments: int,double,double,double - the specific variable
         \return   void - min cell
    */
    void setMinActiveCell(int);

    /*! Function setMaxActiveCell(int) \n
        Function to set max cell of the specified object.
        \n Arguments: int - the specific variable
        \return   void - max cell
    */
    void setMaxActiveCell(int);

    /*! Function handlePolydata() \n
        Function to handle the poly data of the specified object
        \n Arguments: none
        \return   void - Polydata
    */
    void handlePolydata();

    /*! Function updateVTKModel() \n
        Function to update vtk model.
        \n Arguments: none
        \return   void - vtk model
    */
    void updateVTKModel();

    /*! Function makeMeasurements() \n
        Function to make measurements.
        \n Arguments: none
        \return   void - measurement
    */
    void makeMeasurements();

    /*! Function drawHexahedron(Cell*) \n
        Function to draw the Hexahedron.
        \n Arguments: Cell*
        \return   void - draw hexahedron
    */
    void drawHexahedron(Cell*);

    /*! Function drawTetrahedron(Cell*) \n
        Function to draw the Tetrahedron.
        \n Arguments: Cell*
        \return   void - draw Tetrahedron
    */
    void drawTetrahedron(Cell*);

     /*! Function drawPyramid(Cell*) \n
        Function to draw the Pyramid.
        \n Arguments: Cell*
        \return   void - draw Pyramid
    */
    void drawPyramid(Cell*);

    /*! Function displayHexahedron() \n
        Function to display the Hexahedron.
        \n Arguments: none
        \return   void - display Hexahedron
    */
    void displayHexahedron();

    /*! Function displayTetrahedron() \n
        Function to display the Tetrahedron.
        \n Arguments: none
        \return   void - display Tetrahedron
    */
    void displayTetrahedron();

    /*! Function displayPyramid() \n
        Function to display the Pyramid.
        \n Arguments: none
        \return   void - display Pyramid
    */
    void displayPyramid();

    /*! Function displaySphere() \n
        Function to display the Sphere.
        \n Arguments: none
        \return   void - display Sphere
    */
    void displaySphere();

     /*! Function displayDisk() \n
        Function to display the Disk.
        \n Arguments: none
        \return   void - display Disk
    */
    void displayDisk();

     /*! Function displayCone() \n
        Function to display the Cone.
        \n Arguments: none
        \return   void - display Cone
    */
    void displayCone();

    /*! Function displayPlane() \n
        Function to display the Plane.
        \n Arguments: none
        \return   void - display Plane
    */
    void displayPlane();

    /*! Function displayPointCluster() \n
        Function to display the Point of Cluster.
        \n Arguments: int - point of cluster
        \return   void - display the Point of Cluster
    */
    void displayPointCluster(int);

    /*! Function displayLine() \n
        Function to display the line.
        \n Arguments: none
        \return   void - display the line
    */
    void displayLine();

    /*! Function displayCylinder() \n
        Function to display the Cylinder.
        \n Arguments: none
        \return   void - display the Cylinder
    */
    void displayCylinder();

    /*! Function displayEarth() \n
        Function to display the Earth.
        \n Arguments: none
        \return   void - display the Earth
    */
    void displayEarth();

    /*! Function getModelFromFile(QString) \n
        Function to get the model from the selected file.
        \n Arguments: QString - model
        \return   void - get the model from the selected file
    */
    void getModelFromFile(QString);

    /*! Function saveModelFromFile(QString) \n
        Function to save the model from the selected file.
        \n Arguments: QString - model
        \return   void - save the model from the selected file
    */
    void saveModelToFile(QString);

     /*! Function changeColor(QColor) \n
        Function to change the color of object.
        \n Arguments: QColor - color
        \return   void - change the color of object
    */
    void changeColor(QColor);

    /*! Function resetColor() \n
        Function to reset the color of object.
        \n Arguments: none
        \return   void - reset the color of object
    */
    void resetColor();


};

#endif //! VTKOBJECT_H_INCLUDED
