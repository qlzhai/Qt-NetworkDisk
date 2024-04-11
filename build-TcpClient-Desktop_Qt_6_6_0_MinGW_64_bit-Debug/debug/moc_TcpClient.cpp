/****************************************************************************
** Meta object code from reading C++ file 'TcpClient.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TcpClient/TcpClient.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TcpClient.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSTcpClientENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSTcpClientENDCLASS = QtMocHelpers::stringData(
    "TcpClient",
    "showConnect",
    "",
    "recvMsg",
    "getLoginName",
    "curPath",
    "updateCurPath",
    "str_curPath",
    "on_login_pb_clicked",
    "on_registe_pb_clicked",
    "on_cancel_pb_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSTcpClientENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[10];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[13];
    char stringdata5[8];
    char stringdata6[14];
    char stringdata7[12];
    char stringdata8[20];
    char stringdata9[22];
    char stringdata10[21];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSTcpClientENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSTcpClientENDCLASS_t qt_meta_stringdata_CLASSTcpClientENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "TcpClient"
        QT_MOC_LITERAL(10, 11),  // "showConnect"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 7),  // "recvMsg"
        QT_MOC_LITERAL(31, 12),  // "getLoginName"
        QT_MOC_LITERAL(44, 7),  // "curPath"
        QT_MOC_LITERAL(52, 13),  // "updateCurPath"
        QT_MOC_LITERAL(66, 11),  // "str_curPath"
        QT_MOC_LITERAL(78, 19),  // "on_login_pb_clicked"
        QT_MOC_LITERAL(98, 21),  // "on_registe_pb_clicked"
        QT_MOC_LITERAL(120, 20)   // "on_cancel_pb_clicked"
    },
    "TcpClient",
    "showConnect",
    "",
    "recvMsg",
    "getLoginName",
    "curPath",
    "updateCurPath",
    "str_curPath",
    "on_login_pb_clicked",
    "on_registe_pb_clicked",
    "on_cancel_pb_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSTcpClientENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x0a,    1 /* Public */,
       3,    0,   63,    2, 0x0a,    2 /* Public */,
       4,    0,   64,    2, 0x0a,    3 /* Public */,
       5,    0,   65,    2, 0x0a,    4 /* Public */,
       6,    1,   66,    2, 0x0a,    5 /* Public */,
       8,    0,   69,    2, 0x08,    7 /* Private */,
       9,    0,   70,    2, 0x08,    8 /* Private */,
      10,    0,   71,    2, 0x08,    9 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject TcpClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSTcpClientENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSTcpClientENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSTcpClientENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<TcpClient, std::true_type>,
        // method 'showConnect'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'recvMsg'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'getLoginName'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'curPath'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'updateCurPath'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_login_pb_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_registe_pb_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_cancel_pb_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void TcpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TcpClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showConnect(); break;
        case 1: _t->recvMsg(); break;
        case 2: { QString _r = _t->getLoginName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 3: { QString _r = _t->curPath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->updateCurPath((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->on_login_pb_clicked(); break;
        case 6: _t->on_registe_pb_clicked(); break;
        case 7: _t->on_cancel_pb_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *TcpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSTcpClientENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TcpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
