/****************************************************************************
** Meta object code from reading C++ file 'EvaluationParameter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../iqc5/UI/EvaluationParameter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EvaluationParameter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EvaluationParameter_t {
    QByteArrayData data[7];
    char stringdata[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EvaluationParameter_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EvaluationParameter_t qt_meta_stringdata_EvaluationParameter = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 11),
QT_MOC_LITERAL(2, 32, 0),
QT_MOC_LITERAL(3, 33, 23),
QT_MOC_LITERAL(4, 57, 4),
QT_MOC_LITERAL(5, 62, 24),
QT_MOC_LITERAL(6, 87, 22)
    },
    "EvaluationParameter\0textChanged\0\0"
    "on_inputTea_textChanged\0arg1\0"
    "on_inputBias_textChanged\0"
    "on_inputCV_textChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EvaluationParameter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   35,    2, 0x08 /* Private */,
       5,    1,   38,    2, 0x08 /* Private */,
       6,    1,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,

       0        // eod
};

void EvaluationParameter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EvaluationParameter *_t = static_cast<EvaluationParameter *>(_o);
        switch (_id) {
        case 0: _t->textChanged(); break;
        case 1: _t->on_inputTea_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_inputBias_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_inputCV_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EvaluationParameter::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EvaluationParameter::textChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject EvaluationParameter::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EvaluationParameter.data,
      qt_meta_data_EvaluationParameter,  qt_static_metacall, 0, 0}
};


const QMetaObject *EvaluationParameter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EvaluationParameter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EvaluationParameter.stringdata))
        return static_cast<void*>(const_cast< EvaluationParameter*>(this));
    return QWidget::qt_metacast(_clname);
}

int EvaluationParameter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void EvaluationParameter::textChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
