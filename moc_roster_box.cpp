/****************************************************************************
** Meta object code from reading C++ file 'roster_box.h'
**
** Created: Thu Feb 12 17:40:48 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "roster_box.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'roster_box.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QTlenRosterBox[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      22,   16,   15,   15, 0x0a,
      69,   64,   47,   15, 0x0a,
     139,   15,   47,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QTlenRosterBox[] = {
    "QTlenRosterBox\0\0yesno\0setOfflinesVisible(bool)\0"
    "QTreeWidgetItem*\0,,,,\0"
    "addRosterItem(QString,QTlenPresence,QString,QString,QTreeWidgetItem*)\0"
    "addRosterNode(QString)\0"
};

const QMetaObject QTlenRosterBox::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_QTlenRosterBox,
      qt_meta_data_QTlenRosterBox, 0 }
};

const QMetaObject *QTlenRosterBox::metaObject() const
{
    return &staticMetaObject;
}

void *QTlenRosterBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QTlenRosterBox))
        return static_cast<void*>(const_cast< QTlenRosterBox*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int QTlenRosterBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setOfflinesVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: { QTreeWidgetItem* _r = addRosterItem((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QTlenPresence(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< QTreeWidgetItem**>(_a[0]) = _r; }  break;
        case 2: { QTreeWidgetItem* _r = addRosterNode((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QTreeWidgetItem**>(_a[0]) = _r; }  break;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
