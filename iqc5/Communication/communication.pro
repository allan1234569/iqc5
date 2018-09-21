#-------------------------------------------------
#
# Project created by QtCreator 2015-07-15T21:43:48
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = communication
TEMPLATE = app
DESTDIR += ../../iqc5/bin

#include($$PWD\qr\qr.pri)

SOURCES += main.cpp\
    qextserialbase.cpp \
    qextserialport.cpp \
    win_qextserialport.cpp \
    single_application.cpp \
    awarningdialog.cpp \
    res.cpp \
    connection.cpp \
    mainwindow.cpp \
    aserialport.cpp \
    anetworker.cpp \
    aserver.cpp \
    aclient.cpp \
    aprocess.cpp \
    aboutdialog.cpp

HEADERS  += \
    qextserialbase.h \
    qextserialport.h \
    win_qextserialport.h \
    res.h \
    single_application.h \
    awarningdialog.h \
    connection.h \
    mainwindow.h \
    aserialport.h \
    anetworker.h \
    aserver.h \
    aclient.h \
    aprocess.h \
    aboutdialog.h

FORMS    += \
    awarningdialog.ui \
    mainwindow.ui \
    aserialport.ui \
    anetworker.ui \
    aboutdialog.ui

RC_FILE += communication.rc

RESOURCES += \
    pics.qrc
