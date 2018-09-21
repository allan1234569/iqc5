#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T16:32:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_centaur
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/Bayer_ADVIA_CENTAUR

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_centaur.cpp \
    centaursetup.cpp

HEADERS  += w_centaur.h \
    centaursetup.h
