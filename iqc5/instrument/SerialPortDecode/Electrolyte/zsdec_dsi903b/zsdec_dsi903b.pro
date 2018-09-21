#-------------------------------------------------
#
# Project created by QtCreator 2016-03-23T15:30:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_dsi903b
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/DSI903B

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_dsi903b.cpp

HEADERS  += w_dsi903b.h
