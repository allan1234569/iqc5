#-------------------------------------------------
#
# Project created by QtCreator 2016-03-23T12:09:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_avl9180
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/AVL9180

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_avl9180.cpp

HEADERS  += w_avl9180.h
