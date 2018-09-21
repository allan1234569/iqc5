#-------------------------------------------------
#
# Project created by QtCreator 2016-04-08T11:45:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_e411
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/E411

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_e411.cpp \
    e411_setup.cpp

HEADERS  += w_e411.h \
    e411_setup.h
