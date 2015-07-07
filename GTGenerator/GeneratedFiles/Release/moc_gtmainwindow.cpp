/****************************************************************************
** Meta object code from reading C++ file 'gtmainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gtmainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gtmainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GTMainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      24,   13,   13,   13, 0x08,
      36,   13,   31,   13, 0x08,
      43,   13,   31,   13, 0x08,
      52,   13,   13,   13, 0x08,
      60,   13,   13,   13, 0x08,
      89,   82,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GTMainWindow[] = {
    "GTMainWindow\0\0newFile()\0open()\0bool\0"
    "save()\0saveAs()\0about()\0documentWasModified()\0"
    "result\0newProjectWizardFinished(int)\0"
};

void GTMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GTMainWindow *_t = static_cast<GTMainWindow *>(_o);
        switch (_id) {
        case 0: _t->newFile(); break;
        case 1: _t->open(); break;
        case 2: { bool _r = _t->save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->saveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: _t->about(); break;
        case 5: _t->documentWasModified(); break;
        case 6: _t->newProjectWizardFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GTMainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GTMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GTMainWindow,
      qt_meta_data_GTMainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GTMainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GTMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GTMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GTMainWindow))
        return static_cast<void*>(const_cast< GTMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GTMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
