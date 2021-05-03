#ifndef APPHELP_H
#define APPHELP_H

#include <QDialog>

namespace Ui
{
class AppHelp;
}

class AppHelp : public QDialog
{
    Q_OBJECT

public:
    explicit AppHelp(QWidget *parent = nullptr);
    ~AppHelp();

    bool runHelp();

private:
    Ui::AppHelp *ui;
};

#endif // APPHELP_H
