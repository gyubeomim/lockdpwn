/****************************************************************************
** Meta object code from reading C++ file 'controlform_boolean.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../controlform_boolean.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controlform_boolean.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ControlFormBoolean[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   46,   54,   54, 0x08,
      55,   46,   54,   54, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ControlFormBoolean[] = {
    "ControlFormBoolean\0on_rbDisable_toggled(bool)\0"
    "checked\0\0on_rbEnable_toggled(bool)\0"
};

void ControlFormBoolean::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ControlFormBoolean *_t = static_cast<ControlFormBoolean *>(_o);
        switch (_id) {
        case 0: _t->on_rbDisable_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_rbEnable_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ControlFormBoolean::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ControlFormBoolean::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ControlFormBoolean,
      qt_meta_data_ControlFormBoolean, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ControlFormBoolean::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ControlFormBoolean::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ControlFormBoolean::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ControlFormBoolean))
        return static_cast<void*>(const_cast< ControlFormBoolean*>(this));
    return QWidget::qt_metacast(_clname);
}

int ControlFormBoolean::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
