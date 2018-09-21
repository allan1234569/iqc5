#-------------------------------------------------
#
# Project created by QtCreator 2015-12-23T14:27:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = communication_setup
TEMPLATE = app
DESTDIR += ../../iqc5/bin

SOURCES += main.cpp\
        widget.cpp \
    res.cpp

HEADERS  += widget.h \
    res.h

FORMS    += widget.ui

RC_FILE += communicatio_setup.rc
