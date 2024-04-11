/****************************************************************************
** Meta object code from reading C++ file 'friend.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TcpClient/friend.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'friend.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSFriendENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSFriendENDCLASS = QtMocHelpers::stringData(
    "Friend",
    "showOnline",
    "",
    "searchUsr",
    "flushFriList",
    "deleteFriend",
    "privateChatFriend",
    "groupChat"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSFriendENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[7];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[10];
    char stringdata4[13];
    char stringdata5[13];
    char stringdata6[18];
    char stringdata7[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSFriendENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSFriendENDCLASS_t qt_meta_stringdata_CLASSFriendENDCLASS = {
    {
        QT_MOC_LITERAL(0, 6),  // "Friend"
        QT_MOC_LITERAL(7, 10),  // "showOnline"
        QT_MOC_LITERAL(18, 0),  // ""
        QT_MOC_LITERAL(19, 9),  // "searchUsr"
        QT_MOC_LITERAL(29, 12),  // "flushFriList"
        QT_MOC_LITERAL(42, 12),  // "deleteFriend"
        QT_MOC_LITERAL(55, 17),  // "privateChatFriend"
        QT_MOC_LITERAL(73, 9)   // "groupChat"
    },
    "Friend",
    "showOnline",
    "",
    "searchUsr",
    "flushFriList",
    "deleteFriend",
    "privateChatFriend",
    "groupChat"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSFriendENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x0a,    1 /* Public */,
       3,    0,   51,    2, 0x0a,    2 /* Public */,
       4,    0,   52,    2, 0x0a,    3 /* Public */,
       5,    0,   53,    2, 0x0a,    4 /* Public */,
       6,    0,   54,    2, 0x0a,    5 /* Public */,
       7,    0,   55,    2, 0x0a,    6 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Friend::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSFriendENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSFriendENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSFriendENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Friend, std::true_type>,
        // method 'showOnline'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'searchUsr'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'flushFriList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteFriend'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'privateChatFriend'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'groupChat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Friend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Friend *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showOnline(); break;
        case 1: _t->searchUsr(); break;
        case 2: _t->flushFriList(); break;
        case 3: _t->deleteFriend(); break;
        case 4: _t->privateChatFriend(); break;
        case 5: _t->groupChat(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *Friend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Friend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSFriendENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Friend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
