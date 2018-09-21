#-------------------------------------------------
#
# Project created by QtCreator 2015-11-27T11:30:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Application_Configuration
TEMPLATE = app
DESTDIR += ../../iqc5/bin


SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

FORMS    += dialog.ui

RESOURCES += \
    images.qrc

RC_FILE += configureApp.rc
