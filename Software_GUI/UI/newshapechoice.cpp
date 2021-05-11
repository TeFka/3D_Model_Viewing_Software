#include "newshapechoice.h"
#include "ui_newshapechoice.h"

void NewShapeChoice::pickHexahedron(){

    this->shapeChoice = 1;
    this->accept();
}

void NewShapeChoice::pickTetrahedron(){

    this->shapeChoice = 2;
    this->accept();
}
void NewShapeChoice::pickPyramid(){

    this->shapeChoice = 3;
    this->accept();
}
void NewShapeChoice::pickSphere(){

    this->shapeChoice = 4;
    this->accept();
}
void NewShapeChoice::pickDisk(){

    this->shapeChoice = 5;
    this->accept();
}
void NewShapeChoice::pickCone(){

    this->shapeChoice = 6;
    this->accept();
}
void NewShapeChoice::pickPlane(){

    this->shapeChoice = 7;
    this->accept();
}
void NewShapeChoice::pickPoints(){

    this->shapeChoice = 8;
    this->accept();
}
void NewShapeChoice::pickLine(){

    this->shapeChoice = 9;
    this->accept();
}

void NewShapeChoice::pickCylinder(){

    this->shapeChoice = 10;
    this->accept();
}

void NewShapeChoice::pickEarth(){

    this->shapeChoice = 11;
    this->accept();
}

NewShapeChoice::NewShapeChoice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewShapeChoice)
{
    ui->setupUi(this);

    connect( ui->makeHex, &QPushButton::released, this, &NewShapeChoice::pickHexahedron );
    connect( ui->makeTetra, &QPushButton::released, this, &NewShapeChoice::pickTetrahedron );
    connect( ui->makePyr, &QPushButton::released, this, &NewShapeChoice::pickPyramid );
    connect( ui->makeSphere, &QPushButton::released, this, &NewShapeChoice::pickSphere );
    connect( ui->makeDisk, &QPushButton::released, this, &NewShapeChoice::pickDisk );
    connect( ui->makeCone, &QPushButton::released, this, &NewShapeChoice::pickCone );
    connect( ui->makePlane, &QPushButton::released, this, &NewShapeChoice::pickPlane );
    connect( ui->makePoints, &QPushButton::released, this, &NewShapeChoice::pickPoints );
    connect( ui->makeLine, &QPushButton::released, this, &NewShapeChoice::pickLine );
    connect( ui->makeCyl, &QPushButton::released, this, &NewShapeChoice::pickCylinder );
    connect( ui->makeEarth, &QPushButton::released, this, &NewShapeChoice::pickEarth );
}

bool NewShapeChoice::runChoice(int& chosenShape)
{
// get Qt to run the dialog
    if( this->exec() == QDialog::Accepted )
    {
        chosenShape = this->shapeChoice;
        return true;
    }
    return false;
}

NewShapeChoice::~NewShapeChoice()
{
    delete ui;
}
