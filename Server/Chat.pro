HEADERS += \
    server.h \
    client.h

SOURCES += \
    server.cpp \
    client.cpp \
    main.cpp

TEMPLATE = app
QT += widgets network
DEPENDPATH += .
INCLUDEPATH += .
