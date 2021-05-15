#include "newshapechoice.h"
#include "ui_newshapechoice.h"

//Function to pick hexahedron as new object
void NewShapeChoice::pickHexahedron(){

    this->shapeChoice = 1;

    //accept the dialog
    this->accept();
}

//Function to pick tetrahedron as new object
void NewShapeChoice::pickTetrahedron(){

    this->shapeChoice = 2;

    //accept the dialog
    this->accept();
}

//Function to pick pyramid as new object
void NewShapeChoice::pickPyramid(){

    this->shapeChoice = 3;

    //accept the dialog
    this->accept();
}

//Function to pick sphere as new object
void NewShapeChoice::pickSphere(){

    this->shapeChoice = 4;

    //accept the dialog
    this->accept();
}

//Function to pick disk as new object
void NewShapeChoice::pickDisk(){

    this->shapeChoice = 5;

    //accept the dialog
    this->accept();
}

//Function to pick cone as new object
void NewShapeChoice::pickCone(){

    this->shapeChoice = 6;

    //accept the dialog
    this->accept();
}

//Function to pick plane as new object
void NewShapeChoice::pickPlane(){

    this->shapeChoice = 7;

    //accept the dialog
    this->accept();
}

//Function to pick point cluster as new object
void NewShapeChoice::pickPoints(){

    this->shapeChoice = 8;

    //accept the dialog
    this->accept();
}

//Function to pick line as new object
void NewShapeChoice::pickLine(){

    this->shapeChoice = 9;

    //accept the dialog
    this->accept();
}

//Function to pick cylinder as new object
void NewShapeChoice::pickCylinder(){

    this->shapeChoice = 10;

    //accept the dialog
    this->accept();
}

//Function to pick earth as new object
void NewShapeChoice::pickEarth(){

    this->shapeChoice = 11;

    //accept the dialog
    this->accept();
}

NewShapeChoice::NewShapeChoice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewShapeChoice)
{
    ui->setupUi(this);

    //Create connection to object selection buttons
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

//Function to end dialog and specify which object was picked
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

//destructor
NewShapeChoice::~NewShapeChoice()
{
    delete ui;
}
