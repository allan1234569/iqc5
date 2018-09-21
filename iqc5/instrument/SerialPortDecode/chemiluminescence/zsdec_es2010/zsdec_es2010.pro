#-------------------------------------------------
#
# Project created by QtCreator 2016-04-08T11:50:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_es2010
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/ES2010

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_es2010.cpp \
    es2010_setup.cpp

HEADERS  += w_es2010.h \
    es2010_setup.h
