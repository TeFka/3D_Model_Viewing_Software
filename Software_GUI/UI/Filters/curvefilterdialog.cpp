#include "curvefilterdialog.h"
#include "ui_curvefilterdialog.h"

curveFilterDialog::curveFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::curveFilterDialog)
{
    ui->setupUi(this);
}

curveFilterDialog::~curveFilterDialog()
{
    delete ui;
}
