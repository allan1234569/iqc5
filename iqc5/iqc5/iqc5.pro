#-------------------------------------------------
#
# Project created by QtCreator 2014-11-23T13:10:13
#
#-------------------------------------------------

QT       += core gui sql printsupport axcontainer network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iqc5
TEMPLATE = app
DESTDIR += ../../iqc5/bin

QMAKE_CXXFLAGS +=  -Wno-unused-parameter
QMAKE_CXXFLAGS +=  -Wno-unused-but-set-variable

INCLUDEPATH +=  $$PWD/Model \
                $$PWD/Rule \
                $$PWD/Service \
                $$PWD/Formula \
                $$PWD/UI/PV \
                $$PWD/Common \

DEPENDPATH +=   $$PWD/Model \
                $$PWD/Rule \
                $$PWD/Service \
                $$PWD/Formula \
                $$PWD/UI/PV \
                $$PWD/Common
#                $$PWD/doc

SOURCES += main.cpp\
        MainWindow.cpp \
    Model/Category.cpp \
    Model/Device.cpp \
    Model/Material.cpp \
    Model/Method.cpp \
    Model/Project.cpp \
    Model/Reagent.cpp \
    Model/Result.cpp \
    Model/Security.cpp \
    Model/Standard.cpp \
    Model/TestParam.cpp \
    Model/TestType.cpp \
    Model/UserInput.cpp \
    Model/UserInput_Detail.cpp \
    Rule/IRule.cpp \
    Rule/Rule2of32S.cpp \
    Rule/Rule6T.cpp \
    Rule/Rule9X.cpp \
    Rule/Rule10X.cpp \
    Rule/Rule12S.cpp \
    Rule/Rule13S.cpp \
    Rule/Rule22S.cpp \
    Rule/Rule41S.cpp \
    Rule/RuleManager.cpp \
    Rule/RuleR4S.cpp \
    Rule/RuleWestgard.cpp \
    Service/CategoryService.cpp \
    Service/DeviceService.cpp \
    Service/MaterialService.cpp \
    Service/MethodService.cpp \
    Service/ProjectService.cpp \
    Service/ReagentService.cpp \
    Service/TestParamService.cpp \
    Service/TestTypeService.cpp \
    Model/Brand.cpp \
    Model/Country.cpp \
    Model/Density.cpp \
    Model/Manufacturer.cpp \
    Model/MaterialBatch.cpp \
    Model/Unit.cpp \
    Model/User.cpp \
    Model/InputBatch.cpp \
    Model/InputConfig.cpp \
    Model/Lis.cpp \
    Model/Model.cpp \
    Model/ModelCategory.cpp \
    Model/ReagentBatch.cpp \
    Service/ManufacturerService.cpp \
    UI/EditDevice.cpp \
    UI/ManageDevice.cpp \
    Service/BrandService.cpp \
    Service/ModelService.cpp \
    UI/EditMaterial.cpp \
    UI/ManageMaterial.cpp \
    UI/EditMethod.cpp \
    UI/EditReagent.cpp \
    UI/EditType.cpp \
    UI/ManageMethod.cpp \
    UI/ManageReagent.cpp \
    UI/ManageType.cpp \
    UI/ManageProject.cpp \
    UI/EditProject.cpp \
    Service/UnitService.cpp \
    UI/EditUser.cpp \
    UI/ManageUser.cpp \
    UI/NewProjectBatch.cpp \
    UI/InputDataSingle.cpp \
    UI/InputDataMulti.cpp \
    UI/Login.cpp \
    Model/ProjectDetail.cpp \
    Service/MaterialBatchService.cpp \
    Service/ReagentBatchService.cpp \
    UI/ManageMaterialBatch.cpp \
    UI/ManageReagentBatch.cpp \
    UI/ManageMaterialTestType.cpp \
    UI/ManageReagentTestType.cpp \
    UI/ManageMethodTestType.cpp \
    UI/ConfigColumn.cpp \
    UI/NewReagentBatch.cpp \
    UI/NewMaterialBatch.cpp \
    UI/AnalyzeProject.cpp \
    UI/PopBox.cpp \
    UI/TableView.cpp \
    UI/ChartView.cpp \
    Service/CountryService.cpp \
    UI/ChartTitliBar.cpp \
    UI/CustomQwtPlot.cpp \
    UI/AnalyzeRule.cpp \
    UI/Circle.cpp \
    UI/CircleView.cpp \
    UI/Background.cpp \
    UI/AnalyzeDevice.cpp \
    UI/PV/Pv_Precision.cpp \
    Model/Precision.cpp \
    UI/PV/Pv_Accruacy.cpp \
    UI/PV/Pv_AccuracyPlot.cpp \
    UI/PV/Pv_ReportableRange.cpp \
    Model/Accruacy.cpp \
    UI/PV/Pv_ExcursionChart.cpp \
    UI/PV/Pv_TextBrowser.cpp \
    Rule/ChiSquare.cpp \
    UI/TipBox.cpp \
    UI/ShowToolTip.cpp \
    Model/UserInput_TestType.cpp \
    Common/Settings.cpp \
    Service/Userservice.cpp \
    UI/ProjectDataSheet.cpp \
    UI/ExportData.cpp \
    Model/DataSheet.cpp \
    Service/DataSheetService.cpp \
    UI/daterangedialog.cpp \
    Rule/Rule14S.cpp \
    Rule/Rule15S.cpp \
    Rule/Rule12dot5S.cpp \
    Rule/Rule13dot5S.cpp \
    Rule/Rule31S.cpp \
    Delegate/DateDelegate.cpp \
    Delegate/LineEditDelegate.cpp \
    UI/SixSigma_QCRulesScreening.cpp \
    UI/EvaluationParameter.cpp \
    UI/ManageDataImport.cpp \
    Delegate/trackdelegate.cpp \
    UI/Registration.cpp \
    LoginMainWindow.cpp \
    Model/MachineCode.cpp

