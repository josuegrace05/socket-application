/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client/client.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Client[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      37,    7,    7,    7, 0x08,
      64,    7,    7,    7, 0x08,
      90,    7,    7,    7, 0x08,
     123,    7,    7,    7, 0x08,
     154,    7,    7,    7, 0x08,
     187,    7,    7,    7, 0x08,
     213,    7,    7,    7, 0x08,
     229,    7,    7,    7, 0x08,
     240,    7,    7,    7, 0x08,
     260,  253,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Client[] = {
    "Client\0\0on_boutonConnexion_clicked()\0"
    "on_boutonEnvoyer_clicked()\0"
    "on_updateButton_clicked()\0"
    "on_sharePlaylistButton_clicked()\0"
    "on_messageText_returnPressed()\0"
    "on_usernameValue_returnPressed()\0"
    "on_folderButton_clicked()\0donneesRecues()\0"
    "connecte()\0deconnecte()\0erreur\0"
    "erreurSocket(QAbstractSocket::SocketError)\0"
};

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Client *_t = static_cast<Client *>(_o);
        switch (_id) {
        case 0: _t->on_boutonConnexion_clicked(); break;
        case 1: _t->on_boutonEnvoyer_clicked(); break;
        case 2: _t->on_updateButton_clicked(); break;
        case 3: _t->on_sharePlaylistButton_clicked(); break;
        case 4: _t->on_messageText_returnPressed(); break;
        case 5: _t->on_usernameValue_returnPressed(); break;
        case 6: _t->on_folderButton_clicked(); break;
        case 7: _t->donneesRecues(); break;
        case 8: _t->connecte(); break;
        case 9: _t->deconnecte(); break;
        case 10: _t->erreurSocket((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Client::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Client::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Client,
      qt_meta_data_Client, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Client::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Client))
        return static_cast<void*>(const_cast< Client*>(this));
    return QWidget::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
