#include "apphelp.h"
#include "ui_apphelp.h"

//constructor
AppHelp::AppHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppHelp)
{
    ui->setupUi(this);

    connect( ui->websiteButton, &QPushButton::released, this, &AppHelp::openWebsite );
}

//function to run the window
bool AppHelp::runHelp()
{
// get Qt to run the dialog
    if( this->exec() == QDialog::Accepted )
    {
        return true;
    }
    return false;
}

//function to open documentation website
void AppHelp::openWebsite(){

    QString link = "https://tefka.github.io/2020_GROUP_19/";
    QDesktopServices::openUrl(QUrl(link));
}
//destructor
AppHelp::~AppHelp()
{
    delete ui;
}
