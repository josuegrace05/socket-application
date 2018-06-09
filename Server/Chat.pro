HEADERS += \
    server.h \
    client.h

SOURCES += \
    server.cpp \
    main.cpp \
    client.cpp

TEMPLATE = app
QT += widgets network
DEPENDPATH += .
INCLUDEPATH += .
