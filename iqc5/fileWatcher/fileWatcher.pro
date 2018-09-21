#-------------------------------------------------
#
# Project created by QtCreator 2015-07-07T11:06:22
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fileWatcher
TEMPLATE = app
DESTDIR += ../../iqc5/bin

SOURCES += main.cpp \
    configureform.cpp \
    mainwindow.cpp \
    global.cpp

HEADERS  += \
    configureform.h \
    mainwindow.h \
    global.h

FORMS    += \
#    mainwindow.ui
    configureform.ui

RESOURCES += \
    icon.qrc
