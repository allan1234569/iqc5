#-------------------------------------------------
#
# Project created by QtCreator 2016-03-29T12:08:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_cte
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrophoresi/CTE

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_cte.cpp

HEADERS  += w_cte.h
