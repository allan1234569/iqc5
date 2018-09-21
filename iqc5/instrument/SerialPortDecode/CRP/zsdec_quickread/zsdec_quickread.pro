#-------------------------------------------------
#
# Project created by QtCreator 2016-01-18T17:02:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_quickread
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/CRP/quickread

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += \
    quickread.cpp \
    main.cpp

HEADERS	+= \
    quickread.h

FORMS	+=
