#-------------------------------------------------
#
# Project created by QtCreator 2016-02-23T13:18:13
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_d280
TEMPLATE = app

include($$PWD/../../DatabaseDecode_Common/DataBaseDecode_Common.pri)

SOURCES += \
    d280.cpp \
    main.cpp

HEADERS  += \
    d280.h
