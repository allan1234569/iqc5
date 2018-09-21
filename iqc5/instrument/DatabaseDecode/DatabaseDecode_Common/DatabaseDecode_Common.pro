#-------------------------------------------------
#
# Project created by QtCreator 2016-01-18T17:19:02
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DatabaseDecode_Common
TEMPLATE = app

include ($$PWD/DataBaseDecode_Common.pri)

HEADERS += \
    widget.h

SOURCES += \
    widget.cpp
