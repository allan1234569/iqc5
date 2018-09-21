#-------------------------------------------------
#
# Project created by QtCreator 2016-03-23T15:54:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_dsi905
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/DSI905

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_dsi905.cpp

HEADERS  += w_dsi905.h
