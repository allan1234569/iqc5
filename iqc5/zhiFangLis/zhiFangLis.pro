#-------------------------------------------------
#
# Project created by QtCreator 2015-06-02T13:00:12
#
#-------------------------------------------------

QT       += xml xmlpatterns widgets sql

QT       -= gui

TARGET = zhiFangLis
TEMPLATE = lib
DESTDIR += ../../iqc5/bin/plugins/lis

DEFINES += XMLPARSE_LIBRARY

INCLUDEPATH += ../iqc5/Model \
               ../iqc5/Rule\
               ../iqc5/Service\
               ../Lis_Import
DEPENDPATH += ../iqc5/Model \
               ../iqc5/Rule\
               ../iqc5/Service\
              ../Lis_Import

SOURCES += \
    ../iqc5/Model/ProjectDetail.cpp \
    ../iqc5/Model/TestType.cpp \
    ../Lis_Import/LisData.cpp \
    xmlquery.cpp \
    ../iqc5/Model/Material.cpp \
    ../iqc5/Model/Project.cpp \
    ../iqc5/Model/Result.cpp \
    ../iqc5/Rule/ChiSquare.cpp \
    ../iqc5/Rule/IRule.cpp \
    ../iqc5/Rule/Rule2of32S.cpp \
    ../iqc5/Rule/Rule6T.cpp \
    ../iqc5/Rule/Rule9X.cpp \
    ../iqc5/Rule/Rule10X.cpp \
    ../iqc5/Rule/Rule12S.cpp \
    ../iqc5/Rule/Rule13S.cpp \
    ../iqc5/Rule/Rule22S.cpp \
    ../iqc5/Rule/Rule41S.cpp \
    ../iqc5/Rule/RuleManager.cpp \
    ../iqc5/Rule/RuleR4S.cpp \
    ../iqc5/Rule/RuleWestgard.cpp \
    ../iqc5/Service/ProjectService.cpp \
    ../iqc5/Service/MaterialBatchService.cpp \
    ../iqc5/Service/ReagentBatchService.cpp \
    ../iqc5/Model/MaterialBatch.cpp \
    ../iqc5/Model/ReagentBatch.cpp \
    ../Lis_Import/lisinterface.cpp \
    configure.cpp \
    interface.cpp \
    zhiFangInterface.cpp \
    ../iqc5/Service/MaterialService.cpp \
    ../iqc5/Service/ReagentService.cpp \
    ../iqc5/Model/Reagent.cpp

HEADERS += \
    ../iqc5/Model/ProjectDetail.h \
    ../iqc5/Model/TestType.h \
    ../Lis_Import/LisData.h \
    xmlquery.h \
    ../iqc5/Model/Material.h \
    ../iqc5/Model/Project.h \
    ../iqc5/Model/Result.h \
    ../iqc5/Rule/ChiSquare.h \
    ../iqc5/Rule/IRule.h \
    ../iqc5/Rule/Rule2of32S.h \
    ../iqc5/Rule/Rule6T.h \
    ../iqc5/Rule/Rule9X.h \
    ../iqc5/Rule/Rule10X.h \
    ../iqc5/Rule/Rule12S.h \
    ../iqc5/Rule/Rule13S.h \
    ../iqc5/Rule/Rule22S.h \
    ../iqc5/Rule/Rule41S.h \
    ../iqc5/Rule/RuleManager.h \
    ../iqc5/Rule/RuleR4S.h \
    ../iqc5/Rule/RuleWestgard.h \
    ../iqc5/Service/ProjectService.h \
    ../iqc5/Service/MaterialBatchService.h \
    ../iqc5/Service/ReagentBatchService.h \
    ../iqc5/Model/MaterialBatch.h \
    ../iqc5/Model/ReagentBatch.h \
    ../Lis_Import/lisinterface.h \
    configure.h \
    interface.h \
    zhiFangInterface.h \
    ../iqc5/Service/MaterialService.h \
    ../iqc5/Service/ReagentService.h \
    ../iqc5/Model/Reagent.h

#LIBS += -L"../bin" -lIParse


unix {
    target.path = /usr/lib
    INSTALLS += target
}
