/*! \file apphelp.h File Reference
    \author   Copyright: \n Code part: Danielius Zurlys (StudentID: 20130611)
                         \n Comments part: Chen xu  (StudentID: 20187733)
    \brief build the functions to gain and change the variables of specified objects.
*/

#ifndef APPHELP_H
#define APPHELP_H

#include <QDialog>
#include <QDesktopServices>
#include <QString>
#include <QUrl>

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

     /*! Function runChoice(int&) \n
        Function to run and create the new window that will show information
        \n Arguments: none
        \return  none
    */
    bool runHelp();

    /*! Function runChoice(int&) \n
        Function to open documentation website
        \n Arguments: none
        \return  none
    */
    void openWebsite();

private:
    Ui::AppHelp *ui;
};

#endif // APPHELP_H
