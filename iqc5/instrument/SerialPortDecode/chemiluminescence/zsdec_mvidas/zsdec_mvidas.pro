#-------------------------------------------------
#
# Project created by QtCreator 2016-04-07T15:46:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_mvidas
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/MERIEUX_MVIDAS

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_mvidas.cpp

HEADERS  += w_mvidas.h
