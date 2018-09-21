#-------------------------------------------------
#
# Project created by QtCreator 2016-03-22T17:06:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_avl9130
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/AVL9130

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_avl9130.cpp

HEADERS  += w_avl9130.h
