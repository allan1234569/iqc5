#-------------------------------------------------
#
# Project created by QtCreator 2016-02-19T16:27:46
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_linegene
TEMPLATE = app

include($$PWD/../../DatabaseDecode_Common/DataBaseDecode_Common.pri)

SOURCES += \
    w_linegene.cpp \
    main.cpp

HEADERS  += \
    w_linegene.h
