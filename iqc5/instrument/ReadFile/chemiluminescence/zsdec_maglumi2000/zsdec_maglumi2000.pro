#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T14:34:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_maglumi2000
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/MAGLUMI2000

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)


SOURCES += main.cpp\
        w_maglumi2000.cpp \
    maglumi2000_setup.cpp

HEADERS  += w_maglumi2000.h \
    maglumi2000_setup.h