HEADERS  += MainWindow.h \
    Model/Category.h \
    Model/Device.h \
    Model/Material.h \
    Model/Method.h \
    Model/Reagent.h \
    Model/Result.h \
    Model/Security.h \
    Model/Standard.h \
    Model/TestParam.h \
    Model/TestType.h \
    Model/UserInput.h \
    Model/UserInput_Detail.h \
    Rule/IRule.h \
    Rule/Rule2of32S.h \
    Rule/Rule6T.h \
    Rule/Rule9X.h \
    Rule/Rule10X.h \
    Rule/Rule12S.h \
    Rule/Rule13S.h \
    Rule/Rule22S.h \
    Rule/Rule41S.h \
    Rule/RuleManager.h \
    Rule/RuleR4S.h \
    Rule/RuleWestgard.h \
    Service/CategoryService.h \
    Service/DeviceService.h \
    Service/MaterialService.h \
    Service/MethodService.h \
    Service/ReagentService.h \
    Service/TestParamService.h \
    Service/TestTypeService.h \
    Model/Brand.h \
    Model/Country.h \
    Model/Density.h \
    Model/Manufacturer.h \
    Model/MaterialBatch.h \
    Model/Unit.h \
    Model/User.h \
    Model/InputBatch.h \
    Model/InputConfig.h \
    Model/Lis.h \
    Model/Model.h \
    Model/ModelCategory.h \
    Model/ReagentBatch.h \
    Service/ManufacturerService.h \
    UI/EditDevice.h \
    UI/ManageDevice.h \
    Service/BrandService.h \
    Service/ModelService.h \
    UI/EditMaterial.h \
    UI/ManageMaterial.h \
    UI/EditMethod.h \
    UI/EditReagent.h \
    UI/EditType.h \
    UI/ManageMethod.h \
    UI/ManageReagent.h \
    UI/ManageType.h \
    UI/ManageProject.h \
    UI/EditProject.h \
    Service/UnitService.h \
    UI/EditUser.h \
    UI/ManageUser.h \
    UI/NewProjectBatch.h \
    UI/InputDataSingle.h \
    UI/InputDataMulti.h \
    UI/Login.h \
    Model/Project.h \
    Service/ProjectService.h \
    Model/ProjectDetail.h \
    Service/MaterialBatchService.h \
    Service/ReagentBatchService.h \
    UI/ManageMaterialBatch.h \
    UI/ManageReagentBatch.h \
    UI/ManageMaterialTestType.h \
    UI/ManageReagentTestType.h \
    UI/ManageMethodTestType.h \
    UI/ConfigColumn.h \
    UI/NewReagentBatch.h \
    UI/NewMaterialBatch.h \
    UI/AnalyzeProject.h \
    UI/PopBox.h \
    UI/TableView.h \
    UI/ChartView.h \
    Service/CountryService.h \
    UI/ChartTitliBar.h \
    UI/CustomQwtPlot.h \
    UI/AnalyzeRule.h \
    UI/Circle.h \
    UI/CircleView.h \
    UI/Background.h \
    UI/AnalyzeDevice.h \
    UI/PV/Pv_Precision.h \
    Model/Precision.h \
    Formula/formula.h \
    UI/PV/Pv_Accruacy.h \
    UI/PV/Pv_AccuracyPlot.h \
    UI/PV/Pv_ReportableRange.h \
    Model/Accruacy.h \
    UI/PV/Pv_ExcursionChart.h \
    Common/Axis.h \
    Common/Round.h \
    UI/PV/Pv_TextBrowser.h \
    Rule/ChiSquare.h \
    UI/TipBox.h \
    UI/ShowToolTip.h \
    Model/UserInput_TestType.h \
    Common/Settings.h \
    Service/Userservice.h \
    UI/ProjectDataSheet.h \
    UI/ExportData.h \
    Model/DataSheet.h \
    Service/DataSheetService.h \
    UI/daterangedialog.h \
    Rule/Rule14S.h \
    Rule/Rule15S.h \
    Rule/Rule12dot5S.h \
    Rule/Rule13dot5S.h \
    Rule/Rule31S.h \
    Delegate/DateDelegate.h \
    Delegate/LineEditDelegate.h \
    UI/SixSigma_QCRulesScreening.h \
    UI/EvaluationParameter.h \
    UI/ManageDataImport.h \
    Delegate/trackdelegate.h \
    UI/Registration.h \
    LoginMainWindow.h \
    Model/MachineCode.h

