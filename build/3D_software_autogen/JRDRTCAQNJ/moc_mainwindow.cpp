/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "GUI_source/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[315];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 19), // "statusUpdateMessage"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 7), // "message"
QT_MOC_LITERAL(4, 40, 7), // "timeout"
QT_MOC_LITERAL(5, 48, 18), // "handleShrinkFilter"
QT_MOC_LITERAL(6, 67, 16), // "handleClipFilter"
QT_MOC_LITERAL(7, 84, 16), // "handleOpenButton"
QT_MOC_LITERAL(8, 101, 11), // "changeLight"
QT_MOC_LITERAL(9, 113, 14), // "drawHexahedron"
QT_MOC_LITERAL(10, 128, 36), // "vtkSmartPointer<vtkUnstructur..."
QT_MOC_LITERAL(11, 165, 5), // "Cell*"
QT_MOC_LITERAL(12, 171, 15), // "drawTetrahedron"
QT_MOC_LITERAL(13, 187, 11), // "drawPyramid"
QT_MOC_LITERAL(14, 199, 17), // "displayHexahedron"
QT_MOC_LITERAL(15, 217, 18), // "displayTetrahedron"
QT_MOC_LITERAL(16, 236, 14), // "displayPyramid"
QT_MOC_LITERAL(17, 251, 11), // "resetViewer"
QT_MOC_LITERAL(18, 263, 11), // "resetCamera"
QT_MOC_LITERAL(19, 275, 21), // "changeBackgroundColor"
QT_MOC_LITERAL(20, 297, 17) // "changeObjectColor"

    },
    "MainWindow\0statusUpdateMessage\0\0message\0"
    "timeout\0handleShrinkFilter\0handleClipFilter\0"
    "handleOpenButton\0changeLight\0"
    "drawHexahedron\0vtkSmartPointer<vtkUnstructuredGrid>\0"
    "Cell*\0drawTetrahedron\0drawPyramid\0"
    "displayHexahedron\0displayTetrahedron\0"
    "displayPyramid\0resetViewer\0resetCamera\0"
    "changeBackgroundColor\0changeObjectColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   94,    2, 0x0a /* Public */,
       6,    0,   95,    2, 0x0a /* Public */,
       7,    0,   96,    2, 0x0a /* Public */,
       8,    1,   97,    2, 0x0a /* Public */,
       9,    1,  100,    2, 0x0a /* Public */,
      12,    1,  103,    2, 0x0a /* Public */,
      13,    1,  106,    2, 0x0a /* Public */,
      14,    0,  109,    2, 0x0a /* Public */,
      15,    0,  110,    2, 0x0a /* Public */,
      16,    0,  111,    2, 0x0a /* Public */,
      17,    0,  112,    2, 0x0a /* Public */,
      18,    0,  113,    2, 0x0a /* Public */,
      19,    0,  114,    2, 0x0a /* Public */,
      20,    0,  115,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    0x80000000 | 10, 0x80000000 | 11,    2,
    0x80000000 | 10, 0x80000000 | 11,    2,
    0x80000000 | 10, 0x80000000 | 11,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->statusUpdateMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->handleShrinkFilter(); break;
        case 2: _t->handleClipFilter(); break;
        case 3: _t->handleOpenButton(); break;
        case 4: _t->changeLight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: { vtkSmartPointer<vtkUnstructuredGrid> _r = _t->drawHexahedron((*reinterpret_cast< Cell*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< vtkSmartPointer<vtkUnstructuredGrid>*>(_a[0]) = std::move(_r); }  break;
        case 6: { vtkSmartPointer<vtkUnstructuredGrid> _r = _t->drawTetrahedron((*reinterpret_cast< Cell*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< vtkSmartPointer<vtkUnstructuredGrid>*>(_a[0]) = std::move(_r); }  break;
        case 7: { vtkSmartPointer<vtkUnstructuredGrid> _r = _t->drawPyramid((*reinterpret_cast< Cell*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< vtkSmartPointer<vtkUnstructuredGrid>*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->displayHexahedron(); break;
        case 9: _t->displayTetrahedron(); break;
        case 10: _t->displayPyramid(); break;
        case 11: _t->resetViewer(); break;
        case 12: _t->resetCamera(); break;
        case 13: _t->changeBackgroundColor(); break;
        case 14: _t->changeObjectColor(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(const QString & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::statusUpdateMessage)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::statusUpdateMessage(const QString & _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
