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

    bool runChoice(int&);

public slots:

    void pickHexahedron();
    void pickTetrahedron();
    void pickPyramid();
    void pickSphere();
    void pickDisk();
    void pickCone();
    void pickPlane();
    void pickPoints();
    void pickLine();
	void pickCylinder();
	void pickEarth();
private:
    Ui::NewShapeChoice *ui;

    int shapeChoice = 0;
};

#endif // NEWSHAPECHOICE_H
