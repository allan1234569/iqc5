#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T14:37:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_chemclin
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/CHEMCLIN

include($$PWD/../../../DatabaseDecode/DatabaseDecode_Common/DatabaseDecode_Common.pri)

SOURCES += main.cpp \
    w_chenclin.cpp

HEADERS  += \
    w_chenclin.h
