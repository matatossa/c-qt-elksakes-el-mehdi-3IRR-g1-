#-------------------------------------------------
#
# Project created by QtCreator
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ventegstion
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    additem.cpp \
    updateitem.cpp \
    itemsreport.cpp \
    mydb.cpp \
    expireditems.cpp \
    returneditems.cpp \
    availableitems.cpp \
    finditem.cpp

HEADERS += \
        mainwindow.h \
    additem.h \
    updateitem.h \
    itemsreport.h \
    mydb.h \
    expireditems.h \
    returneditems.h \
    availableitems.h \
    finditem.h

FORMS += \
        mainwindow.ui \
    additem.ui \
    updateitem.ui \
    itemsreport.ui \
    expireditems.ui \
    returneditems.ui \
    availableitems.ui \
    finditem.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
