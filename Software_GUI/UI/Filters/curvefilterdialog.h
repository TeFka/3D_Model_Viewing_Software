#ifndef CURVEFILTERDIALOG_H
#define CURVEFILTERDIALOG_H

#include <QDialog>

namespace Ui {
class curveFilterDialog;
}

class curveFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit curveFilterDialog(QWidget *parent = nullptr);
    ~curveFilterDialog();

private:
    Ui::curveFilterDialog *ui;
};

#endif // CURVEFILTERDIALOG_H