FORMS    += MainWindow.ui \
    UI/EditDevice.ui \
    UI/ManageDevice.ui \
    UI/ManageMaterial.ui \
    UI/EditMaterial.ui \
    UI/EditMethod.ui \
    UI/EditReagent.ui \
    UI/EditType.ui \
    UI/ManageMethod.ui \
    UI/ManageReagent.ui \
    UI/ManageType.ui \
    UI/EditProject.ui \
    UI/ManageProject.ui \
    UI/NewProjectBatch.ui \
    UI/InputDataSingle.ui \
    UI/InputDataMulti.ui \
    UI/Login.ui \
    UI/ManageMaterialBatch.ui \
    UI/ManageReagentBatch.ui \
    UI/ManageMaterialTestType.ui \
    UI/ManageReagentTestType.ui \
    UI/ManageMethodTestType.ui \
    UI/ConfigColumn.ui \
    UI/ChartView.ui \
    UI/NewReagentBatch.ui \
    UI/NewMaterialBatch.ui \
    UI/AnalyzeProject.ui \
    UI/popbox.ui \
    UI/TableView.ui \
    UI/ChartTitliBar.ui \
    UI/CustomQwtPlot.ui \
    UI/AnalyzeRule.ui \
    UI/Circle.ui \
    UI/PV/Pv_Precision.ui \
    UI/PV/Pv_Accruacy.ui \
    UI/PV/Pv_AccuracyPlot.ui \
    UI/PV/Pv_ReportableRange.ui \
    UI/PV/Pv_ExcursionChart.ui \
    UI/PV/Pv_TextBrowser.ui \
    UI/TipBox.ui \
    UI/AnalyzeDevice.ui \
    UI/ProjectDataSheet.ui \
    UI/ExportData.ui \
    UI/daterangedialog.ui \
    UI/SixSigma_QCRulesScreening.ui \
    UI/EvaluationParameter.ui \
    UI/ManageDataImport.ui \
    UI/Registration.ui \
    LoginMainWindow.ui

#UI_DIR += ./

RESOURCES += \
    Icon.qrc


win32:CONFIG(release, debug|release): LIBS += -L"C:/Qt/QtitanRibbon Demo/bin/" -lqtnribbon3
else:win32:CONFIG(debug, debug|release): LIBS += -L"C:/Qt/QtitanRibbon Demo/bin/" -lqtnribbon3

INCLUDEPATH += "C:/Qt/QtitanRibbon Demo/include"
DEPENDPATH += "C:/Qt/QtitanRibbon Demo/include"

INCLUDEPATH += "C:/Qt/Qt5.3.1/5.3/mingw482_32/include/QWT/"
DEPENDPATH += "C:/Qt/Qt5.3.1/5.3/mingw482_32/include/QWT/"

CONFIG(release, debug|release): LIBS += -L"C:/Qt/Qt5.3.1/5.3/mingw482_32/lib/" -lqwt
                                else: LIBS += -L"/C:/Qt/Qt5.3.1/5.3/mingw482_32/lib/" -lqwtd

OTHER_FILES += \
    Resource/columns.txt
