/****************************************************************************
** Meta object code from reading C++ file 'sharefile.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TcpClient/sharefile.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sharefile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSShareFileENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSShareFileENDCLASS = QtMocHelpers::stringData(
    "ShareFile",
    "selectAll",
    "",
    "cancelSelect",
    "okShare",
    "cancelShare"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSShareFileENDCLASS_t {
    uint offsetsAndSizes[12];
    char stringdata0[10];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[8];
    char stringdata5[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSShareFileENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSShareFileENDCLASS_t qt_meta_stringdata_CLASSShareFileENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "ShareFile"
        QT_MOC_LITERAL(10, 9),  // "selectAll"
        QT_MOC_LITERAL(20, 0),  // ""
        QT_MOC_LITERAL(21, 12),  // "cancelSelect"
        QT_MOC_LITERAL(34, 7),  // "okShare"
        QT_MOC_LITERAL(42, 11)   // "cancelShare"
    },
    "ShareFile",
    "selectAll",
    "",
    "cancelSelect",
    "okShare",
    "cancelShare"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSShareFileENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x0a,    1 /* Public */,
       3,    0,   39,    2, 0x0a,    2 /* Public */,
       4,    0,   40,    2, 0x0a,    3 /* Public */,
       5,    0,   41,    2, 0x0a,    4 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ShareFile::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSShareFileENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSShareFileENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSShareFileENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ShareFile, std::true_type>,
        // method 'selectAll'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cancelSelect'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'okShare'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cancelShare'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ShareFile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ShareFile *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->selectAll(); break;
        case 1: _t->cancelSelect(); break;
        case 2: _t->okShare(); break;
        case 3: _t->cancelShare(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *ShareFile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShareFile::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSShareFileENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ShareFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
