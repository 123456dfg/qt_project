QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    algorithm.cpp \
    main.cpp \
    mainwindow.cpp \
    mygraphicsscene.cpp \
    myqgraphview.cpp \
    trainstation.cpp

HEADERS += \
    algorithm.h \
    mainwindow.h \
    mygraphicsscene.h \
    myqgraphview.h \
    trainstation.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    map_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    train_map.qrc

msvc{
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}
