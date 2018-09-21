#-------------------------------------------------
#
# Project created by QtCreator 2015-08-12T11:12:26
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

TARGET = BNProSpec_Parser
TEMPLATE = app
DESTDIR += ../../../iqc5/bin

INCLUDEPATH +=  ../../iqc5/Model \
                ../../iqc5/Rule \
                ../../iqc5/Service
DEPENDPATH +=   ../../iqc5/Model \
                ../../iqc5/Rule \
                ../../iqc5/Service

SOURCES += main.cpp\
        widget.cpp\
    ../../iqc5/Model/Project.cpp \
    ../../iqc5/Model/ProjectDetail.cpp \
    ../../iqc5/Model/Result.cpp \
    ../../iqc5/Model/TestType.cpp \
    ../../iqc5/Model/MaterialBatch.cpp \
    ../../iqc5/Model/ReagentBatch.cpp \
    ../../iqc5/Model/Material.cpp \
    ../../iqc5/Model/Reagent.cpp \
    mytesttype.cpp \
    myProject.cpp \
    global.cpp \
    ../../iqc5/Model/Device.cpp \
    clientsocket.cpp \
    setupdialog.cpp \
    ../../iqc5/Service/ProjectService.cpp \
    ../../iqc5/Rule/IRule.cpp \
    ../../iqc5/Rule/Rule2of32S.cpp \
    ../../iqc5/Rule/Rule6T.cpp \
    ../../iqc5/Rule/Rule9X.cpp \
    ../../iqc5/Rule/Rule10X.cpp \
    ../../iqc5/Rule/Rule12S.cpp \
    ../../iqc5/Rule/Rule13S.cpp \
    ../../iqc5/Rule/Rule22S.cpp \
    ../../iqc5/Rule/Rule41S.cpp \
    ../../iqc5/Rule/RuleManager.cpp \
    ../../iqc5/Rule/RuleR4S.cpp \
    ../../iqc5/Rule/RuleWestgard.cpp \
    ../../iqc5/Service/MaterialBatchService.cpp \
    ../../iqc5/Service/ReagentBatchService.cpp \
    ../../iqc5/Service/MaterialService.cpp \
    ../../iqc5/Service/ReagentService.cpp

HEADERS  += widget.h \
    ../../iqc5/Model/Project.h \
    ../../iqc5/Model/ProjectDetail.h \
    ../../iqc5/Model/Result.h \
    ../../iqc5/Model/TestType.h \
    ../../iqc5/Rule/RuleR4S.h \
    ../../iqc5/Model/MaterialBatch.h \
    ../../iqc5/Model/Device.h \
    ../../iqc5/Model/ReagentBatch.h \
    ../../iqc5/Model/Material.h \
    ../../iqc5/Model/InputBatch.h \
    ../../iqc5/Model/Reagent.h \
    myTestType.h \
    myProject.h \
    global.h \
    clientsocket.h \
    setupdialog.h \
    ../../iqc5/Service/ProjectService.h \
    ../../iqc5/Rule/IRule.h \
    ../../iqc5/Rule/Rule2of32S.h \
    ../../iqc5/Rule/Rule6T.h \
    ../../iqc5/Rule/Rule9X.h \
    ../../iqc5/Rule/Rule10X.h \
    ../../iqc5/Rule/Rule12S.h \
    ../../iqc5/Rule/Rule13S.h \
    ../../iqc5/Rule/Rule22S.h \
    ../../iqc5/Rule/Rule41S.h \
    ../../iqc5/Rule/RuleManager.h \
    ../../iqc5/Rule/RuleWestgard.h \
    ../../iqc5/Service/MaterialBatchService.h \
    ../../iqc5/Service/ReagentBatchService.h \
    ../../iqc5/Service/MaterialService.h \
    ../../iqc5/Service/ReagentService.h

FORMS    += widget.ui \
    setupdialog.ui

RESOURCES += \
    sources.qrc
