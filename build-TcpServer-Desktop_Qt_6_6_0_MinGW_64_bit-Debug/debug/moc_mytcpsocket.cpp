/****************************************************************************
** Meta object code from reading C++ file 'mytcpsocket.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TcpServer/mytcpsocket.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mytcpsocket.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSMyTcpSocketENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMyTcpSocketENDCLASS = QtMocHelpers::stringData(
    "MyTcpSocket",
    "offline",
    "",
    "MyTcpSocket*",
    "mysocket",
    "recvMsg",
    "clientOffline",
    "sendFileToClient"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMyTcpSocketENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[12];
    char stringdata1[8];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[9];
    char stringdata5[8];
    char stringdata6[14];
    char stringdata7[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMyTcpSocketENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMyTcpSocketENDCLASS_t qt_meta_stringdata_CLASSMyTcpSocketENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "MyTcpSocket"
        QT_MOC_LITERAL(12, 7),  // "offline"
        QT_MOC_LITERAL(20, 0),  // ""
        QT_MOC_LITERAL(21, 12),  // "MyTcpSocket*"
        QT_MOC_LITERAL(34, 8),  // "mysocket"
        QT_MOC_LITERAL(43, 7),  // "recvMsg"
        QT_MOC_LITERAL(51, 13),  // "clientOffline"
        QT_MOC_LITERAL(65, 16)   // "sendFileToClient"
    },
    "MyTcpSocket",
    "offline",
    "",
    "MyTcpSocket*",
    "mysocket",
    "recvMsg",
    "clientOffline",
    "sendFileToClient"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMyTcpSocketENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   41,    2, 0x0a,    3 /* Public */,
       6,    0,   42,    2, 0x0a,    4 /* Public */,
       7,    0,   43,    2, 0x0a,    5 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MyTcpSocket::staticMetaObject = { {
    QMetaObject::SuperData::link<QTcpSocket::staticMetaObject>(),
    qt_meta_stringdata_CLASSMyTcpSocketENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMyTcpSocketENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMyTcpSocketENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MyTcpSocket, std::true_type>,
        // method 'offline'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<MyTcpSocket *, std::false_type>,
        // method 'recvMsg'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clientOffline'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendFileToClient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MyTcpSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyTcpSocket *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->offline((*reinterpret_cast< std::add_pointer_t<MyTcpSocket*>>(_a[1]))); break;
        case 1: _t->recvMsg(); break;
        case 2: _t->clientOffline(); break;
        case 3: _t->sendFileToClient(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MyTcpSocket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyTcpSocket::*)(MyTcpSocket * );
            if (_t _q_method = &MyTcpSocket::offline; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *MyTcpSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyTcpSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMyTcpSocketENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QTcpSocket::qt_metacast(_clname);
}

int MyTcpSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MyTcpSocket::offline(MyTcpSocket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
