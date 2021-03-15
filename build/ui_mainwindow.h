/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QVTKOpenGLWidget.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionHelp;
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QVTKOpenGLWidget *qvtkWidget;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *makeHex;
    QPushButton *makeTetra;
    QPushButton *makePyr;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *resetObject;
    QPushButton *resetCamera;
    QPushButton *backgroundColor;
    QPushButton *objectColor;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QLabel *lightLabel;
    QSlider *lightSlider;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *shrinkCheck;
    QCheckBox *clipCheck;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1027, 600);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/newIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/openIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/saveIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/helpIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelp->setIcon(icon3);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(50, 10, 871, 491));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        qvtkWidget = new QVTKOpenGLWidget(verticalLayoutWidget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(qvtkWidget->sizePolicy().hasHeightForWidth());
        qvtkWidget->setSizePolicy(sizePolicy1);
        qvtkWidget->setMinimumSize(QSize(0, 171));

        verticalLayout->addWidget(qvtkWidget);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        makeHex = new QPushButton(verticalLayoutWidget);
        makeHex->setObjectName(QString::fromUtf8("makeHex"));

        horizontalLayout_4->addWidget(makeHex);

        makeTetra = new QPushButton(verticalLayoutWidget);
        makeTetra->setObjectName(QString::fromUtf8("makeTetra"));

        horizontalLayout_4->addWidget(makeTetra);

        makePyr = new QPushButton(verticalLayoutWidget);
        makePyr->setObjectName(QString::fromUtf8("makePyr"));

        horizontalLayout_4->addWidget(makePyr);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        resetObject = new QPushButton(verticalLayoutWidget);
        resetObject->setObjectName(QString::fromUtf8("resetObject"));

        horizontalLayout_3->addWidget(resetObject);

        resetCamera = new QPushButton(verticalLayoutWidget);
        resetCamera->setObjectName(QString::fromUtf8("resetCamera"));

        horizontalLayout_3->addWidget(resetCamera);

        backgroundColor = new QPushButton(verticalLayoutWidget);
        backgroundColor->setObjectName(QString::fromUtf8("backgroundColor"));

        horizontalLayout_3->addWidget(backgroundColor);

        objectColor = new QPushButton(verticalLayoutWidget);
        objectColor->setObjectName(QString::fromUtf8("objectColor"));

        horizontalLayout_3->addWidget(objectColor);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        lightLabel = new QLabel(verticalLayoutWidget);
        lightLabel->setObjectName(QString::fromUtf8("lightLabel"));

        horizontalLayout->addWidget(lightLabel);

        lightSlider = new QSlider(verticalLayoutWidget);
        lightSlider->setObjectName(QString::fromUtf8("lightSlider"));
        lightSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(lightSlider);

        horizontalSpacer = new QSpacerItem(268, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        shrinkCheck = new QCheckBox(verticalLayoutWidget);
        shrinkCheck->setObjectName(QString::fromUtf8("shrinkCheck"));

        horizontalLayout_2->addWidget(shrinkCheck);

        clipCheck = new QCheckBox(verticalLayoutWidget);
        clipCheck->setObjectName(QString::fromUtf8("clipCheck"));

        horizontalLayout_2->addWidget(clipCheck);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1027, 26));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionHelp);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionSave);
        toolBar->addAction(actionHelp);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionHelp->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
        makeHex->setText(QCoreApplication::translate("MainWindow", "Hexahedron", nullptr));
        makeTetra->setText(QCoreApplication::translate("MainWindow", "Tetrahedron", nullptr));
        makePyr->setText(QCoreApplication::translate("MainWindow", "Pyramid", nullptr));
        resetObject->setText(QCoreApplication::translate("MainWindow", "Reset Object", nullptr));
        resetCamera->setText(QCoreApplication::translate("MainWindow", "Reset Camera", nullptr));
        backgroundColor->setText(QCoreApplication::translate("MainWindow", "Background Color", nullptr));
        objectColor->setText(QCoreApplication::translate("MainWindow", "Object Color", nullptr));
        lightLabel->setText(QCoreApplication::translate("MainWindow", "Light intensity   ", nullptr));
        shrinkCheck->setText(QCoreApplication::translate("MainWindow", "Shrink filter", nullptr));
        clipCheck->setText(QCoreApplication::translate("MainWindow", "Clip filter", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
