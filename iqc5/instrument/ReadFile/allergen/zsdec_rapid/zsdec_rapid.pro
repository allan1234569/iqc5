#-------------------------------------------------
#
# Project created by QtCreator 2016-04-01T14:39:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_rapid
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/allergen/RAPID

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_rapid.cpp \
    w_rapid_setup.cpp

HEADERS  += w_rapid.h \
    w_rapid_setup.h
