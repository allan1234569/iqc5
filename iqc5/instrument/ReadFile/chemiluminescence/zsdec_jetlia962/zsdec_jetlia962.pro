#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T14:36:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_jetlia962
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/JETLIA962

include($$PWD/../../../ReadFile/ReadFile_Common/ReadFile_Common.pri)

SOURCES += main.cpp\
        w_jetlia962.cpp

HEADERS  += w_jetlia962.h
