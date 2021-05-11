#include "apphelp.h"
#include "ui_apphelp.h"

AppHelp::AppHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppHelp)
{
    ui->setupUi(this);
}

bool AppHelp::runHelp()
{
// get Qt to run the dialog
    if( this->exec() == QDialog::Accepted )
    {
        return true;
    }
    return false;
}


AppHelp::~AppHelp()
{
    delete ui;
}
