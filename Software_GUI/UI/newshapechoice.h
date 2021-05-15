/*! \file newShapeChoice.h File Reference
    \author   Copyright: \n Code part: Danielius Zurlys (StudentID: 20130611)
                         \n Comments part: Danielius Zurlys  (StudentID: 20130611)
    \brief Create a window that will allow to choose new object
*/

#ifndef NEWSHAPECHOICE_H
#define NEWSHAPECHOICE_H

#include <QDialog>

namespace Ui {
class NewShapeChoice;
}

class NewShapeChoice : public QDialog
{
    Q_OBJECT

public:
    explicit NewShapeChoice(QWidget *parent = nullptr);
    ~NewShapeChoice();

    /*! Function runChoice(int&) \n
        Function to run the dialog and specify which object was picked
        \n Arguments:int& - reference of value that will be updated
        \return  none (value is updated through reference)
    */
    bool runChoice(int&);

public slots:

    /*! Function pickHexahedron() \n
        Function to pick hexahedron as new object
        \n Arguments:none
        \return none (Updates inner dialog value that specifies chosen object)
    */
    void pickHexahedron();

    /*! Function pickTetrahedron() \n
        Function to pick tetrahedron as new object
        \n Arguments:none
        \return none (Updates inner dialog value that specifies chosen object)
    */
    void pickTetrahedron();

    /*! Function pickPyramid() \n
        Function to pick pyramid as new object
        \n Arguments:none
        \return none (Updates inner dialog value that specifies chosen object)
    */
    void pickPyramid();

    /*! Function pickSphere() \n
        Function to pick sphere as new object
        \n Arguments:none
        \return none (Updates inner dialog value that specifies chosen object)
    */
    void pickSphere();

    /*! Function pickDisk() \n
        Function to pick disk as new object
        \n Arguments:none
        \return none (Updates inner dialog value that specifies chosen object)
    */
    void pickDisk();

    /*! Function pickCone() \n
        Function to pick cone as new object
        \n Arguments:none
        \return none (Updates inner dialog value that specifies chosen object)
    */
    void pickCone();

    /*! Function pickPlane() \n
        Function to pick plane as new object
        \n Arguments:none
        \return none (Updates inner dialog value that specifies chosen object)
    */
    void pickPlane();

    /*! Function pickPoints() \n
        Function to pick point cluster as new object
        \n Arguments:none
        \return none (Updates inner dialog value that specifies chosen object)
    */
    void pickPoints();

    /*! Function pickLine() \n
        Function to pick line as new object
        \n Arguments:none
        \return none (Updates inner dialog value that specifies chosen object)
    */
    void pickLine();

    /*! Function pickCylinder() \n
        Function to pick cylinder as new object
        \n Arguments:none
        \return none (Updates inner dialog value that specifies chosen object)
    */
	void pickCylinder();

	/*! Function pickEarth() \n
        Function to pick earth as new object
        \n Arguments:none
        \return none (Updates inner dialog value that specifies chosen object)
    */
	void pickEarth();
private:
    Ui::NewShapeChoice *ui;

    int shapeChoice = 0;
};

#endif // NEWSHAPECHOICE_H
